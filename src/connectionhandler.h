#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QtCore/QHash>
#include <QtCore/QObject>

class Collection;
class QTcpSocket;


/**
 * @brief Handles the ReST connections the http server receives
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 *
 * This class is used to handle incoming requests from clients. It parses the data received
 * from the socket and calls the correct function on the correct collection.
 */

namespace RESTFul {

class Collection;

class ConnectionHandler : public QObject
{
    Q_OBJECT

public:
    enum HttpRequestType {
        GETRequestType = 0,
        POSTRequestType,
        PUTRequestType,
        UnknownRequestType
    };

    enum HttpStatusCode {
        HttpOk = 200,
        HttpBadRequest = 400,
        HttpNotFound = 404,
    };

    ConnectionHandler(QTcpSocket *socket, QHash<QString, Collection*> collections, QObject *parent = 0);
    virtual ~ConnectionHandler();

    void setHttpStatusCode(HttpStatusCode code);

private:
    QString httpStatusCodeToString() const;
    void parseData();

    class Private;
    Private * const d;
};

};


#endif  // CONNECTIONHANDLER_H
