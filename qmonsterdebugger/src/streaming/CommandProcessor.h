#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

class QByteArray;

namespace monster {

class CommandProcessor
{
public:
    static void policyRequest(QByteArray* bytes);

    static void hello(QByteArray* bytes);

    static void package(QByteArray& msg, QByteArray& bytes);
};

}
#endif // COMMANDPROCESSOR_H
