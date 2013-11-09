#include "resource.h"

class Resource::Private
{
public:
    Private(const QString &resId) : id(resId) {}

    QString id;
};


Resource::Resource(const QString &resId)
    : d(new Private(resId))
{
}


Resource::~Resource()
{
    delete d;
}
