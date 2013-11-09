#ifndef RESOURCE_H
#define RESOURCE_H

#include <QtCore/QByteArray>
#include <QtCore/QString>

class Resource
{
public:
    Resource(const QString &resId);
    virtual ~Resource();

    // TODO add QVariantHash to post/put methods (vars)
    virtual QByteArray restGet() = 0;
    virtual void restDelete() = 0;
    virtual void restPost() = 0;
    virtual void restPut() = 0;

private:
    class Private;
    Private * const d;
};

#endif  // RESOURCE_H
