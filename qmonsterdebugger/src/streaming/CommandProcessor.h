#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "amf/utils/amfitemptr.hpp"

class QString;
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

    static void decode(amf::AmfString& id, amf::AmfObject& data,
                       QByteArray& bytes);

    static amf::v8 serialize(const char* command);

    static amf::AmfItemPtr deserialize(const QByteArray& bytes);
};

}
#endif // COMMANDPROCESSOR_H
