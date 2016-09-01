#include "request.h"


#include <QtNetwork/QTcpSocket>


namespace RESTFul {

class Request::Private
{
public:
    Private()
        : socket(nullptr)
    {}

    ~Private()
    {
        if (socket && socket->isOpen()) {
            socket->close();
            delete socket;
        }
    }


    QTcpSocket *socket;
};


Request::Request(QTcpSocket *socket, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->socket = socket;

    connect(d->socket, &QTcpSocket::readyRead, this, &Request::parseRequest);
}

Request::~Request()
{
    qDebug("[Request::~Request]");
    delete d;
}

void Request::parseRequest()
{
    QByteArray data(d->socket->readAll());

    qDebug() << "SOCKET DATA INCOME: " << data;

    d->socket->close();


    // TEST this doesn't go here but after having responded to the client
    Q_EMIT finished();
}




}   // RESTFul
