#include "MessagePack.h"
#include <QDataStream>
#include <QIODevice>
#include "stream/CommandProcessor.h"
#include "amf/utils/amfitemptr.hpp"
#include "amf/serializer.hpp"
#include "QMap"
#include "QString"

namespace monster {
MessagePack MessagePack::read(QByteArray &bytes) {
    MessagePack pack(CommandProcessor::decode(bytes));
    return pack;
}

MessagePack::MessagePack() : m_id(), m_data() {

}

MessagePack::MessagePack(amf::AmfItemPtr id, amf::AmfItemPtr data)
    : m_id(id), m_data(data) {

}

QSharedPointer<QByteArray> MessagePack::getBytes() const {
    return CommandProcessor::encode(*this);
}

}
