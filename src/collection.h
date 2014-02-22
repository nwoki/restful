#ifndef COLLECTION_H
#define COLLECTION_H

#include "connectionhandler.h"

#include <QtCore/QString>
#include <QtCore/QVariant>

namespace RESTFul {

class Collection
{
public:
    Collection(const QString &path);
    virtual ~Collection();

    QString path() const;

    virtual QByteArray collectionGet(const QString &resource = QString(), const QVariantHash &parameters = QVariantHash());
    virtual QByteArray collectionPost(const QByteArray &data,   const QString &resource = QString());
    virtual QByteArray collectionPut(const QByteArray &data, const QString &resource = QString());

    ConnectionHandler::HttpStatusCode httpStatusCode() const;

protected:
    void setHttpStatusCode(ConnectionHandler::HttpStatusCode statusCode);

private:
    class Private;
    Private * const d;
};

};


#endif  // COLLECTION_H
