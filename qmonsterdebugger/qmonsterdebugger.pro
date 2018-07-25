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

VPATH += src
INCLUDEPATH += src
SOURCES += main.cpp\
    MainWindow.cpp \
    MonsterTabWidget.cpp \
    DebuggerInfo.cpp \
    panels/traceitem.cpp \
    panels/tracemodel.cpp \
    streaming/sessions/sessions.cpp \
    streaming/sessions/session.cpp \
    streaming/monsterserver.cpp \
    streaming/socket/socketapplication.cpp \
    streaming/applicationstreamer.cpp \
    panels/streamview.cpp \
    panels/traceview.cpp

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
    streaming/applicationstreamer.h \
    panels/streamview.h \
    panels/traceview.h

FORMS    += forms/MainWindow.ui \
    forms/streamview.ui \
    forms/TraceView.ui


MOC_DIR = autogen

include(config/qmake-target-platform.pri)
include(config/qmake-destination-path.pri)

DESTDIR = $PWD/../bin/$$DESTINATION_PATH
OBJECTS_DIR = $PWD/..//bin/$$DESTINATION_PATH/.obj
MOC_DIR = $PWD/../bin/$$DESTINATION_PATH/.moc
RCC_DIR = $PWD/../bin/$$DESTINATION_PATH/.qrc
UI_DIR = $PWD/../bin/$$DESTINATION_PATH/.ui
#MAKEFILE = $PWD/../../bin/$$DESTINATION_PATH/.makefile

LIBS += -L$$PWD/../bin/$$DESTINATION_PATH
