#include <QtCore/QCoreApplication>

#include <Server>

#include "mycollection.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Server server(8080);

//     server.addRESTUrl("bla bla", ResourceHandler);

    server.addCollection(new MyCollection("/test"));


    return app.exec();
}
