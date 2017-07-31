#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QByteArray>

class QTcpSocket;
class Session
{
public:
    explicit Session(QTcpSocket* socket);

    bool connected() const;

    bool write(const QByteArray& msg);

    void close();

    std::string getAddress() const;

    qintptr getId() const;

private:
    QTcpSocket* m_socket;
};

#endif // SESSION_H
