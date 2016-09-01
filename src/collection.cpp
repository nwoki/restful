#include "collection.h"

namespace RESTFul {

class Collection::Private
{
public:
    Private()
        : httpStatusCode(ConnectionHandler::HttpNotFound)
    {}

    ~Private() {}


    /* basically the REST endpoint (API) that will be available on the http server */
    QString path;
    ConnectionHandler::HttpStatusCode httpStatusCode;
};



Collection::Collection(const QString &path)
    :d (new Private)
{
    d->path = path;
}

Collection::~Collection()
{
    delete d;
}

QByteArray Collection::collectionGet(const QString &resource, const QVariantHash &parameters)
{
    return QByteArray();
}

QByteArray Collection::collectionPost(const QByteArray &data, const QString &resource)
{
    return QByteArray();
}

QByteArray Collection::collectionPut(const QByteArray &data, const QString &resource)
{
    return QByteArray();
}

ConnectionHandler::HttpStatusCode Collection::httpStatusCode() const
{
    return d->httpStatusCode;
}

QString Collection::path() const
{
    return d->path;
}

void Collection::setHttpStatusCode(ConnectionHandler::HttpStatusCode statusCode)
{
    d->httpStatusCode = statusCode;
}

}
