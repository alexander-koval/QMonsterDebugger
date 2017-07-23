#ifndef TRACEITEM_H
#define TRACEITEM_H

#include <cstddef>
#include <QString>

struct TraceItem
{
public:
    enum Names {Line, Time, Target, Message, Label, Person, Memory, Count};
    explicit TraceItem();

    quint64 line;
    QString time;
    QString target;
    QString message;
    QString label;
    QString memory;
    QString person;
};


#endif // TRACEITEM_H
