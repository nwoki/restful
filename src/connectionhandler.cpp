#include "collection.h"
#include "connectionhandler.h"

#include <QtCore/QDebug>

#include <QtNetwork/QTcpSocket>


class ConnectionHandler::Private
{
public:
    QTcpSocket *socket;
    QHash<QString, Collection*> collections;

    // request info
    QString requestData;
    QVariantHash requestParameters;
    HttpRequestType requestType;
    QString requestUrl;
};

ConnectionHandler::ConnectionHandler(QTcpSocket *socket, QHash<QString, Collection*> collections, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->socket = socket;
    d->collections = collections;

    connect(d->socket, &QIODevice::readyRead, [this] () {
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

    QByteArray data;

    while (d->socket->bytesAvailable() != 0) {
        data += d->socket->readAll();
    }

    QTextStream streamData(data);
    QString line = streamData.readLine();

    // parse header
    while (!line.isEmpty()) {
        // TODO store "Content-Type"

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
                        d->requestParameters.insert(param.split('=').first(), param.split('=').last());
                    }
                }
            } else {
                d->requestUrl = requestSplit.at(1);

                // post/put data comes after a new line break which is what makes the while loop exit.
                // so the parsing is done outside
            }

            qDebug() << d->requestUrl << " collection to call";
        }

        line = streamData.readLine();
    }

    // post/put data. Saved "as is" so that developers can handle the data as they wish
    d->requestData = streamData.readLine();
}

