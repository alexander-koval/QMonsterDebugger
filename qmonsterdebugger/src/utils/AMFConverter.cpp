#include "AMFConverter.h"
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

QList<QVariant> fromAmfArr(amf::AmfItemPtr item) {
    using namespace amf;
    QList<QVariant> items;
    std::vector<AmfItemPtr> dense = item.as<AmfArray>().dense;
    std::for_each(dense.begin(), dense.end(), [&items](AmfItemPtr& item) {
        QVariant variant = AMFConverter::convert(item->marker(), item);
        items.push_back(variant);
    });
    return items;
}

QMap<QString, QVariant> fromAmfObj(amf::AmfItemPtr item) {
    using namespace amf;
    QMap<QString, QVariant> properties;
    std::map<std::string, AmfItemPtr>& dynamic = item.as<AmfObject>().dynamicProperties;
    std::for_each(dynamic.begin(), dynamic.end(), [&properties](std::pair<const std::string, AmfItemPtr>& pair) {
        AmfItemPtr& item = pair.second;
        QVariant variant = AMFConverter::convert(item->marker(), item);
        properties.insert(QString::fromStdString(pair.first), variant);
    });
    std::map<std::string, AmfItemPtr>& sealed = item.as<AmfObject>().sealedProperties;
    std::for_each(sealed.begin(), sealed.end(), [&properties](std::pair<const std::string, AmfItemPtr>& pair) {
        AmfItemPtr& item = pair.second;
        QVariant variant = AMFConverter::convert(item->marker(), item);
        properties.insert(QString::fromStdString(pair.first), variant);
    });
    return properties;
}

QByteArray fromAmfBytes(amf::AmfItemPtr item) {
    using namespace amf;
    std::vector<u8> buffer = item.as<AmfByteArray>().value;
    QByteArray bytes = QByteArray::fromRawData(
                reinterpret_cast<char*>(buffer.data()), buffer.size());
    return bytes;
}

QList<QVariant> fromAmfVecI(amf::AmfItemPtr item) {
    using namespace amf;
    QList<QVariant> items;
    std::vector<int> values = item.as<AmfVector<int>>().values;
    std::for_each(values.begin(), values.end(), [&items](int value) {
        items.push_back(value);
    });
    return items;
}

QList<QVariant> fromAmfVec(amf::AmfItemPtr item) {
    using namespace amf;
    QList<QVariant> items;
    std::vector<AmfItemPtr> values = item.as<AmfVector<AmfObject>>().values;
    std::for_each(values.begin(), values.end(), [&items](AmfItemPtr value) {
        items.push_back(AMFConverter::convert(value->marker(), value));
    });
    return items;
}

QList<QVariant> fromAmfVecU(amf::AmfItemPtr item) {
    using namespace amf;
    QList<QVariant> items;
    std::vector<uint> values = item.as<AmfVector<uint>>().values;
    std::for_each(values.begin(), values.end(), [&items](uint value) {
        items.push_back(value);
    });
    return items;
}

QList<QVariant> fromAmfVecD(amf::AmfItemPtr item) {
    using namespace amf;
    QList<QVariant> items;
    std::vector<double> values = item.as<AmfVector<double>>().values;
    std::for_each(values.begin(), values.end(), [&items](double value) {
        items.push_back(value);
    });
    return items;
}

QHash<QString, QVariant> fromAmfDict(amf::AmfItemPtr item) {
    using namespace amf;
    QHash<QString, QVariant> hash;
    std::unordered_map<AmfItemPtr, AmfItemPtr, AmfDictionaryHash>& values =
            item.as<AmfDictionary>().values;
    std::for_each(values.begin(), values.end(), [&hash](std::pair<const AmfItemPtr, AmfItemPtr>& pair) {
        const AmfItemPtr& key = pair.first;
        AmfItemPtr& item = pair.second;
        hash.insert(QString::fromStdString(key.as<AmfString>().value),
                    AMFConverter::convert(item->marker(), item));
    });
    return hash;
}

QVariant AMFConverter::convert(amf::u8 type, amf::AmfItemPtr item) {
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
    case AMF_ARRAY: return QVariant(fromAmfArr(item));
    case AMF_OBJECT: return QVariant(fromAmfObj(item));
    case AMF_XML: return QVariant(QString::fromStdString(item.as<AmfXml>().value));
    case AMF_BYTEARRAY: return QVariant(fromAmfBytes(item));
    case AMF_VECTOR_INT: return QVariant(fromAmfVecI(item));
    case AMF_VECTOR_UINT: return QVariant(fromAmfVecU(item));
    case AMF_VECTOR_DOUBLE: return QVariant(fromAmfVecD(item));
    case AMF_VECTOR_OBJECT: return QVariant(fromAmfVec(item));
    case AMF_DICTIONARY: return QVariant(fromAmfDict(item));
    }
    return QVariant();
}

amf::AmfItemPtr AMFConverter::convert(amf::u8 type, QVariant &variant) {
    using namespace amf;
    return AmfItemPtr();
}

}