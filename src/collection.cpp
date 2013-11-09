#include "collection.h"

class Collection::Private
{
public:
    Private() {};

    QString path;
    QStringList resourceList;
};


Collection::Collection(const QString &path, const QStringList &resourceList)
    :d (new Private)
{
    d->path = path;
    d->resourceList = resourceList;
}


Collection::~Collection()
{
    delete d;
}


QString Collection::path() const
{
    return d->path;
}
