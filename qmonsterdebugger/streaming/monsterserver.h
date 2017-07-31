#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QTcpServer>
#include <memory>
#include <map>

class Sessions;
class MonsterServer : public QTcpServer {
Q_OBJECT
public:
    MonsterServer(QObject* parent = nullptr);

    virtual ~MonsterServer();

    bool start(int port = 5840);

protected:
    virtual void incomingConnection(qintptr handle);

private:
    std::unique_ptr<Sessions> m_sessions;
};

#endif // SOCKETSERVER_H
