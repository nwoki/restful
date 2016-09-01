#ifndef COLLECTION_H
#define COLLECTION_H

#include "connectionhandler.h"

#include <QtCore/QString>
#include <QtCore/QVariant>

namespace RESTFul {

class Collection
{
public:
    Collection(const QString &path);
    virtual ~Collection();

    QString path() const;

    virtual QByteArray collectionGet(const QString &resource = QString(), const QVariantHash &parameters = QVariantHash());
    virtual QByteArray collectionPost(const QByteArray &data,   const QString &resource = QString());
    virtual QByteArray collectionPut(const QByteArray &data, const QString &resource = QString());

private:
    class Private;
    Private * const d;
};

}   // RESTFul


#endif  // COLLECTION_H
