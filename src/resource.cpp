#include "resource.h"

namespace RESTFul {

class Resource::Private
{
public:
    Private(const QString &resId) : id(resId) {}

    QString id;
};


Resource::Resource(const QString &resId, QObject *parent)
    : QObject(parent)
    , d(new Private(resId))
{
}


Resource::~Resource()
{
    delete d;
}

QString Resource::id() const
{
    return d->id;
}

}
