#ifndef STREAMFWD_H
#define STREAMFWD_H

#include <QPointer>
#include <QSharedPointer>
#include <QScopedPointer>

class QTcpSocket;

namespace monster {

class Session;
class Sessions;
class MainWindow;
class MonsterServer;
class MessagePack;

using SessionPtr = QSharedPointer<Session>;
using SessionsWPtr = QWeakPointer<Sessions>;
using SessionsPtr = QSharedPointer<Sessions>;
using TcpSocketPtr = QPointer<QTcpSocket>;
using MonsterServerPtr = QSharedPointer<MonsterServer>;
using MessagePackPtr = QSharedPointer<MessagePack>;

}

#endif // STREAMFWD_H
