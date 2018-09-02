#include "MessagePack.h"
#include <QDataStream>
#include <QIODevice>
#include "streaming/CommandProcessor.h"
#include "amf/utils/amfitemptr.hpp"

namespace monster {
MessagePack MessagePack::read(QByteArray &bytes) {
    MessagePack pack;
    pack.setBytes(bytes);
    return pack;
}

MessagePack::MessagePack() : m_id(), m_data() {

}

MessagePack::MessagePack(const amf::AmfString &id, const amf::AmfObject& data)
    : m_id(id), m_data(data) {

}

const amf::AmfString& MessagePack::getID() {
    return m_id;
}

const amf::AmfObject& MessagePack::getData() {
    return m_data;
}

QSharedPointer<QByteArray> MessagePack::getBytes() {
    QSharedPointer<QByteArray> bytes(new QByteArray);
    QByteArray msg = m_data.toJson();
    CommandProcessor::encode(msg, *bytes);
    return bytes;
}

void MessagePack::setBytes(QByteArray &bytes) {
    amf::AmfItemPtr item = CommandProcessor::deserialize(bytes);
    item.as<amf::AmfString>();
    CommandProcessor::decode(m_id, m_data, bytes);
}
}
