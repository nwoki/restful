#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QtCore/QHash>
#include <QtCore/QObject>

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

    ConnectionHandler(QObject *parent = 0);
    ~ConnectionHandler();

    /**
     * sets the REST url to respond to.(without the domain)
     * For example: "/urbanterror/people
     */
    void addCollection(Collection *collection);

//    void setHttpStatusCode(HttpStatusCode code);

private:

//    /**
//     * as there's no way of telling if the url is pointing to a resource on a collection
//     * or to the whole collection, I have to check for the url validity
//     *
//     * if the full url is not contained in the hash, then MAYBE the last part of the
//     * url (after the last '/') is the resource. So I try checking if the hash contains the
//     * url without the last part.
//     *
//     * If both tries fail, then the url is not contained in the hash
//     */
//    void callCollection(const QString &requestUrl = QString(), const QString &resource = QString());
//    QString httpStatusCodeToString() const;

//    /** parsed the incoming data from the http request */
//    void parseData();


    class Private;
    Private * const d;
};

}   // RESTFul


#endif  // CONNECTIONHANDLER_H
