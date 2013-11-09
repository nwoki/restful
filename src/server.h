#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>

/**
 * @brief Main server that accepts HTTP connections and handles various http requests
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 */

class Collection;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(quint16 port, QObject *parent = 0);
    virtual ~Server();

    /**
     * sets the REST url to respond to.(without the domain)
     * For example: "/urbanterror/people
     */
    void addCollection(Collection *collection);


private:
    class Private;
    Private * const d;
};



#endif  // SERVER_H
