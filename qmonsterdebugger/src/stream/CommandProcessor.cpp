#include "CommandProcessor.h"
#include <string>
#include <sstream>
#include <QBuffer>
#include <QDataStream>
#include <QJsonDocument>
#include <QDomDocument>
#include <QMap>
#include <QHash>
#include <QList>
#include <QVariant>
#include <QVector>
#include "utils/AMFConverter.h"
#include "stream/constants.h"
#include <iostream>
#include "amf/serializer.hpp"
#include "amf/deserializer.hpp"
#include "amf/types/amfobject.hpp"
#include "amf/types/amfstring.hpp"

namespace monster {

amf::v8 CommandProcessor::serialize(const char* cmd) {
    using namespace amf;
    AmfObject* object = new AmfObject("", true, false);
    AmfString command(cmd);
    object->addDynamicProperty("command", command);
    return serialize(AmfItemPtr(object));
}

amf::v8 CommandProcessor::serialize(const amf::AmfItemPtr &item) {
    using namespace amf;
    Serializer serializer;
    serializer << *item.get();
    return serializer.data();
}

amf::AmfItemPtr CommandProcessor::deserialize(const QByteArray &bytes) {
    using namespace amf;
    v8 data(bytes.begin(), bytes.end());
    Deserializer deserializer;
    v8::const_iterator it = data.cbegin();
    AmfItemPtr item = deserializer.deserialize(it, data.cend());
    return item;
}

void CommandProcessor::policyRequest(QByteArray* bytes) {
    char zero = 0x00;
    QDataStream streamXML(bytes, QIODevice::WriteOnly);
    QString crossdomain("<?xml version=\"1.0\"?>"
                        "<!DOCTYPE cross-domain-policy SYSTEM \"http://www.adobe.com/xml/dtds/cross-domain-policy.dtd\">"
                        "<cross-domain-policy xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.adobe.com/xml/schemas/PolicyFile.xsd\">"
                        "<site-control permitted-cross-domain-policies=\"master-only\"/>"
                        "<allow-access-from domain=\"*\" to-ports=\"*\" secure=\"false\"/>"
                        "<allow-http-request-headers-from domain=\"*\" headers=\"*\" secure=\"false\"/>"
                        "</cross-domain-policy>");
    (*bytes) = crossdomain.toUtf8();
    streamXML.writeRawData(bytes->data(), bytes->size());
    streamXML.writeRawData(&zero, 1);
}

void CommandProcessor::hello(QByteArray* bytes) {
    amf::v8 data = serialize(COMMAND_HELLO);
    QByteArray msg = QByteArray::fromRawData(
                reinterpret_cast<const char*>(data.data()), data.size());
    encode(msg, *bytes);
}

void CommandProcessor::base(QByteArray* bytes) {
    amf::v8 data = serialize(COMMAND_HELLO);
    QByteArray msg = QByteArray::fromRawData(
                reinterpret_cast<const char*>(data.data()), data.size());
    encode(msg, *bytes);
}

QSharedPointer<QByteArray> CommandProcessor::encode(const MessagePack &pack) {
    QSharedPointer<QByteArray> bytes(new QByteArray);
    amf::Serializer serializer;
    const amf::AmfObject& object = pack.getData().as<amf::AmfObject>();
    serializer << object;
    const amf::v8& buffer = serializer.data();
    QByteArray msg = QByteArray::fromRawData(
                reinterpret_cast<const char*>(buffer.data()), buffer.size());
    CommandProcessor::encode(msg, *bytes);
    return bytes;
}

void CommandProcessor::encode(QByteArray& msg, QByteArray& bytes) {
    using namespace amf;
    QByteArray bufferID;
    QByteArray bufferMsg;
    v8 v8 = serialize(AmfItemPtr(new AmfString(LOGGER_ID)));
    QByteArray id = QByteArray::fromRawData(
                reinterpret_cast<const char*>(v8.data()), v8.size());
    QDataStream dataStream(&bytes, QIODevice::WriteOnly);

    QDataStream streamID(&bufferID, QIODevice::WriteOnly);
    QDataStream streamMsg(&bufferMsg, QIODevice::WriteOnly);
//    streamID << static_cast<quint16>(id.size());
    streamID.writeRawData(id, static_cast<uint16_t>(id.size()));
//    streamMsg << static_cast<quint16>(msg.size());
    streamMsg.writeRawData(msg, static_cast<uint16_t>(msg.size()));
    dataStream << bufferID << bufferMsg;
}

MessagePack CommandProcessor::decode(QByteArray &bytes) {
    QDataStream buffer(&bytes, QIODevice::ReadOnly);
    quint32 packSize;

    buffer >> packSize;
    char* bufID = new char[packSize];
    buffer.readRawData(bufID, packSize);
    amf::AmfItemPtr header = deserialize(QByteArray::fromRawData(bufID, packSize));


    buffer >> packSize;
    char* bufMsg = new char[packSize];
    buffer.readRawData(bufMsg, packSize);
    amf::AmfItemPtr body = deserialize(QByteArray::fromRawData(bufMsg, packSize));

    delete[] bufID;
    delete[] bufMsg;

    MessagePack pack(header, body);
    return pack;
}

}
