#include "collection.h"
#include "resource.h"
#include "resourcefactory.h"

#include <QtCore/QDebug>


namespace RESTFul {

class Collection::Private
{
public:
    Private() {};

    QString path;
    ConnectionHandler::HttpStatusCode httpStatusCode;

Q_SIGNALS:
    void finished();
};


Collection::Collection(const QString &path)
    :d (new Private)
{
    d->path = path;
    d->httpStatusCode = ConnectionHandler::HttpOk;
}


Collection::~Collection()
{
    delete d;
}

QByteArray Collection::collectionGet(const QString &resource)
{
    setHttpStatusCode(ConnectionHandler::HttpNotFound);
    return QByteArray();
}

QByteArray Collection::collectionPost(const QString &resource)
{
    setHttpStatusCode(ConnectionHandler::HttpNotFound);
    return QByteArray();
}

QByteArray Collection::collectionPut(const QString &resource)
{
    setHttpStatusCode(ConnectionHandler::HttpNotFound);
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
