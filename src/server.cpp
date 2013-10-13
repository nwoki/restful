#include "connectionhandler.h"
#include "server.h"

#include <QtCore/QDebug>

#include <QtNetwork/QTcpSocket>


class Server::Private
{
public:
    quint16 port;
};



Server::Server(quint16 port, QObject *parent)
    : QTcpServer(parent)
    , d(new Private)
{
    d->port = port;

    // start listening
    // TODO handle binding error
    if (listen(QHostAddress::Any, d->port)) {
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

            // create connection obj to handle the http request by itself
            ConnectionHandler *connHandler = new ConnectionHandler(socket);
        });

    } else {
        // TODO quit app?
    }
}


Server::~Server()
{
    delete d;
}


