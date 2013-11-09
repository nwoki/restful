#ifndef COLLECTION_H
#define COLLECTION_H

#include <QStringList>

class Resource;

class Collection
{
public:
    Collection(const QString &path, const QStringList &resourceList = QStringList());
    virtual ~Collection();

    QString path() const;

private:
    class Private;
    Private * const d;
};


#endif  // COLLECTION_H
