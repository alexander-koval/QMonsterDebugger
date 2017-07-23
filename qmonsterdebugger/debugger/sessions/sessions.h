#ifndef SESSIONS_H
#define SESSIONS_H

#include <map>
#include <memory>
#include <qglobal.h>

class Session;
class Sessions
{
using SessionPtr = std::shared_ptr<Session>;
using SessionWPtr = std::weak_ptr<Session>;
using SessionMap = std::map<quint64, const SessionWPtr&>;

public:
    Sessions() : m_sessions() {}

    void add(const SessionPtr& session) {
//        m_sessions.insert(std::make_pair(session))
    }

    void remove(const SessionPtr& session);

    const SessionMap& getSessions() const;

    quint64 size() const;

private:
    SessionMap m_sessions;
};

#endif // SESSIONS_H
