#include "collection.h"
#include "resource.h"
#include "resourcefactory.h"

#include <QtCore/QDebug>

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
