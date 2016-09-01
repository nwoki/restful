#include "collection.h"
#include "connectionhandler.h"
#include "request.h"
#include "requestserver.h"

#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtNetwork/QTcpSocket>

namespace RESTFul {

class RequestServer::Private
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


RequestServer::RequestServer(quint16 port, QObject *parent)
    : QTcpServer(parent)
    , d(new Private)
{
    d->port = port;
}


RequestServer::~RequestServer()
{
    delete d;
}

bool RequestServer::start()
{
    // start listening
    // TODO handle binding error
    bool result = listen(QHostAddress::Any, d->port);

    if (result) {
        qDebug() << "[RequestServer::RequestServer] listening on: " << d->port;

        // get client socket on connect
        connect(this, &QTcpServer::newConnection, [this]() {
            qDebug("[RequestServer::RequestServer]");

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
            connect(req, &Request::finished, this, &RequestServer::onRequestFinished);
        });
    } else {
        qDebug() << "ERROR starting RequestServer: " << errorString();
    }

    return result;
}

void RequestServer::addCollection(Collection *collection)
{
    d->connectionHandler->addCollection(collection);
}

void RequestServer::onRequestFinished()
{
    delete sender();
}

}



