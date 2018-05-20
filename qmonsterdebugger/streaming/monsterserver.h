#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QPointer>
#include <QSharedPointer>
#include <QScopedPointer>
#include <map>

class Session;
class Sessions;
using SessionPtr = QSharedPointer<Session>;
using SessionsWPtr = QWeakPointer<Sessions>;
using SessionsPtr = QSharedPointer<Sessions>;
using TcpSocketPtr = QPointer<QTcpSocket>;
class MonsterServer : public QTcpServer {
Q_OBJECT
public:
    using Base = QTcpServer;

    MonsterServer(QObject* parent = nullptr);

    ~MonsterServer() override;

    bool start(quint16 port = 5840);

protected:
    virtual void incomingConnection(qintptr handle) override;

private:
    SessionsPtr m_sessions;
    QList<QPointer<QThread>> m_threads;
};

class MonsterThread : public QThread {
Q_OBJECT
public:
    explicit MonsterThread(SessionPtr session, SessionsWPtr sessions, QObject* parent = nullptr);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketerror);

private slots:
    void onReadyRead();

    void onDisconnected();

private:
    SessionPtr m_session;
    SessionsWPtr m_sessions;
};

#endif // SOCKETSERVER_H
