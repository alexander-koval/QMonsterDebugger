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

    MessagePack(const QString& id, const QMap<QString, QVariant>& data);

    const QString& getID();

    const QMap<QString, QVariant>& getData();

    QSharedPointer<QByteArray> getBytes() const;

    void setBytes(QByteArray& bytes);

private:
    QString m_id;
    QMap<QString, QVariant> m_data;
};

}
#endif // MESSAGEPACK_H
