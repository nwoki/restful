#include "request.h"
#include "requestparser.h"

#include <QtCore/QDateTime>

#include <QtNetwork/QTcpSocket>


namespace RESTFul {

class Request::Private
{
public:
    Private()
        : parser(new RequestParser)
        , socket(nullptr)
        , status(ResponseStatusCode::NOT_FOUND)
        , type(RequestType::UNHANDLED)
    {}

    ~Private()
    {
        if (socket && socket->isOpen()) {
            socket->close();
            delete socket;
        }

        delete parser;
    }


    QByteArray data;
    QHash<QString, QString> headers;
    RequestParser *parser;
    QString path;
    QTcpSocket *socket;
    Request::ResponseStatusCode status;
    Request::RequestType type;
};


Request::Request(QTcpSocket *socket, QObject *parent)
    : QObject(parent)
    , d(new Private)
{
    d->socket = socket;

    connect(d->socket, &QTcpSocket::readyRead, this, &Request::parseRequest);
}

Request::~Request()
{
    qDebug("[Request::~Request]");
    delete d;
}

QByteArray Request::data() const
{
    return d->data;
}

void Request::sendResponse(const QByteArray &response)
{
    d->socket->write(prepareResponse(response));
    d->socket->close();

    Q_EMIT finished();
}

void Request::parseRequest()
{
    QByteArray data(d->socket->readAll());

    qDebug() << "SOCKET DATA INCOME: " << data;
    d->parser->parse(this, data);

    switch (d->type) {
    case GET:
        Q_EMIT get(d->path, d->data);
        break;
    case POST:
        Q_EMIT post(d->path, d->data);
        break;
    case PUT:
        Q_EMIT put(d->path, d->data);
        break;
    default:
        break;
    }
}

QByteArray Request::prepareResponse(const QByteArray &responseData)
{
    QByteArray dataToSend;

    dataToSend.append(statusCodeToString());
    dataToSend.append("Date:" + QDateTime::currentDateTime().toString("ddd, d MMMM yyyy HH:mm:ss t") + "\r\n");
    dataToSend.append("Connection: close\r\n");
    dataToSend.append("Content-Type: \"text/json\"\r\n");
//    dataToSend.append(QString("Content-Length: %1\r\n").arg(response.length()));
    dataToSend.append("\r\n");
    dataToSend.append(responseData);
    dataToSend.append("\r\n\r\n");

    return dataToSend;
}

void Request::setData(const QByteArray &data)
{
    d->data = data;
}

void Request::setHeader(const QString &headerKey, const QString &headerValue)
{
    d->headers.insert(headerKey, headerValue);
}

void Request::setPath(const QString &path)
{
    d->path = path;
}

void Request::setStatusCode(ResponseStatusCode status)
{
    d->status = status;
}

void Request::setType(const QString &type)
{
    d->type = typeFromString(type);
}

Request::RequestType Request::typeFromString(const QString &str)
{
    RequestType type = UNHANDLED;

    if (str == QStringLiteral("GET")) {
        type = GET;
    } else if (str == QStringLiteral("POST")) {
        type = POST;
    } else if (str == QStringLiteral("PUT")) {
        type = PUT;
    }

    return type;
}

QByteArray Request::statusCodeToString() const
{
    switch (d->status) {
        case ResponseStatusCode::OK:
            return "HTTP/1.1 200 OK\r\n";
            break;
        case ResponseStatusCode::BAD_REQUEST:
            return "HTTP/1.1 400 Bad Request\r\n";
            break;
        case ResponseStatusCode::NOT_FOUND:
            return "HTTP/1.1 404 Not Found\r\n";
            break;
        default:
            return "HTTP/1.1 404 Not Found\r\n";
    }
}

Request::RequestType Request::type() const
{
    return d->type;
}

}   // RESTFul
