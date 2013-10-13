#include "connectionhandler.h"

#include <QtNetwork/QTcpSocket>


class ConnectionHandler::Private
{
public:
    QTcpSocket *socket;
};

ConnectionHandler::ConnectionHandler(QTcpSocket *socket, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->socket = socket;

    // TODO read data
//     connect(d->socket, SIGNAL(readyRead()), this, SLOT(readData()));

    // delete on socket life end
    connect(d->socket, &QTcpSocket::disconnected, [this]() {
        d->socket->deleteLater();
        deleteLater();
    });
}


ConnectionHandler::~ConnectionHandler()
{
    delete d;
    qDebug("[ConnectionHandler::~ConnectionHandler]");
}
