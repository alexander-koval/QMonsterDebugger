#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QObject>
#include <QByteArray>
#include <QBuffer>
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
    using Base = QObject;

    explicit Session(TcpSocketPtr socket);

    void init();

    bool connected() const;

    bool write(const QByteArray& msg);

    void close();

    QString address() const;

    qintptr socketDescriptor() const;

    const QTcpSocket* socket() const;

private:
    void encode();

private slots:
    void onReadyRead();

    void onDisconnected();

private:
    uint32_t m_size;
    QBuffer m_bytes;
    QBuffer m_package;
    TcpSocketPtr m_socket;
};
}
#endif // SESSION_H