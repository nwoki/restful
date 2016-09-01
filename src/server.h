#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>

/**
 * @brief Main server that accepts HTTP connections and handles various http requests
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 */

namespace RESTFul {

class Collection;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Q_DECL_EXPORT Server(quint16 port, QObject *parent = 0);
    Q_DECL_EXPORT virtual ~Server();

    /**
     * @brief listen
     * starts listening for incoming connections
     *
     * @return the result of the binding
     */
    Q_DECL_EXPORT bool start();

    /**
     * sets the REST url to respond to.(without the domain)
     * For example: "/urbanterror/people
     */
    Q_DECL_EXPORT void addCollection(Collection *collection);

private Q_SLOTS:
    void onRequestFinished();

private:
    class Private;
    Private * const d;
};

}   // RESTFul



#endif  // SERVER_H
