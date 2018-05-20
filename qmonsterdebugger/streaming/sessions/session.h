#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QObject>
#include <QByteArray>
#include <QPointer>
#include <QWeakPointer>

class QTcpSocket;
class Session;
using SessionWPtr = QWeakPointer<Session>;
using SessionPtr = QSharedPointer<Session>;
using TcpSocketPtr = QPointer<QTcpSocket>;
class Session : public QObject {
Q_OBJECT
public:
    explicit Session(TcpSocketPtr socket);

    bool connected() const;

    bool write(const QByteArray& msg);

    void close();

    QString address() const;

    qintptr socketDescriptor() const;

    const QTcpSocket* socket() const;
private:
    TcpSocketPtr m_socket;
};

#endif // SESSION_H
