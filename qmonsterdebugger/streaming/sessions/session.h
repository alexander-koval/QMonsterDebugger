#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QObject>
#include <QByteArray>
#include <QPointer>
#include <QWeakPointer>

class QTcpSocket;
namespace monster { class Session; }
using SessionWPtr = QWeakPointer<monster::Session>;
using SessionPtr = QSharedPointer<monster::Session>;
using TcpSocketPtr = QPointer<QTcpSocket>;
namespace monster {
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
}
#endif // SESSION_H
