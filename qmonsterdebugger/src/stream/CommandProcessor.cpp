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

amf::v8 serializeMsg(const char *cmd) {
    amf::Serializer serializer;
    amf::AmfObject object("", true, false);
    amf::AmfString command(cmd);
    object.addDynamicProperty("command", command);
    serializer << object;
    return serializer.data();
}

amf::v8 serializeID(const char* id) {
    amf::Serializer serializer;
    amf::AmfString string(id);
    serializer << string;
    return serializer.data();
}

QVariant deserializeMsg(const QByteArray& bytes) {
    return CommandProcessor::deserialize(bytes);
}

QVariant deserializeID(const QByteArray& bytes) {
    return CommandProcessor::deserialize(bytes);
}

QVariant CommandProcessor::deserialize(const QByteArray &bytes) {
    using namespace amf;
    v8 data(bytes.begin(), bytes.end());
    Deserializer deserializer;
    v8::const_iterator it = data.cbegin();
    AmfItemPtr item = deserializer.deserialize(it, data.cend());
    return AMFConverter::convert(item->marker(), item);
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
    amf::v8&& data = serializeMsg(COMMAND_HELLO);
    QByteArray msg = QByteArray::fromRawData(
                reinterpret_cast<const char*>(data.data()), data.size());
    encode(msg, *bytes);
}

void CommandProcessor::base(QByteArray* bytes) {
    amf::v8&& data = serializeMsg(COMMAND_HELLO);
    QByteArray msg = QByteArray::fromRawData(
                reinterpret_cast<const char*>(data.data()), data.size());
    encode(msg, *bytes);
}

void CommandProcessor::encode(QByteArray& msg, QByteArray& bytes) {
    QByteArray bufferID;
    QByteArray bufferMsg;
    amf::v8&& v8 = serializeID(LOGGER_ID);
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

void CommandProcessor::decode(QString& id, QMap<QString, QVariant>& data,
                              QByteArray &bytes) {
    QDataStream buffer(&bytes, QIODevice::ReadOnly);
    quint32 packSize;

    buffer >> packSize;
    char* bufID = new char[packSize];
    buffer.readRawData(bufID, packSize);
    QVariant header = deserialize(QByteArray::fromRawData(bufID, packSize));
    id = header.toString();

    buffer >> packSize;
    char* bufMsg = new char[packSize];
    buffer.readRawData(bufMsg, packSize);
    QVariant body = deserialize(QByteArray::fromRawData(bufMsg, packSize));
    data = body.toMap();

    delete[] bufID;
    delete[] bufMsg;
}

amf::v8 CommandProcessor::serialize(const char *command)
{
    return amf::v8();
}

}
