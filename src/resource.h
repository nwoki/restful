#ifndef RESOURCE_H
#define RESOURCE_H

#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariantHash>

namespace RESTFul {

class Resource : public QObject
{
public:
    Resource(const QString &resId, QObject *parent = 0);
    virtual ~Resource();

    QString id() const;

    virtual void restGet(const QVariantHash vars) = 0;
    virtual void restDelete(const QVariantHash vars) = 0;
    virtual void restPost(const QVariantHash vars) = 0;
    virtual void restPut(const QVariantHash vars) = 0;

private:
    class Private;
    Private * const d;
};

};

#endif  // RESOURCE_H
