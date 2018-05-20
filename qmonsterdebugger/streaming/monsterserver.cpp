#include "monsterserver.h"
#include <QPointer>
#include <QMessageBox>
#include "MainWindow.hpp"
#include "sessions/session.h"
#include "sessions/sessions.h"

namespace monster {

MainWindow* g_window = nullptr;

MonsterThread::MonsterThread(SessionPtr session, SessionsWPtr sessions, QObject *parent)
    : QThread(parent),
      m_session(session),
      m_sessions(sessions) {

}

void MonsterThread::run() {
    const QTcpSocket* socket = m_session->socket();
    connect(socket, SIGNAL(readyRead()),    this, SLOT(onReadyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);

    SessionsPtr sessions = m_sessions.toStrongRef();
    if (sessions) {
        sessions->add(m_session.toWeakRef());
    }
    exec();
}

void MonsterThread::onReadyRead() {
    qDebug("READY_READ");
}

void MonsterThread::onDisconnected() {
    qDebug("DISCONNECTED");
}

MonsterServer::MonsterServer(QObject* parent /*= nullptr*/)
    : QTcpServer(parent),
      m_sessions(SessionsPtr::create(this)) {

}

MonsterServer::~MonsterServer() {
    qDebug("%s", "DESTROY");
    if (m_threads.begin() != m_threads.end()) {
        std::for_each(m_threads.begin(), m_threads.end(),
                      [](const QPointer<QThread>& thread){
            thread->quit();
            thread->wait();
        });
    }
}

bool MonsterServer::start(quint16 port /*= 5840*/) {
    bool result = listen(QHostAddress::LocalHost, port);
    if (!result) { close(); }
    return result;
}

void MonsterServer::incomingConnection(qintptr handle) {
    Base::incomingConnection(handle);
    if (hasPendingConnections()) {
        QTcpSocket* socket = nextPendingConnection();
        SessionPtr session = SessionPtr::create(socket);
        QPointer<QThread> thread = new MonsterThread(session, m_sessions.toWeakRef(), this);
        connect(thread, &QThread::finished, thread.data(), &QObject::deleteLater);
        m_threads.append(thread);
        thread->start();
    }
}

void reset_main_window(monster::MainWindow *window) {
    monster::g_window = window;
}

MainWindow& get_main_window() {
    return *monster::g_window;
}

}
