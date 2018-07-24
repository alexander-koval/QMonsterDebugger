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

INCLUDEPATH += src
SOURCES += src/main.cpp\
    src/MainWindow.cpp \
    src/MonsterTabWidget.cpp \
    src/DebuggerInfo.cpp \
    src/panels/traceitem.cpp \
    src/panels/tracemodel.cpp \
    src/streaming/sessions/sessions.cpp \
    src/streaming/sessions/session.cpp \
    src/streaming/monsterserver.cpp \
    src/streaming/socket/socketapplication.cpp \
    src/streaming/applicationstreamer.cpp \
    src/panels/streamview.cpp \
    src/panels/traceview.cpp

HEADERS  += src/MainWindow.hpp \
    src/MonsterTabWidget.hpp \
    src/DebuggerInfo.hpp \
    src/panels/traceitem.h \
    src/panels/tracemodel.h \
    src/streaming/sessions/sessions.h \
    src/streaming/sessions/session.h \
    src/streaming/monsterserver.h \
    src/streaming/debuggable.h \
    src/streaming/socket/socketapplication.h \
    src/streaming/applicationstreamer.h \
    src/panels/streamview.h \
    src/panels/traceview.h

FORMS    += forms/MainWindow.ui \
    forms/traceview.ui \
    forms/streamview.ui


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
