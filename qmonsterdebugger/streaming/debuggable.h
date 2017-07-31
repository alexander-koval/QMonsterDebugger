#ifndef IDEBUGGABLE_H
#define IDEBUGGABLE_H

#include <string>
#include <qglobal.h>

class Debuggable {
public:
    virtual quint64 getId() const = 0;

    virtual const std::string& getName() const = 0;

    virtual const std::string& getType() const = 0;
};

#endif // IDEBUGGABLE_H
