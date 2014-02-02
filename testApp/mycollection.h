#include <RESTFul/Collection>

class MyCollection : public RESTFul::Collection
{
public:
    MyCollection(const QString& path);
    virtual ~MyCollection();

    QByteArray collectionGet(const QString &resource = QString());
};
