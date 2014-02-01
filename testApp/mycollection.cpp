#include "mycollection.h"

MyCollection::MyCollection(const QString& path): Collection(path)
{

}


MyCollection::~MyCollection()
{

}


QByteArray MyCollection::collectionGet(const QString &resource)
{

    if (resource.isEmpty()) {
        qDebug("return entire collection");
    } else {
        qDebug("return resource");
    }

    return QByteArray("asdasdasda");
}
