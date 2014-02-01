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
    HttpStatusCode httpStatusCode;
    QString requestUrl;
};

ConnectionHandler::ConnectionHandler(QTcpSocket *socket, QHash<QString, Collection*> collections, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->socket = socket;
    d->collections = collections;
    d->httpStatusCode = HttpOk;

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

    if (d->socket->isOpen()) {
        d->socket->close();
        d->socket->deleteLater();
    }

    delete d;
}

QString ConnectionHandler::httpStatusCodeToString() const
{
    switch (d->httpStatusCode) {
        case HttpStatusCode::HttpOk:
            return "HTTP/1.1 200 OK\r\n";
            break;
        case HttpStatusCode::HttpBadRequest:
            return "HTTP/1.1 400 Bad Request\r\n";
            break;
        case HttpStatusCode::HttpNotFound:
            return "HTTP/1.1 404 Not Found\r\n";
            break;
        default:
            return "HTTP/1.1 404 Not Found\r\n";
    }
}

void ConnectionHandler::parseData()
{
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

                d->httpStatusCode = HttpBadRequest;

                // respond to request
                d->socket->write(httpStatusCodeToString().toUtf8());
                d->socket->close();
                return;
            }

            // remove trailing '/'
            auto checkTrailingSlash = [this] () {
                // in case "/" is requested, we don't want to remove it!!
                if (d->requestUrl.endsWith('/') && d->requestUrl.size() != 1) {
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
        Collection *collection = requestUrl.isEmpty() ? d->collections.value(d->requestUrl) : d->collections.value(requestUrl);

        if (d->requestType == GETRequestType) {
            response = collection->collectionGet(resource);
        } else if (d->requestType == POSTRequestType) {
            response = d->collections.value(d->requestUrl)->collectionPost();
        } else if (d->requestType == PUTRequestType) {
            response = d->collections.value(d->requestUrl)->collectionPut();
        }

        // don't need to handle the "else" here, as all methods not available are handled previously during parsing

        // stash http status code
        d->httpStatusCode = collection->httpStatusCode();

        d->socket->write(httpStatusCodeToString().toUtf8());
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
        callCollection(requestUrlWithoutResource, guessedResource);
    } else {
        // ERROR
        // TODO return bad request/not handled/bla bla bla
        qDebug("TODO return bad request/not handled/bla bla bla");

        // respond to request
        d->httpStatusCode = HttpBadRequest;
        d->socket->write(httpStatusCodeToString().toUtf8());
        d->socket->close();
    }


    if (d->socket->isOpen()) {
        d->socket->close();
    }

    return;
}

void ConnectionHandler::setHttpStatusCode(ConnectionHandler::HttpStatusCode code)
{
    d->httpStatusCode = code;
}


