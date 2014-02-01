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

            // remove trailing '/'
            auto checkTrailingSlash = [this] () {
                if (d->requestUrl.endsWith('/')) {
                    d->requestUrl.remove(d->requestUrl.size() - 1, 1);
                }
            };

            // second part contains the collection to call
            if (d->requestType == GETRequestType) {
                // the GET might have url parameters as well. Check
                QStringList urlSplit = requestSplit.at(1).split('?');
                d->requestUrl = urlSplit.first();
                checkTrailingSlash();

                if (urlSplit.count() > 1) {
                    for (const QString &param : urlSplit.value(1).split('&')) {
                        d->requestParameters.insert(param.split('=').first(), param.split('=').last());
                    }
                }
            } else {
                d->requestUrl = requestSplit.at(1);
                checkTrailingSlash();

                // post/put data comes after a new line break which is what makes the while loop exit.
                // so the parsing is done outside
            }
        }

        line = streamData.readLine();
    }

    // post/put data. Saved "as is" so that developers can handle the data as they wish
    d->requestData = streamData.readLine();


    // now handle the request url

    // as there's no way of telling if the url is pointing to a resource on a collection
    // or to the whole collection, I have to check for the url validity
    //
    // if the full url is not contained in the hash, then MAYBE the last part of the
    // url (after the last '/') is the resource. So I try checking if the hash contains the
    // url without the last part.
    //
    // If both tries fail, then the url is not contained in the hash
    auto callCollection = [this] (const QString &requestUrl = QString(), const QString &resource = QString()) {
        QByteArray response;

        if (d->requestType == GETRequestType) {
            response = requestUrl.isEmpty() ? d->collections.value(d->requestUrl)->collectionGet(resource) : d->collections.value(requestUrl)->collectionGet(resource);
        }
        /*
         * else if (d->requestType == PUTRequestType) {
         *     response = d->collections.value(d->requestUrl)->collectionGet();
         * } else if (d->requestType == POSTRequestType) {
         *     response = d->collections.value(d->requestUrl)->collectionGet();
         * }
         */

        // TODO allow collection to set http status codes

        // this is hardcoded for now. Will replace soon
        d->socket->write("HTTP/1.1 200 OK\r\n");
        d->socket->write(QString("Content-Length: %1\r\n\r\n").arg(response.size()).toUtf8());
        d->socket->write(response);
        d->socket->close();
    };


    QString guessedResource = d->requestUrl.split('/').last();
    QString requestUrlWithoutResource = d->requestUrl.left(d->requestUrl.indexOf("/" + guessedResource));

    // call collection
    if (d->collections.contains(d->requestUrl)) {
        callCollection(d->requestUrl);
    } else if (d->collections.contains(requestUrlWithoutResource)) {
        qDebug() << "url with resource!";
        callCollection(requestUrlWithoutResource, guessedResource);
    } else {
        // ERROR
        // TODO return bad request/not handled/bla bla bla
    }
}

