#include "collection.h"
#include "connectionhandler.h"

#include <QtCore/QDebug>

#include <QtNetwork/QTcpSocket>

namespace RESTFul {

class ConnectionHandler::Private
{
public:
    Private() {}
    ~Private() {}

//    QTcpSocket *socket;
    QHash<QString, Collection*> collections;

//    // request info
//    QByteArray requestData;             // data requested when calling POST/PUT
//    QVariantHash requestParameters;     // data requested when calling GET
//    ConnectionHandler::HttpRequestType requestType;
//    ConnectionHandler::HttpStatusCode httpStatusCode;
//    QString requestUrl;
};

ConnectionHandler::ConnectionHandler(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
//    qDebug() << "CREATED WITH DATA : " << socket->readAll();

//    connect(d->socket, &QIODevice::readyRead, [this] () {
//        // parse received data from http request
//        parseData();
//    });

//    // TODO connect on error

//    // delete on socket life end
//    connect(d->socket, &QTcpSocket::disconnected, [this] () {
////        d->socket->deleteLater();
////        deleteLater();
//        delete d->socket;
//        d->socket = nullptr;
//    });
}


ConnectionHandler::~ConnectionHandler()
{
    qDebug("[ConnectionHandler::~ConnectionHandler]");
    delete d;
}

void ConnectionHandler::addCollection(Collection *collection)
{
    d->collections.insert(collection->path(), collection);
}

//void ConnectionHandler::callCollection(const QString &requestUrl, const QString &resource)
//{
//    QByteArray response;
//    Collection *collection = requestUrl.isEmpty() ? d->collections.value(d->requestUrl) : d->collections.value(requestUrl);

//    if (d->requestType == GETRequestType) {
//        response = collection->collectionGet(resource, d->requestParameters);
//    } else if (d->requestType == POSTRequestType) {
//        response = d->collections.value(d->requestUrl)->collectionPost(d->requestData, resource);
//    } else if (d->requestType == PUTRequestType) {
//        response = d->collections.value(d->requestUrl)->collectionPut(d->requestData, resource);
//    }

//    // don't need to handle the "else" here, as all methods not available are handled previously during parsing

//    // stash http status code
//    d->httpStatusCode = collection->httpStatusCode();

//    // TODO create proper response
//    d->socket->write(httpStatusCodeToString().toUtf8());
//    d->socket->write("Content-Type: \"text/plain\"\r\n");
//    d->socket->write(QString("Content-Length: %1\r\n").arg(response.size()).toUtf8());
//    d->socket->write(response + "\r\n");
//    d->socket->write("Connection: close\r\n");
//    d->socket->write("\r\n\r\n");   // close
////    d->socket->close();
//}

//QString ConnectionHandler::httpStatusCodeToString() const
//{
//    switch (d->httpStatusCode) {
//        case HttpStatusCode::HttpOk:
//            return "HTTP/1.1 200 OK\r\n";
//            break;
//        case HttpStatusCode::HttpBadRequest:
//            return "HTTP/1.1 400 Bad Request\r\n";
//            break;
//        case HttpStatusCode::HttpNotFound:
//            return "HTTP/1.1 404 Not Found\r\n";
//            break;
//        default:
//            return "HTTP/1.1 404 Not Found\r\n";
//    }
//}

//void ConnectionHandler::parseData()
//{
//    qDebug("[ConnectionHandler::parseData]");

//    // remove trailing '/'
//    auto checkTrailingSlash = [this] () {
//        // in case "/" is requested, we don't want to remove it!!
//        if (d->requestUrl.endsWith('/') && d->requestUrl.size() != 1) {
//            d->requestUrl.remove(d->requestUrl.size() - 1, 1);
//        }
//    };



//    QByteArray data;

//    while (d->socket->bytesAvailable() != 0) {
//        data += d->socket->readAll();
//    }

//    qDebug() << "DATA -> " << data;

//    QTextStream streamData(data);
//    QString line = streamData.readLine();

//    // parse header
//    while (!line.isEmpty()) {
//        // TODO store "Content-Type"

//        // determine request type
//        if (line.contains("HTTP")) {
//            QStringList requestSplit = line.split(' ', QString::SkipEmptyParts);

//            // first part of the split contains the request type
//            QString reqTypeStr = requestSplit.first();

//            if (reqTypeStr == "GET") {
//                d->requestType = GETRequestType;
//            } else if (reqTypeStr == "POST") {
//                d->requestType = POSTRequestType;
//            } else if (reqTypeStr == "PUT") {
//                d->requestType = PUTRequestType;
//            } else {
//                d->requestType = UnknownRequestType;
//                qDebug("[ConnectionHandler::parseData] UnknownRequestType not handled");

//                d->httpStatusCode = HttpBadRequest;

//                // respond to request
//                d->socket->write(httpStatusCodeToString().toUtf8());
//                d->socket->close();
//                return;
//            }

//            // second part contains the collection to call
//            if (d->requestType == GETRequestType) {
//                // the GET might have url parameters as well. Check
//                QStringList urlSplit = requestSplit.at(1).split('?');
//                d->requestUrl = urlSplit.first();
//                checkTrailingSlash();

//                if (urlSplit.count() > 1) {
//                    for (const QString &param : urlSplit.value(1).split('&')) {
//                        d->requestParameters.insert(param.split('=').first(), param.split('=').last());
//                    }
//                }
//            } else {
//                d->requestUrl = requestSplit.at(1);
//                checkTrailingSlash();

//                // post/put data comes after a new line break which is what makes the while loop exit.
//                // so the parsing is done outside
//            }
//        }

//        line = streamData.readLine();
//    }

//    // post/put data. Saved "as is" so that developers can handle the data as they wish
//    d->requestData = streamData.readLine().toUtf8();

//    qDebug() << "REQ DATA: " << d->requestData;


//    // now handle the request url
//    QString guessedResource = d->requestUrl.split('/').last();
//    QString requestUrlWithoutResource = d->requestUrl.left(d->requestUrl.indexOf("/" + guessedResource));

//    qDebug() << "REQ URL: " << d->requestUrl;
//    qDebug() << "REQ PAR: " << d->requestParameters;
//    qDebug() << "REQ DATA: " << d->requestData;
//    qDebug() << "GUESSED : " << guessedResource;


//    qDebug() << "My collections are: " << d->collections.keys();

//    // call collection
//    if (d->collections.contains(d->requestUrl)) {
//        callCollection(d->requestUrl);
//    } else if (d->collections.contains(requestUrlWithoutResource)) {
//        callCollection(requestUrlWithoutResource, guessedResource);
//    } else {
//        // ERROR
//        // TODO return bad request/not handled/bla bla bla
//        qDebug("TODO return bad request/not handled/bla bla bla");

//        // respond to request
//        d->httpStatusCode = HttpBadRequest;
//        d->socket->write(httpStatusCodeToString().toUtf8());
//        d->socket->close();
//    }


//    if (d->socket->isOpen()) {
//        d->socket->close();
//    }

//    return;
//}

//void ConnectionHandler::setHttpStatusCode(ConnectionHandler::HttpStatusCode code)
//{
//    d->httpStatusCode = code;
//}

}


