#include "Core.h"
#include "panels/TraceModel.h"
#include "models/SessionDataModel.h"
#include "stream/MonsterServer.h"
#include "stream/MessagePack.h"
#include "stream/constants.h"

namespace monster {

static Core* _core;
static MonsterServerPtr _server;
static SessionDataModelPtr _sessions;

Core::Core()
    : QObject() {
}

void Core::start() {
    _core = new Core();
    _server = MonsterServerPtr::create();
    _sessions = SessionDataModelPtr::create();

    if (_server->start()) {
        connect(_server.data(), &MonsterServer::sessionCreated,
                _core, &Core::onSessionCreated, Qt::DirectConnection);
    } else {
        qCritical() << "Unable to start server";
    }
}

void Core::onSessionCreated(SessionPtr session) {
    connect(session.data(), &Session::inboundMessage,
            this, &Core::onInboundMessage);
    int count = _sessions->rowCount();
    _sessions->insertRow(count);
    QModelIndex index = _sessions->index(count);
    QVariant variant;
    variant.setValue(session.data());
    _sessions->setData(index, variant, SessionProxy::Session);
}

void Core::onInboundMessage(MessagePack &message) {
    amf::AmfObject& item = message.getData().as<amf::AmfObject>();
    const amf::AmfString& cmd = item.getDynamicProperty<amf::AmfString>("command");
    if (cmd.value == COMMAND_BASE) {
        int kkk = 0;
    }
    qDebug() << "MESSAGE: " << cmd.value.c_str();
}

Core& Core::core() {
    return *_core;
}

MonsterServerPtr Core::server() {
    return _server;
}

SessionDataModelPtr Core::sessions() {
    return _sessions;
}


}
