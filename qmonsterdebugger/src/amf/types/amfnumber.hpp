#ifndef AMFNUMBER_H
#define AMFNUMBER_H

#include "types/amfitem.hpp"

namespace amf {
class AmfNumber : public AmfItem {
public:
    virtual operator double() const = 0;

    virtual operator int() const = 0;
};
}

#endif // AMFNUMBER_H
