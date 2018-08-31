#include "MessagePack.h"
#include <QDataStream>
#include <QIODevice>
#include "streaming/CommandProcessor.h"

namespace monster {
MessagePack MessagePack::read(QByteArray &bytes) {
    MessagePack pack;
    pack.setBytes(bytes);
    return pack;
}

MessagePack::MessagePack() : m_id(), m_data() {

}

MessagePack::MessagePack(const QString &id, const QJsonDocument& data)
    : m_id(id), m_data(data) {

}

const QString& MessagePack::getID() {
    return m_id;
}

const QJsonDocument& MessagePack::getData() {
    return m_data;
}

QSharedPointer<QByteArray> MessagePack::getBytes() {
    QSharedPointer<QByteArray> bytes(new QByteArray);
    QByteArray msg = m_data.toJson();
    CommandProcessor::encode(msg, *bytes);
    return bytes;
}

void MessagePack::setBytes(QByteArray &bytes) {
    CommandProcessor::decode(m_id, m_data, bytes);
}
}
