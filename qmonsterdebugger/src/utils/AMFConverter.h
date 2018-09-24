#ifndef AMFCONVERTER_H
#define AMFCONVERTER_H

#include <QVariant>
#include "amf/utils/amfitemptr.hpp"

namespace monster {

class AMFConverter {
public:
    static QVariant convert(amf::u8 type, amf::AmfItemPtr item);

    static amf::AmfItemPtr convert(QVariant::Type type, QVariant& variant);
};

}
#endif // AMFCONVERTER_H
