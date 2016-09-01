TEMPLATE = lib
TARGET = restful
CONFIG += c++11 shared

# NOTE
#
# If we want to use a dynamic lib and have the lib functions callable, we'll need to use:
#
#   __declspec(dllexport) void MyFunction();
#   class __declspec(dllexport) MyClass;
#
#   This is acheived with the QT macro: Q_DECL_EXPORT which makes the library portable

QT += core network

# outputs to the project root in the "lib" folder
ROOTDIR  = $$IN_PWD/..
DESTDIR += $$ROOTDIR/lib

OBJECTS_DIR = $$ROOTDIR/.obj
UI_DIR = $$ROOTDIR/.ui
MOC_DIR = $$ROOTDIR/.moc
RCC_DIR = $$ROOTDIR/.rcc

HEADERS += \
        $$PWD/collection.h \
        $$PWD/connectionhandler.h \
        $$PWD/request.h \
        $$PWD/requestparser.h \
        $$PWD/server.h

SOURCES += \
        $$PWD/collection.cpp \
        $$PWD/connectionhandler.cpp \
        $$PWD/request.cpp \
        $$PWD/requestparser.cpp \
        $$PWD/server.cpp



# used for in-source compiling. Devs point to this folder when compiling the lib in their
# project. Keeps the code cleaner imho
OTHER_FILES += \
    $$PWD/../include/RESTFul/Collection \
    $$PWD/../include/RESTFul/Resource \
    $$PWD/../include/RESTFul/Server
