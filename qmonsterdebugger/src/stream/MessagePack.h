#ifndef MESSAGEPACK_H
#define MESSAGEPACK_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QJsonDocument>
#include <QSharedPointer>
#include "amf/types/amfstring.hpp"
#include "amf/types/amfobject.hpp"

namespace monster {
class MessagePack
{
public:
    static MessagePack read(QByteArray& bytes);

    MessagePack();

    MessagePack(amf::AmfItemPtr id, amf::AmfItemPtr data);

    amf::AmfItemPtr getID() { return m_id; }

    amf::AmfItemPtr getData() { return m_data; }

    const amf::AmfItemPtr& getID() const { return m_id; }

    const amf::AmfItemPtr& getData() const { return m_data; }

    QSharedPointer<QByteArray> getBytes() const;

//    template< typename T >
//    T unpack( amf::AmfItemPtr item, const T& defVal = T() ) {
//        item.as<amf::AmfObject>().
//        if( var.isValid() && var.canConvert< T >() ) {
//            return var.value< T >();
//        }
//        return defVal;
//    }

private:
    amf::AmfItemPtr m_id;
    amf::AmfItemPtr m_data;
};

}
#endif // MESSAGEPACK_H
