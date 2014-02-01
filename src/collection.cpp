#include "collection.h"
#include "resource.h"
#include "resourcefactory.h"

#include <QtCore/QDebug>

class Collection::Private
{
public:
    Private() {};

    QString path;

Q_SIGNALS:
    void finished();
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


QString Collection::path() const
{
    return d->path;
}
