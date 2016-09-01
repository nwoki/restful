#include "collection.h"
#include "connectionhandler.h"
#include "request.h"

#include <QtCore/QDebug>


namespace RESTFul {

class ConnectionHandler::Private
{
public:
    Private() {}
    ~Private() {}

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

void ConnectionHandler::onRequest(const QString &path, const QByteArray &data)
{
    Request *req = qobject_cast<Request*>(sender());

    if (!req) {
        qDebug() << "NO CAST AVAILABLE";
        return;
    }

    QByteArray collectionData;

    // look for the collection
    if (d->collections.contains(path)) {
        req->setStatusCode(Request::ResponseStatusCode::OK);

        switch (req->type()) {
        case Request::GET:
            collectionData = d->collections.value(path)->collectionGet();
            break;
        case Request::POST:
            collectionData = d->collections.value(path)->collectionPost(data);
            break;
        case Request::PUT:
            collectionData = d->collections.value(path)->collectionPut(data);
            break;
        }
    } else {
        req->setStatusCode(Request::ResponseStatusCode::NOT_FOUND);
    }

    req->sendResponse(collectionData);
}

//void ConnectionHandler::onPostRequest(const QString &path, const QByteArray &data)
//{
//    Q_UNUSED(path);
//    Q_UNUSED(data);
//}

//void ConnectionHandler::onPutRequest(const QString &path, const QByteArray &data)
//{
//    Q_UNUSED(path);
//    Q_UNUSED(data);
//}

}


