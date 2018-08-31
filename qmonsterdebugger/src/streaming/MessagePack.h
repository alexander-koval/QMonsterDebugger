#ifndef MESSAGEPACK_H
#define MESSAGEPACK_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QSharedPointer>

namespace monster {
class MessagePack
{
public:
    static MessagePack read(QByteArray& bytes);

    MessagePack();

    MessagePack(const QString& id, const QJsonDocument& data);

    const QString& getID();

    const QJsonDocument& getData();

    QSharedPointer<QByteArray> getBytes();

    void setBytes(QByteArray& bytes);

private:
    QString m_id;
    QJsonDocument m_data;
};

}
#endif // MESSAGEPACK_H
