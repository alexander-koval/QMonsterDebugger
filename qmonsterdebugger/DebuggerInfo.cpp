#include "DebuggerInfo.hpp"
#include <QString>
#include <QObject>

DebuggerInfo::DebuggerInfo(const QString& id, QObject* info)
    : m_id(id)
    , m_data(info) {

}
