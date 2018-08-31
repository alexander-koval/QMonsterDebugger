#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QObject>
#include <QByteArray>
#include <QBuffer>
#include <QPointer>
#include <QWeakPointer>
#include <QAbstractSocket>

class QTcpSocket;
namespace monster { class Session; }
using SessionWPtr = QWeakPointer<monster::Session>;
using SessionPtr = QSharedPointer<monster::Session>;
using TcpSocketPtr = QPointer<QTcpSocket>;

namespace monster {
class MessagePack;
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

    void process(MessagePack& pack);

private slots:
    void onReadyRead();

    void onDisconnected();

    void onSocketError(QAbstractSocket::SocketError);

private:
    int32_t m_size;
    QBuffer m_bytes;
    QBuffer m_package;
    TcpSocketPtr m_socket;
    quint16     m_blockSize;
};
}
#endif // SESSION_H
