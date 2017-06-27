#-------------------------------------------------
#
# Project created by QtCreator 2017-06-27T18:31:04
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qmonsterdebugger
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MonsterTabWidget.cpp

HEADERS  += MainWindow.hpp \
    MonsterTabWidget.hpp

FORMS    += MainWindow.ui
