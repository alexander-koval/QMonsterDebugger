#include "MonsterServer.h"
#include <QPointer>
#include <QMessageBox>
#include "MainWindow.h"
#include "sessions/Session.h"
#include "sessions/Sessions.h"
#include "stream/constants.h"
#include "stream/CommandProcessor.h"

namespace monster {

MonsterThread::MonsterThread(SessionPtr session, SessionsWPtr sessions, QObject *parent)
    : QThread(parent),
      m_session(session),
      m_sessions(sessions) {

}

void MonsterThread::run() {
    SessionsPtr sessions = m_sessions.toStrongRef();
    if (sessions) {
        sessions->add(m_session.toWeakRef());
    }
    exec();
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
        connect(socket, &QTcpSocket::readyRead, this, &MonsterServer::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &MonsterServer::onDisconnect);
//        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
//                this, SLOT(onDisconnect(QAbstractSocket::SocketError)));
    }
}

void MonsterServer::onReadyRead() {
    uint32_t size;
    QBuffer buffer;
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray bytes = socket->readAll();
    buffer.open(QIODevice::ReadWrite);
    buffer.write(bytes);
    buffer.seek(0);

    if (buffer.bytesAvailable() == 0) return;
    QByteArray package;
    buffer.read(reinterpret_cast<char*>(&size), sizeof(uint32_t));
    QString command = buffer.buffer();
    if (command == "<policy-file-request/>") {
        QByteArray xml;
        CommandProcessor::policyRequest(&xml);
        qDebug() << "LENGTH: " << xml.length();
        socket->write(xml);
        socket->flush();
    } else if (command == LOGGER_ID) {
        QByteArray bytes;
        CommandProcessor::hello(&bytes);
        qDebug() << "BYTES: " << bytes;
        qDebug() << "LENGHT: " << bytes.size();
        QDataStream bytesStream(&package, QIODevice::WriteOnly);

        bytesStream << bytes;
        qDebug() << "PAC: " << package.size();
        bool result = socket->write(package) == package.size();
        socket->flush();
        qDebug() << "RESULT: " << result;

        disconnect(socket, &QTcpSocket::readyRead, this, &MonsterServer::onReadyRead);
        disconnect(socket, &QTcpSocket::disconnected, this, &MonsterServer::onDisconnect);
//        disconnect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
//                this, SLOT(onDisconnect(QAbstractSocket::SocketError)));

        SessionPtr session = SessionPtr::create(socket);
        session->init();
        this->connect(session.data(), &Session::initialized, this, [=]() {
            emit sessionCreated(session);
        });
        QPointer<QThread> thread = new MonsterThread(session, m_sessions.toWeakRef(), this);
        connect(thread, &QThread::finished, thread.data(), &QObject::deleteLater);
        m_threads.append(thread);
        thread->start();

    }
    qDebug() << "COMMAND: " << command;
    buffer.close();
}

void MonsterServer::onDisconnect() {
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    disconnect(socket, &QTcpSocket::readyRead, this, &MonsterServer::onReadyRead);
    disconnect(socket, &QTcpSocket::disconnected, this, &MonsterServer::onDisconnect);
//    disconnect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
//            this, SLOT(onDisconnect(QAbstractSocket::SocketError)));
}

}
