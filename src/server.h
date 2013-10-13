#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>


/**
 * @brief Main server that accepts HTTP connections and handles various http requests
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 */

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(quint16 port, QObject *parent = 0);
    virtual ~Server();


private:
    class Private;
    Private * const d;
};



#endif  // SERVER_H
