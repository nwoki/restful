#ifndef CONNECTIONHANDLER_H
#define CONNECTIONHANDLER_H

#include <QtCore/QObject>

class QTcpSocket;


/**
 * @brief Handles the ReST connections the http server receives
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 */
class ConnectionHandler : public QObject
{
    Q_OBJECT

public:
    enum HttpRequestType {
        GETRequestType = 0,
        POSTRequestType,
        PUTRequestType
    };

    ConnectionHandler(QTcpSocket *socket, QObject *parent = 0);
    virtual ~ConnectionHandler();

private:
    void parseData();

    class Private;
    Private * const d;
};



#endif  // CONNECTIONHANDLER_H
