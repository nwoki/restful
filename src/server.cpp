#include "collection.h"
#include "connectionhandler.h"
#include "request.h"
#include "server.h"

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtNetwork/QTcpSocket>

namespace RESTFul {

class Server::Private
{
public:
    Private()
        : connectionHandler(new ConnectionHandler)
    {}

    ~Private()
    {
        delete connectionHandler;
    }


    quint16 port;
//    QHash<QString, Collection*> collections;
    ConnectionHandler *connectionHandler;
};


Server::Server(quint16 port, QObject *parent)
    : QTcpServer(parent)
    , d(new Private)
{
    d->port = port;
}


Server::~Server()
{
    delete d;
}

bool Server::start()
{
    // start listening
    // TODO handle binding error
    bool result = listen(QHostAddress::Any, d->port);

    if (result) {
        qDebug() << "[Server::Server] listening on: " << d->port;

        // get client socket on connect
        connect(this, &QTcpServer::newConnection, [this]() {
            qDebug("[Server::Server]");

            if (!hasPendingConnections()) {
                return;
            }

            QTcpSocket *socket = nextPendingConnection();

            // should never happen
            if (!socket) {
                return;
            }

            Request *req = new Request(socket);
            connect(req, &Request::get, d->connectionHandler, &ConnectionHandler::onRequest);
            connect(req, &Request::post, d->connectionHandler, &ConnectionHandler::onRequest);
            connect(req, &Request::post, d->connectionHandler, &ConnectionHandler::onRequest);
            connect(req, &Request::finished, this, &Server::onRequestFinished);
        });
    } else {
        qDebug() << "ERROR starting server: " << errorString();
    }

    return result;
}

void Server::addCollection(Collection *collection)
{
    d->connectionHandler->addCollection(collection);
}

void Server::onRequestFinished()
{
    delete sender();
}

}



