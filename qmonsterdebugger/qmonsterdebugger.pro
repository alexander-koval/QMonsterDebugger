#-------------------------------------------------
#
# Project created by QtCreator 2017-06-27T18:31:04
#
#-------------------------------------------------

QT       += core gui network
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qmonsterdebugger
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MonsterTabWidget.cpp \
    DebuggerInfo.cpp \
    panels/traceitem.cpp \
    panels/tracemodel.cpp \
    streaming/sessions/sessions.cpp \
    streaming/monsterserver.cpp \
    streaming/socket/socketapplication.cpp \
    streaming/applicationstreamer.cpp \
    streaming/sessions/session.cpp

HEADERS  += MainWindow.hpp \
    MonsterTabWidget.hpp \
    DebuggerInfo.hpp \
    panels/traceitem.h \
    panels/tracemodel.h \
    streaming/sessions/sessions.h \
    streaming/sessions/session.h \
    streaming/monsterserver.h \
    streaming/debuggable.h \
    streaming/socket/socketapplication.h \
    streaming/applicationstreamer.h

FORMS    += MainWindow.ui \
    traceview.ui
