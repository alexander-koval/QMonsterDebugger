#ifndef MESSAGEPACK_H
#define MESSAGEPACK_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QJsonDocument>
#include <QSharedPointer>
#include "amf/types/amfstring.hpp"
#include "amf/types/amfobject.hpp"

namespace monster {
class MessagePack
{
public:
    static MessagePack read(QByteArray& bytes);

    MessagePack();

    MessagePack(const QString& id, const QPair<std::string, QVariant>& data);

    const QString& getID();

    const QPair<std::string, QVariant>& getData();

    QSharedPointer<QByteArray> getBytes() const;

    void setBytes(QByteArray& bytes);

private:
    QString m_id;
    QPair<std::string, QVariant> m_data;
};

}
#endif // MESSAGEPACK_H
