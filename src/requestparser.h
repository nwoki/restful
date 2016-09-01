#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <QtCore/QObject>


namespace RESTFul {


class Request;

/**
 * @brief The RequestParser class
 * @author Francesco Nwokeka <francesco.nwokeka@gmail.com>
 *
 * Parse to handle incoming data from clients
 */

class RequestParser : public QObject
{
    Q_OBJECT

public:
    explicit RequestParser(QObject *parent = nullptr);
    ~RequestParser();

    void parse(Request *request, const QByteArray &data);

private:
    class Private;
    Private * const d;
};

}   // RESTFul

#endif // REQUESTPARSER_H
