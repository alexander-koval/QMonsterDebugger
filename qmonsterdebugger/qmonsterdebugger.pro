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
    debugger/sessions/sessions.cpp \
    debugger/monsterserver.cpp

HEADERS  += MainWindow.hpp \
    MonsterTabWidget.hpp \
    DebuggerInfo.hpp \
    panels/traceitem.h \
    panels/tracemodel.h \
    debugger/sessions/sessions.h \
    debugger/sessions/session.h \
    debugger/monsterserver.h

FORMS    += MainWindow.ui \
    traceview.ui
