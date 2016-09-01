#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include <RESTFul/Server>

#include "mycollection.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    RESTFul::Server server(8080);
    qDebug() << "SERVER STATUS: " << server.start();

//     server.addRESTUrl("bla bla", ResourceHandler);

//    server.addCollection(new MyCollection("/test"));
    server.addCollection(new MyCollection("/"));


    return app.exec();
}
