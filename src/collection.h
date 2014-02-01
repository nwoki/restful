#ifndef COLLECTION_H
#define COLLECTION_H

#include <QtCore/QString>
#include <QtCore/QVariant>

class Collection
{
public:
    Collection(const QString &path);
    virtual ~Collection();

    QString path() const;

    virtual QByteArray collectionGet(const QString &resource = QString()) = 0;

private:
    class Private;
    Private * const d;
};


#endif  // COLLECTION_H
