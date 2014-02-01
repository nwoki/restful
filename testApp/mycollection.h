#include <Collection>

class MyCollection : public Collection
{
public:
    MyCollection(const QString& path);
    virtual ~MyCollection();

    QByteArray collectionGet(const QString &resource = QString());
    QByteArray collectionPost(const QString &resource = QString());
    QByteArray collectionPut(const QString &resource = QString());
};
