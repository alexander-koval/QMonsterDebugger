#include "MainMediator.h"
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlComponent>
#include <stream/sessions/session.h>
#include "stream/MessagePack.h"

namespace monster {

MainMediator::MainMediator()
    : QObject(), m_mainView(), m_session() {

}

void MainMediator::init(QObject *mainView) {
    m_mainView = mainView;
}

void MainMediator::onShowOptionsDialog() {

}

void MainMediator::onSessionCreated(MainMediator::SessionPtr session) {
    m_session = session;
    connect(session.data(), &Session::inboundMessage,
           this, &MainMediator::onInboundMessage);
    emit sessionCreated(session->fileTitle());
}

void MainMediator::onInboundMessage(MessagePack &message) {
    amf::AmfObject& item = message.getData().as<amf::AmfObject>();
    const amf::AmfString& cmd = item.getDynamicProperty<amf::AmfString>("command");
    qDebug() << "MESSAGE: " << cmd.value.c_str();
}

}
