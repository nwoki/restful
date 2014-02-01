#include "mycollection.h"

#include <QtCore/QDebug>

MyCollection::MyCollection(const QString& path): Collection(path)
{

}


MyCollection::~MyCollection()
{

}


QByteArray MyCollection::collectionGet(const QString &resource)
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

QByteArray MyCollection::collectionPost(const QString& resource)
{
    return QByteArray("Requested POST");
}

QByteArray MyCollection::collectionPut(const QString& resource)
{
    return QByteArray("Requested PUT");
}

