#ifndef REQUEST_H
#define REQUEST_H

#include <QtCore/QObject>

class QTcpSocket;


namespace RESTFul {

/**
 * @brief The Request class
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 *
 * The Request class is used to handle the single requests from clients.
 */
class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QTcpSocket *socket, QObject *parent = nullptr);
    ~Request();

Q_SIGNALS:
    /** called when the request has finished its lifecycle (after having sent a response to the client) */
    void finished();

private Q_SLOTS:
    /** parses the http request */
    void parseRequest();

private:
    class Private;
    Private * const d;
};

}   // RESTFul

#endif // REQUEST_H
