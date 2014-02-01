#ifndef COLLECTION_H
#define COLLECTION_H

#include "connectionhandler.h"

#include <QtCore/QString>
#include <QtCore/QVariant>

class Collection
{
public:
    Collection(const QString &path);
    virtual ~Collection();

    QString path() const;

    virtual QByteArray collectionGet(const QString &resource = QString()) = 0;
//     virtual QByteArray collectionPost(const QString &resource = QString()) = 0;
//     virtual QByteArray collectionPut(const QString &resource = QString()) = 0;

    ConnectionHandler::HttpStatusCode httpStatusCode() const;

private:
    void setHttpStatusCode(ConnectionHandler::HttpStatusCode statusCode);

    class Private;
    Private * const d;
};


#endif  // COLLECTION_H
