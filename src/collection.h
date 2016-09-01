#ifndef COLLECTION_H
#define COLLECTION_H

#include "connectionhandler.h"

#include <QtCore/QString>
#include <QtCore/QVariant>

namespace RESTFul {

class Collection
{
public:
    Q_DECL_EXPORT Collection(const QString &path);
    Q_DECL_EXPORT virtual ~Collection();

    Q_DECL_EXPORT QString path() const;

    Q_DECL_EXPORT virtual QByteArray collectionGet(const QString &resource = QString(), const QVariantHash &parameters = QVariantHash());
    Q_DECL_EXPORT virtual QByteArray collectionPost(const QByteArray &data,   const QString &resource = QString());
    Q_DECL_EXPORT virtual QByteArray collectionPut(const QByteArray &data, const QString &resource = QString());

private:
    class Private;
    Private * const d;
};

}   // RESTFul


#endif  // COLLECTION_H
