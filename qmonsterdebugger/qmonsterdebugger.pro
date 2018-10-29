#-------------------------------------------------
#
# Project created by QtCreator 2017-06-27T18:31:04
#
#-------------------------------------------------

QT       += core gui network widgets \
            qml quick quickwidgets quickcontrols2

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += xml widgets

TARGET = qmonsterdebugger
TEMPLATE = app

VPATH += src
INCLUDEPATH += src src/amf
SOURCES += main.cpp\
    MainWindow.cpp \
    MonsterTabWidget.cpp \
    stream/sessions/Sessions.cpp \
    stream/sessions/Session.cpp \
    stream/MonsterServer.cpp \
    panels/TraceItem.cpp \
    panels/TraceModel.cpp \
    panels/StreamView.cpp \
    panels/TraceView.cpp \
    stream/constants.cpp \
    stream/CommandProcessor.cpp \
    stream/MessagePack.cpp \
    amf/amfpacket.cpp \
    amf/deserializer.cpp \
    amf/serializationcontext.cpp \
    amf/serializer.cpp \
    amf/types/amfarray.cpp \
    amf/types/amfbool.cpp \
    amf/types/amfbytearray.cpp \
    amf/types/amfdate.cpp \
    amf/types/amfdictionary.cpp \
    amf/types/amfdouble.cpp \
    amf/types/amfinteger.cpp \
    amf/types/amfobject.cpp \
    amf/types/amfstring.cpp \
    amf/types/amfvector.cpp \
    amf/types/amfxml.cpp \
    amf/types/amfxmldocument.cpp \
    utils/AMFConverter.cpp \
    src/controllers/MainMediator.cpp \
    src/Repo.cpp \
    src/models/SessionDataModel.cpp \
    src/Core.cpp \
    src/utils/LoggerUtils.cpp

HEADERS  += MainWindow.h \
    MonsterTabWidget.h \
    stream/sessions/Sessions.h \
    stream/sessions/Session.h \
    stream/MonsterServer.h \
    panels/TraceItem.h \
    panels/TraceModel.h \
    panels/StreamView.h \
    panels/TraceView.h \
    stream/constants.h \
    stream/CommandProcessor.h \
    stream/MessagePack.h \
    amf/amf.hpp \
    amf/amfpacket.hpp \
    amf/deserializer.hpp \
    amf/serializationcontext.hpp \
    amf/serializer.hpp \
    amf/types/amfarray.hpp \
    amf/types/amfbool.hpp \
    amf/types/amfbytearray.hpp \
    amf/types/amfdate.hpp \
    amf/types/amfdictionary.hpp \
    amf/types/amfdouble.hpp \
    amf/types/amfinteger.hpp \
    amf/types/amfitem.hpp \
    amf/types/amfnull.hpp \
    amf/types/amfobject.hpp \
    amf/types/amfstring.hpp \
    amf/types/amfundefined.hpp \
    amf/types/amfvector.hpp \
    amf/types/amfxml.hpp \
    amf/types/amfxmldocument.hpp \
    amf/utils/amfitemptr.hpp \
    amf/utils/amfobjecttraits.hpp \
    stream/StreamFwd.h \
    utils/AMFConverter.h \
    src/controllers/MainMediator.h \
    src/Repo.h \
    src/models/SessionDataModel.h \
    src/models/ModelsFwd.h \
    src/Core.h \
    src/utils/LoggerUtils.h

FORMS    += forms/MainWindow.ui \
    forms/StreamView.ui \
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

#TARGETPATH = $PWD/../bin/$$DESTINATION_PATH/.qmlc
LIBS += -L$$PWD/../bin/$$DESTINATION_PATH

DISTFILES += \
    resources/qml/MainView.qml

RESOURCES += \
    resources/qmonsterdebugger.qrc
