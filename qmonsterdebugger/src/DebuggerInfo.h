#ifndef DEBUGGERINFO_HPP
#define DEBUGGERINFO_HPP

#include <QString>

class QObject;
class QByteArray;
class DebuggerInfo {
public:
    DebuggerInfo(const QString& id, QObject* info);

//    QByteArray* getBytes() const;

//    void setBytes(QByteArray* bytes);

//    const QString& getId() const;

//    const QObject* getInfo() const;

private:
    QString     m_id;
    QObject*    m_data;
};

#endif // DEBUGGERINFO_HPP
