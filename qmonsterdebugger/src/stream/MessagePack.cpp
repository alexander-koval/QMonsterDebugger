#include "MessagePack.h"
#include <QDataStream>
#include <QIODevice>
#include "stream/CommandProcessor.h"
#include "amf/utils/amfitemptr.hpp"
#include "amf/serializer.hpp"
#include "QMap"
#include "QString"

namespace {

amf::AmfString convert(const QString& string) {
    amf::AmfString amf_str(string.toStdString());
    return amf_str;
}

template <typename T, typename U>
T toAMF(U& variant) {
    return convert(variant);
}

}

namespace monster {
MessagePack MessagePack::read(QByteArray &bytes) {
    MessagePack pack;
    pack.setBytes(bytes);
    return pack;
}

MessagePack::MessagePack() : m_id(), m_data() {

}

MessagePack::MessagePack(const QString &id, const QMap<QString, QVariant>& data)
    : m_id(id), m_data(data) {

}

const QString& MessagePack::getID() {
    return m_id;
}

const QMap<QString, QVariant>& MessagePack::getData() {
    return m_data;
}

QSharedPointer<QByteArray> MessagePack::getBytes() const{
    QSharedPointer<QByteArray> bytes(new QByteArray);
    amf::Serializer serializer;
    amf::AmfObject object("", true, false);
    foreach(const QString& key, m_data.keys()) {
        QVariant item = m_data.value(key, QVariant());
        QVariant::Type type = item.type();
        if (type == QVariant::Type::String) {
            const QString& value = item.toString();
            object.addDynamicProperty(key.toStdString(),
                                      toAMF<amf::AmfString, const QString>(value));
        }
    }
    serializer << object;
    const amf::v8& buffer = serializer.data();
    QByteArray msg = QByteArray::fromRawData(
                reinterpret_cast<const char*>(buffer.data()), buffer.size());
    CommandProcessor::encode(msg, *bytes);
    return bytes;
}

void MessagePack::setBytes(QByteArray &bytes) {
//    amf::AmfItemPtr item = CommandProcessor::deserialize(bytes);
//    item.as<amf::AmfString>();
    CommandProcessor::decode(m_id, m_data, bytes);
}
}
