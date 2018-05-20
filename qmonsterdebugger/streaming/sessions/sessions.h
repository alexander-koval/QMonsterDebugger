#ifndef SESSIONS_H
#define SESSIONS_H

#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include <QReadWriteLock>
#include <qglobal.h>

namespace monster {
class Session;
using SessionPtr = QSharedPointer<Session>;
using SessionWPtr = QWeakPointer<Session>;
using SessionMap = QMap<quint64, SessionWPtr>;

class Sessions : public QObject {
Q_OBJECT
public:
    Sessions(QObject* parent) : QObject(parent), m_lock(), m_sessions() {}

    void add(const SessionPtr session);

    void remove(quint16 id);

    const SessionMap& getSessions() const;

    quint64 size() const;

private:
    mutable QReadWriteLock m_lock;
    SessionMap m_sessions;
};

}
#endif // SESSIONS_H
