#ifndef RESTFUL_REQUEST_H
#define RESTFUL_REQUEST_H

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
    enum RequestType {
        GET = 0,
        POST,
        PUT,
        UNHANDLED
    };

    enum ResponseStatusCode {
        OK = 200,
        BAD_REQUEST = 400,
        NOT_FOUND = 404
    };


    explicit Request(QTcpSocket *socket, QObject *parent = nullptr);
    ~Request();

    QByteArray data() const;

    void sendResponse(const QByteArray &response);

    void setData(const QByteArray &data);
    void setHeader(const QString &headerKey, const QString &headerValue);
    void setPath(const QString &path);
    void setStatusCode(ResponseStatusCode status);
    void setType(const QString &type);

    QByteArray statusCodeToString() const;
    RequestType type() const;

Q_SIGNALS:
    /** called when the request has finished its lifecycle (after having sent a response to the client) */
    void finished();

    /**
     * emitted to request a GET from the collection handler. When the CollectionHandler receives this signal it
     * searches for the corrisponding API and writes back the response in the Request object
     */
    // TODO add args
    void get(const QString &path, const QByteArray &data);
    void post(const QString &path, const QByteArray &data);
    void put(const QString &path, const QByteArray &data);

private Q_SLOTS:
    /** parses the http request */
    void parseRequest();

private:
    QByteArray prepareResponse(const QByteArray &responseData);
    RequestType typeFromString(const QString &str);

    class Private;
    Private * const d;
};

}   // RESTFul

#endif // RESTFUL_REQUEST_H
