#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <QByteArray>

class Session
{
public:
    explicit Session();

    bool connected() const;

    void write(const QByteArray& msg);

    void close();

    const std::string& getAddress() const;

};

#endif // SESSION_H
