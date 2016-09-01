#include "request.h"
#include "requestparser.h"

#include <QtCore/QDebug>

namespace RESTFul {


class RequestParser::Private
{
public:
    Private() {}
    ~Private() {}
};


RequestParser::RequestParser(QObject *parent)
    : QObject(parent)
    , d(new Private)
{
}

RequestParser::~RequestParser()
{
    delete d;
}

void RequestParser::parse(Request *request, const QByteArray &data)
{
//    GET / HTTP/1.1\r\nUser-Agent: curl/7.35.0\r\nHost: localhost:8080\r\nAccept: */*\r\n\r\n

//    GET -> req type
//    / 	-> path to api
    Q_UNUSED (request);

    // use QString for text operations
    QString strData(data);

    for (const QString &str : strData.split("\r\n", QString::SkipEmptyParts)) {
        if (str.contains("HTTP")) {
            // get req type
            QStringList list = str.split(" ");
            request->setType(list.at(0));
            request->setPath(list.at(1));
//            request->setProtocol(list.at(2)); // don't need this ?
        }
    }
}

}   // RESTFul
