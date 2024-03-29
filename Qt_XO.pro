
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_XO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    cellbutton.cpp \
    gamesettings.cpp \
    server.cpp \
    servergame.cpp

HEADERS  += mainwindow.h \
    game.h \
    cellbutton.h \
    gamesettings.h \
    server.h \
    servergame.h

FORMS    += mainwindow.ui \
    gamesettings.ui
