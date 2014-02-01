#include "collection.h"

class MyCollection : public Collection
{
public:
    MyCollection(const QString& path);
    virtual ~MyCollection();

    virtual QByteArray collectionGet(const QString &resource = QString());
};
