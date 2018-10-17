#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QObject>
#include <QByteArray>
#include <QBuffer>
#include <QPointer>
#include <QWeakPointer>
#include <QAbstractSocket>
#include "panels/TraceModel.h"

class QTcpSocket;
namespace monster { class Session; }
using SessionWPtr = QWeakPointer<monster::Session>;
using SessionPtr = QSharedPointer<monster::Session>;
using TcpSocketPtr = QPointer<QTcpSocket>;

namespace monster {
class MessagePack;
class SessionModelData;
using SessionModelDataPtr = QSharedPointer<SessionModelData>;
class Session : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString address READ address CONSTANT)
    Q_PROPERTY(const QString& playerType READ playerType CONSTANT)
    Q_PROPERTY(const QString& playerVersion READ playerVersion CONSTANT)
    Q_PROPERTY(bool isFlex READ isFlex CONSTANT)
    Q_PROPERTY(const QString& title READ fileTitle CONSTANT)
    Q_PROPERTY(const QString& location READ fileLocation CONSTANT)
    Q_PROPERTY(QObject* traces READ traces CONSTANT)
public:
    enum Roles { Title = Qt::UserRole + 1, Socket, Trace, Monitor };
    using Base = QObject;

    explicit Session();

    explicit Session(TcpSocketPtr socket);

    void init();

    bool connected() const;

    bool write(const QByteArray& msg);

    void close();

    QString address() const;

    qintptr socketDescriptor() const;

    const QTcpSocket* socket() const;

    void socket(TcpSocketPtr socket);

    const QString& playerType() const { return m_playerType; }

    const QString& playerVersion() const { return m_playerVersion; }

    bool isDebugger() const { return m_isDebugger; }

    bool isFlex() const { return m_isFlex; }

    const QString& fileTitle() const { return m_fileTitle; }

    const QString& fileLocation() const { return m_fileLocation; }

    QObject* traces() { return m_traces.data(); }

signals:
    void initialized();

    void inboundMessage(MessagePack& pack);

private:
    void decode(QBuffer& bytes, int32_t size);

    void process(MessagePack& pack);

private slots:
    void onReadyRead();

    void onDisconnected();

    void onSocketError(QAbstractSocket::SocketError);

private:
//    int32_t m_size;
//    QBuffer m_bytes;
//    QByteArray m_package;
    TcpSocketPtr m_socket;
    QString m_playerType;
    QString m_playerVersion;
    bool m_isDebugger;
    bool m_isFlex;
    QString m_fileTitle;
    QString m_fileLocation;
    TraceModelPtr m_traces;
};
//Q_DECLARE_METATYPE(Session*);
}
#endif // SESSION_H
