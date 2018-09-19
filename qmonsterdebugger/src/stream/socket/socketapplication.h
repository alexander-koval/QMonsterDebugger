#ifndef SOCKETAPPLICATION_H
#define SOCKETAPPLICATION_H

#include "stream/debuggable.h"
#include <qglobal.h>
#include <string>

class SocketApplication : public Debuggable
{
public:
    SocketApplication(quint64 id, const std::string& name, const std::string& type)
        : Debuggable(),
          m_id(id),
          m_name(name),
          m_type(type) { }

    virtual quint64 getId() const override {
        return m_id;
    }

    virtual const std::string& getName() const override {
        return m_name;
    }

    virtual const std::string& getType() const override {
        return m_type;
    }

private:
    quint64 m_id;
    std::string m_name;
    std::string m_type;
};

#endif // SOCKETAPPLICATION_H
