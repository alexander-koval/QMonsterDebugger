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

class AMFConverter {
public:
    static QVariant convert(amf::u8 type, amf::AmfItemPtr item) {
        using namespace amf;
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
            QList<QVariant> items;
            std::vector<AmfItemPtr> dense = item.as<AmfArray>().dense;
            std::for_each(dense.begin(), dense.end(), [&items](AmfItemPtr& item) {
                QVariant variant = convert(item->marker(), item);
                items.push_back(variant);
            });
            return QVariant(items);
        }
        case AMF_OBJECT: {
            QMap<QString, QVariant> properties;
            std::map<std::string, AmfItemPtr>& dynamic = item.as<AmfObject>().dynamicProperties;
            std::for_each(dynamic.begin(), dynamic.end(), [&properties](std::pair<const std::string, AmfItemPtr>& pair) {
                AmfItemPtr& item = pair.second;
                QVariant variant = convert(item->marker(), item);
                properties.insert(QString::fromStdString(pair.first), variant);
            });
            std::map<std::string, AmfItemPtr>& sealed = item.as<AmfObject>().sealedProperties;
            std::for_each(sealed.begin(), sealed.end(), [&properties](std::pair<const std::string, AmfItemPtr>& pair) {
                AmfItemPtr& item = pair.second;
                QVariant variant = convert(item->marker(), item);
                properties.insert(QString::fromStdString(pair.first), variant);
            });
            return QVariant(properties);
        }
        case AMF_XML: {
           return QVariant(QString::fromStdString(item.as<AmfXml>().value));
        }
        case AMF_BYTEARRAY: {
            std::vector<u8> buffer = item.as<AmfByteArray>().value;
            QByteArray bytes = QByteArray::fromRawData(
                        reinterpret_cast<char*>(buffer.data()), buffer.size());
            return QVariant(bytes);
        }
        case AMF_VECTOR_INT: {
            QList<QVariant> items;
            std::vector<int> values = item.as<AmfVector<int>>().values;
            std::for_each(values.begin(), values.end(), [&items](int value) {
                items.push_back(value);
            });
            return QVariant(items);
        }
        case AMF_VECTOR_UINT: {
            QList<QVariant> items;
            std::vector<uint> values = item.as<AmfVector<uint>>().values;
            std::for_each(values.begin(), values.end(), [&items](uint value) {
                items.push_back(value);
            });
            return QVariant(items);
        }
        case AMF_VECTOR_DOUBLE: {
            QList<QVariant> items;
            std::vector<double> values = item.as<AmfVector<double>>().values;
            std::for_each(values.begin(), values.end(), [&items](double value) {
                items.push_back(value);
            });
            return QVariant(items);
        }
        case AMF_VECTOR_OBJECT: {
            QList<QVariant> items;
            std::vector<AmfItemPtr> values = item.as<AmfVector<AmfItem>>().values;
            std::for_each(values.begin(), values.end(), [&items](AmfItemPtr& item) {
                QVariant variant = convert(item->marker(), item);
                items.push_back(variant);
            });
            return QVariant(items);
        }
        case AMF_DICTIONARY: {
            QHash<QString, QVariant> hash;
            std::unordered_map<AmfItemPtr, AmfItemPtr, AmfDictionaryHash>& values =
                    item.as<AmfDictionary>().values;
            std::for_each(values.begin(), values.end(), [&hash](std::pair<const AmfItemPtr, AmfItemPtr>& pair) {
                const AmfItemPtr& key = pair.first;
                AmfItemPtr& item = pair.second;
                hash.insert(QString::fromStdString(key.as<AmfString>().value),
                            convert(item->marker(), item));
            });
            return QVariant(hash);
        }
        }
        return QVariant();
    }
};

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
