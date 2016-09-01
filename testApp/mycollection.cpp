#include "mycollection.h"

#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>

MyCollection::MyCollection(const QString& path)
    : Collection(path)
{
}

MyCollection::~MyCollection()
{
}

QByteArray MyCollection::collectionGet(const QString &resource, const QVariantHash &parameters)
{
    Q_UNUSED (parameters);

    QVariantMap root;
    QVariantMap data;

    data.insert("id", "TestJson");
    data.insert("text", "hello world!");

    root.insert("data", data);

    if (resource.isEmpty()) {
        qDebug("return entire collection");
    } else {
        qDebug("return resource");
    }

    return QJsonDocument::fromVariant(root).toJson();
}
