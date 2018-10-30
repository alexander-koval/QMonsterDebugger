#ifndef TRACEITEM_H
#define TRACEITEM_H

#include <cstddef>
#include <QString>
#include <QObject>

namespace monster {

//class TraceName {
//    Q_GADGET
//public:
//    enum Enum {
//        Line = Qt::UserRole + 1, Time, Target, Message, Label, Person, Memory, Count
//    };
//    Q_ENUM(Enum)

//    explicit TraceName() = default;
//};

struct TraceItem
{
    Q_GADGET
public:
    enum TraceNames {Line = Qt::UserRole + 1, Time, Target, Message, Label, Person, Memory, Count};
    Q_ENUM(TraceNames)

    explicit TraceItem() = default;

    quint64 line{};
    QString time{};
    QString target{};
    QString message{};
    QString label{};
    QString memory{};
    QString person{};
};

}
#endif // TRACEITEM_H
