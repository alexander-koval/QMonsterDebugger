#include "CommandProcessor.h"
#include <string>
#include <sstream>
#include <QBuffer>
#include <QDataStream>
#include <QJsonDocument>
#include <QDomDocument>
#include <QMap>
#include <QList>
#include <QVariant>
#include <QVector>
#include "stream/constants.h"
#include <iostream>
#include "amf/serializer.hpp"
#include "amf/deserializer.hpp"
#include "amf/amf.hpp"
#include "amf/types/amfobject.hpp"
#include "amf/types/amfstring.hpp"
#include "amf/types/amfbool.hpp"
#include "amf/types/amfbytearray.hpp"
#include "amf/types/amfdate.hpp"
#include "amf/types/amfdictionary.hpp"
#include "amf/types/amfdouble.hpp"
#include "amf/types/amfinteger.hpp"
#include "amf/types/amfitem.hpp"
#include "amf/types/amfnull.hpp"
#include "amf/types/amfundefined.hpp"
#include "amf/types/amfvector.hpp"
#include "amf/types/amfxml.hpp"
#include "amf/types/amfxmldocument.hpp"
#include "amf/types/amfarray.hpp"


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
//    return CommandProcessor::deserialize(bytes).as<amf::AmfObject>();
}

QVariant deserializeID(const QByteArray& bytes) {
//    return CommandProcessor::deserialize(bytes).as<amf::AmfString>();
}

QVariant CommandProcessor::deserialize(const QByteArray &bytes) {
    using namespace amf;
    v8 data(bytes.begin(), bytes.end());
    Deserializer deserializer;
    v8::const_iterator it = data.cbegin();
    if (it == data.cend())
        throw std::out_of_range("CommandProcessor::deserialize end of input");
    u8 type = *it;
    AmfItemPtr item = deserializer.deserialize(it, data.cend());
    switch (type) {
    case AMF_UNDEFINED: return QVariant(QVariant::Invalid);
    case AMF_NULL: return QVariant(QVariant::Invalid);
    case AMF_FALSE: return QVariant(item.as<AmfBool>().value);
    case AMF_INTEGER: return QVariant(item.as<AmfInteger>().value);
    case AMF_DOUBLE: return QVariant(item.as<AmfDouble>().value);
    case AMF_STRING: return QVariant(QString::fromStdString(item.as<AmfString>().value));
    case AMF_XMLDOC: return QVariant(QString::fromStdString(item.as<AmfXmlDocument>().value)); // TODO a.koval It's just a string
    case AMF_DATE: return QVariant(item.as<AmfDate>().value); // TODO a.koval It's just a long long
    case AMF_ARRAY: {
//        QVector<AmfItemPtr> vector = QVector<AmfItemPtr>::fromStdVector(item.as<AmfArray>().dense);
//        return QVariant(QList<AmfItemPtr>::fromVector(vector)); // TODO a.koval It's vector of AmfItemPtr
    }
//    case AMF_OBJECT: return QVariant(item.as<AmfObject>().dynamicProperties);
//    case AMF_XML: return QVariant(item.as<AmfXml>().value);
//    case AMF_BYTEARRAY: return QVariant(item.as<AmfByteArray>().value);
//    case AMF_VECTOR_INT: return QVariant(item.as<AmfVector<int>>().values);
//    case AMF_VECTOR_UINT: return QVariant(item.as<AmfVector<uint>>().values);
//    case AMF_VECTOR_DOUBLE: return QVariant(item.as<AmfVector<double>>().values);
//    case AMF_VECTOR_OBJECT: return QVariant(item.as<AmfVector<AmfObject>>().values);
//    case AMF_DICTIONARY: return QVariant(item.as<AmfDictionary>().values);
//    default: return QVariant(Qvariant::Invalid);
    }
//    switch (type) {
//        case AMF_UNDEFINED: {
//            QVariant(QVariant::Invalid);
//            return item.as<AmfUndefined*>();
//        }
//        case AMF_NULL:
//            return AmfItemPtr(AmfNull::deserialize(it, end, ctx));
//        case AMF_FALSE:
//        case AMF_TRUE:
//            return AmfItemPtr(AmfBool::deserialize(it, end, ctx));
//        case AMF_INTEGER:
//            return AmfItemPtr(AmfInteger::deserialize(it, end, ctx));
//        case AMF_DOUBLE:
//            return AmfItemPtr(AmfDouble::deserialize(it, end, ctx));
//        case AMF_STRING:
//            return AmfItemPtr(AmfString::deserialize(it, end, ctx));
//        case AMF_XMLDOC:
//            return AmfItemPtr(AmfXmlDocument::deserialize(it, end, ctx));
//        case AMF_DATE:
//            return AmfItemPtr(AmfDate::deserialize(it, end, ctx));
//        case AMF_ARRAY:
//            return AmfArray::deserializePtr(it, end, ctx);
//        case AMF_OBJECT:
//            return AmfObject::deserializePtr(it, end, ctx);
//        case AMF_XML:
//            return AmfItemPtr(AmfXml::deserialize(it, end, ctx));
//        case AMF_BYTEARRAY:
//            return AmfItemPtr(AmfByteArray::deserialize(it, end, ctx));
//        case AMF_VECTOR_INT:
//            return AmfItemPtr(AmfVector<int>::deserialize(it, end, ctx));
//        case AMF_VECTOR_UINT:
//            return AmfItemPtr(AmfVector<unsigned int>::deserialize(it, end, ctx));
//        case AMF_VECTOR_DOUBLE:
//            return AmfItemPtr(AmfVector<double>::deserialize(it, end, ctx));
//        case AMF_VECTOR_OBJECT:
//            return AmfVector<AmfItem>::deserializePtr(it, end, ctx);
//        case AMF_DICTIONARY:
//            return AmfDictionary::deserializePtr(it, end, ctx);
//        default:
//            throw std::invalid_argument("Deserializer::deserialize: Invalid type byte");
//    }
//    return item;
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

void CommandProcessor::decode(QString& id, QMap<std::string, QVariant>& data,
                              QByteArray &bytes) {
    QDataStream buffer(&bytes, QIODevice::ReadOnly);
    quint32 packSize;

    buffer >> packSize;
    char* bufID = new char[packSize];
    buffer.readRawData(bufID, packSize);
    amf::AmfString amf_str = deserializeID(QByteArray::fromRawData(bufID, packSize));
    id = QString::fromStdString(amf_str.value);

    buffer >> packSize;
    char* bufMsg = new char[packSize];
    buffer.readRawData(bufMsg, packSize);
    amf::AmfObject amf_obj = deserializeMsg(QByteArray::fromRawData(bufMsg, packSize));
//    data = QMap<std::string, QVariant>(amf_obj.dynamicProperties);

    delete[] bufID;
    delete[] bufMsg;
}

amf::v8 CommandProcessor::serialize(const char *command)
{
    return amf::v8();
}

}
