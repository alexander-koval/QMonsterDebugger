#include "MainMediator.h"
#include <QQuickWidget>
#include <QQmlEngine>
#include <QQmlComponent>
#include <stream/sessions/session.h>
#include "stream/MessagePack.h"
#include "stream/constants.h"
#include "panels/TraceModel.h"
#include "models/ConnectionModel.h"
#include "Repo.h"

namespace monster {

MainMediator::MainMediator()
    : QObject(), m_mainView(), m_traceModels(), m_session() {

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

    ConnectionModel* connectionModel = Repo::connectionModel();
    int count = connectionModel->rowCount();
    connectionModel->insertRow(count);
    QModelIndex index = connectionModel->index(count);
    connectionModel->setData(index, session->fileTitle(), ConnectionItem::Name);

    TraceModelPtr model = QSharedPointer<TraceModel>::create();
    model->insertRow(model->rowCount());
    model->insertColumn(model->columnCount());
    model->setData(model->index(0, 0), 777, TraceItem::Line);
    m_traceModels.append(model);
    emit sessionCreated(session->fileTitle());
}

void MainMediator::onInboundMessage(MessagePack &message) {
    amf::AmfObject& item = message.getData().as<amf::AmfObject>();
    const amf::AmfString& cmd = item.getDynamicProperty<amf::AmfString>("command");
    if (cmd.value == COMMAND_BASE) {
        int kkk = 0;
    }
    qDebug() << "MESSAGE: " << cmd.value.c_str();
}

QObject* MainMediator::model(int index) {
    return m_traceModels.at(index).get();
}

}
