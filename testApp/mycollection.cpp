#include "mycollection.h"

#include <QtCore/QDebug>

MyCollection::MyCollection(const QString& path): Collection(path)
{

}


MyCollection::~MyCollection()
{

}


QByteArray MyCollection::collectionGet(const QString &resource, const QVariantHash &parameters)
{
    qDebug("[MyCollection::collectionGet]");

    qDebug() << "resource: " << resource;

    if (resource.isEmpty()) {
        qDebug("return entire collection");
    } else {
        qDebug("return resource");
    }

    return QByteArray("asdasdasda");
}
