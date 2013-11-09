#include "connectionhandler.h"

#include <QtCore/QDebug>

#include <QtNetwork/QTcpSocket>


class ConnectionHandler::Private
{
public:
    QTcpSocket *socket;
    QByteArray data;
    HttpRequestType requestType;
    QByteArray requestUrl;
};

ConnectionHandler::ConnectionHandler(QTcpSocket *socket, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->socket = socket;

    connect(d->socket, &QIODevice::readyRead, [this] () {
        d->data = d->socket->readAll();

        // parse received data
        parseData();
    });

    // delete on socket life end
    connect(d->socket, &QTcpSocket::disconnected, [this]() {
        d->socket->deleteLater();
        deleteLater();
    });
}


ConnectionHandler::~ConnectionHandler()
{
    qDebug("[ConnectionHandler::~ConnectionHandler]");
    delete d;
}


void ConnectionHandler::parseData()
{
    qDebug("ConnectionHandler::finishedReading");
//     // update data
//     QByteArray data = d->socket->readLine();
//
//     // exit if we have no data to parse
//     if (data.isEmpty()) {
//         return;
//     }
//
//     // check our data
//     qDebug() << data;
//     if (data.startsWith("GET ")) {
//         d->requestType = GETRequestType;
//     } else if (data.startsWith("POST ")) {
//         d->requestType = POSTRequestType;
//     } else if (data.startsWith("PUT ")) {
//         d->requestType = PUTRequestType;
//     } else {
//         // TODO return error. Kill off request
//     }
//
//     // TODO get request url
//
//     qDebug() << d->requestType;
//
//
//     QList<QByteArray> requestParts = data.split(' ');
//
//     // be sure to have all parts of the request
//     if (requestParts.count() > 2) {
//         // extract url (@1)
//         QByteArray url = requestParts.at(1);
//
//         qDebug() << "url : " << url;
//
//         // get scope and method name (TODO, see paper notes on how to handle this part)
// //         QStringList
//
//     }
}

