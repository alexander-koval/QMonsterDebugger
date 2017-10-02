#include "monsterserver.h"
#include <QMessageBox>
#include <QTcpSocket>
#include <QThread>
#include <memory>
#include "sessions/session.h"
#include "sessions/sessions.h"

class MonsterThread : public QThread {
    using SessionsPtr = std::shared_ptr<Sessions>;
public:
    explicit MonsterThread(qintptr descriptor, SessionsPtr sessins, QObject* parent = nullptr)
        : QThread(parent),
          m_descriptor(descriptor),
          m_socket(),
          m_session() {

    }

    virtual void run() override {
        m_socket = new QTcpSocket(this);
        if (m_socket->setSocketDescriptor(m_descriptor)) {
            m_session = std::make_unique<Session>(m_socket);
        }
    }

private:
    qintptr m_descriptor;
    QTcpSocket* m_socket;

    std::unique_ptr<Session> m_session;
};

MonsterServer::MonsterServer(QObject* parent /*= nullptr*/)
    : QTcpServer(parent),
      m_sessions(std::make_unique<Sessions>()) {

}

MonsterServer::~MonsterServer() {
    qDebug("%s", "DESTROY");
//    if (m_threads.begin() != m_threads.end()) {
//        std::for_each(m_threads.begin(), m_threads.end(),
//                      [](const std::pair<qintptr, QThread*>& pair){
//            pair.second->quit();
//            pair.second->wait();
//        });
//    }
}

bool MonsterServer::start(int port /*= 5840*/) {
    bool result = listen(QHostAddress::LocalHost, port);
    if (!result) { close(); }
    return result;
}

void MonsterServer::incomingConnection(qintptr handle) {
//    MonsterThread* thread = new MonsterThread(handle, this);
//    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
//    thread->start();
}
