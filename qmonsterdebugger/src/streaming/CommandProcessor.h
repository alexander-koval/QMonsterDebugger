#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H


class QString;
class QByteArray;
class QJsonDocument;

namespace monster {
class CommandProcessor
{
public:
    static void policyRequest(QByteArray* bytes);

    static void hello(QByteArray* bytes);

    static void encode(QByteArray& msg, QByteArray& bytes);

    static void decode(QString& id, QJsonDocument& data,
                       QByteArray& bytes);
};

}
#endif // COMMANDPROCESSOR_H
