#include <QtCore/QCoreApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Server server(8080);

//     server.addRESTUrl("bla bla", ResourceHandler);

    return app.exec();
}
