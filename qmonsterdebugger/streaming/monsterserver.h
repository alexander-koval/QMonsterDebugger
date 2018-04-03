#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QTcpServer>
#include <memory>
#include <map>

class Sessions;
class MonsterServer : public QTcpServer {
Q_OBJECT
public:
    using SessionsPtr = std::shared_ptr<Sessions>;

    MonsterServer(QObject* parent = nullptr);

    virtual ~MonsterServer();

    bool start(int port = 5840);

protected:
    virtual void incomingConnection(qintptr handle) override;

private:
    SessionsPtr m_sessions;
    QList<QPointer<QThread>> m_threads;
};

#endif // SOCKETSERVER_H
