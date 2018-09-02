#ifndef MESSAGEPACK_H
#define MESSAGEPACK_H

#include <QObject>
#include <QString>
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

    MessagePack(const amf::AmfString& id, const amf::AmfObject& data);

    const amf::AmfString& getID();

    const amf::AmfObject& getData();

    QSharedPointer<QByteArray> getBytes();

    void setBytes(QByteArray& bytes);

private:
    amf::AmfString m_id;
    amf::AmfObject m_data;
};

}
#endif // MESSAGEPACK_H
