#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "amf/utils/amfitemptr.hpp"
#include "stream/MessagePack.h"
#include <QMap>

class QString;
class QVariant;
class QByteArray;
class QJsonDocument;

namespace amf {
    class AmfString;
    class AmfObject;
}

namespace monster {
class CommandProcessor
{
public:
    static void policyRequest(QByteArray* bytes);

    static void hello(QByteArray* bytes);

    static void base(QByteArray *bytes);

    static void encode(QByteArray& msg, QByteArray& bytes);

    static QSharedPointer<QByteArray> encode(const MessagePack& pack);

    static MessagePack decode(QByteArray& bytes);

    static amf::v8 serialize(const char* cmd);

    static amf::v8 serialize(const amf::AmfItemPtr& item);

    static amf::AmfItemPtr deserialize(const QByteArray& bytes);
};

}
#endif // COMMANDPROCESSOR_H
