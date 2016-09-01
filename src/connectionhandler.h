#ifndef RESTFUL_CONNECTIONHANDLER_H
#define RESTFUL_CONNECTIONHANDLER_H

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
class Request;


class ConnectionHandler : public QObject
{
    Q_OBJECT

public:
    ConnectionHandler(QObject *parent = 0);
    ~ConnectionHandler();

    /**
     * sets the REST url to respond to.(without the domain)
     * For example: "/urbanterror/people
     */
    void addCollection(Collection *collection);

public Q_SLOTS:
    void onRequest(const QString &path, const QByteArray &data);
//    void onGetRequest(/*Request *req,*/ const QString &path);
//    void onPostRequest(const QString &path, const QByteArray &data);
//    void onPutRequest(const QString &path, const QByteArray &data);

private:
    class Private;
    Private * const d;
};

}   // RESTFul


#endif  // RESTFUL_CONNECTIONHANDLER_H
