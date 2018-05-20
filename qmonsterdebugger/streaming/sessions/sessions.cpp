#include "sessions.h"
#include <QReadLocker>
#include <QWriteLocker>
#include "session.h"

void Sessions::add(const SessionPtr session) {
    QWriteLocker locker(&m_lock);
    m_sessions.insert(session->socketDescriptor(), session.toWeakRef());
}

void Sessions::remove(quint16 id) {
    QWriteLocker locker(&m_lock);
    m_sessions.remove(id);
}

const SessionMap &Sessions::getSessions() const {
    return m_sessions;
}

quint64 Sessions::size() const {
    return m_sessions.size();
}
