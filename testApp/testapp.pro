TEMPLATE = app
TARGET = testApp
CONFIG += c++11 console

QT += core network

ROOTDIR  = $$IN_PWD/..

OBJECTS_DIR = .obj
UI_DIR = .ui
MOC_DIR = .moc
RCC_DIR = .rcc

HEADERS += $$PWD/mycollection.h
#           $$PWD/myresource.h

SOURCES += $$PWD/mycollection.cpp \
#           $$PWD/myresource.cpp \
           $$PWD/main.cpp

INCLUDEPATH += $$ROOTDIR/include


## used for in-source compiling. Devs point to this folder when compiling the lib in their
## project. Keeps the code cleaner imho
#OTHER_FILES += \
#    $$PWD/../include/RESTFul/Collection \
#    $$PWD/../include/RESTFul/Resource \
#    $$PWD/../include/RESTFul/Server


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -lrestful
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -lrestful
else:unix:!macx: LIBS += -L$$PWD/../lib/ -lrestful

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
