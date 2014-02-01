#include "collection.h"
#include "connectionhandler.h"

#include <QtCore/QDebug>

#include <QtNetwork/QTcpSocket>


class ConnectionHandler::Private
{
public:
    QTcpSocket *socket;
    QByteArray data;
    HttpRequestType requestType;
    QString requestUrl;
    QHash<QString, Collection*> collections;
    QVariantHash parameters;
};

ConnectionHandler::ConnectionHandler(QTcpSocket *socket, QHash<QString, Collection*> collections, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->socket = socket;
    d->collections = collections;

    connect(d->socket, &QIODevice::readyRead, [this] () {
        d->data = d->socket->readAll();

        // parse received data
        parseData();
    });

    // TODO connect on error

    // delete on socket life end
    connect(d->socket, &QTcpSocket::disconnected, [this] () {
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

    while (d->socket->bytesAvailable() != 0) {
        d->data += d->socket->readAll();
    }

    qDebug() << "GOT: " << d->data;

    QTextStream streamData(d->data);
    QString line = streamData.readLine();

    // parse header
    while (!line.isEmpty()) {
        qDebug() << "line: " << line;

        // determine request type
        if (line.contains("HTTP")) {
            QStringList requestSplit = line.split(' ', QString::SkipEmptyParts);

            // first part of the split contains the request type
            QString reqTypeStr = requestSplit.first();

            if (reqTypeStr == "GET") {
                d->requestType = GETRequestType;
            } else if (reqTypeStr == "POST") {
                d->requestType = POSTRequestType;
            } else if (reqTypeStr == "PUT") {
                d->requestType = PUTRequestType;
            } else {
                d->requestType = UnknownRequestType;
                qDebug("[ConnectionHandler::parseData] UnknownRequestType not handled");
                return;
            }

            // second part contains the collection to call
            if (d->requestType == GETRequestType) {
                // the GET might have url parameters as well. Check
                QStringList urlSplit = requestSplit.at(1).split('?');
                d->requestUrl = urlSplit.first();

                if (urlSplit.count() > 1) {
                    for (const QString &param : urlSplit.value(1).split('&')) {
                        d->parameters.insert(param.split('=').first(), param.split('=').last());
                    }
                }
            } else {
                d->requestUrl = requestSplit.at(1);

                // get POST/PUT data
            }

            qDebug() << d->requestUrl << " collection to call";
        }

        line = streamData.readLine();
    }
}

