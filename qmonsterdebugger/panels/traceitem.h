#ifndef TRACEITEM_H
#define TRACEITEM_H

#include <cstddef>
#include <QString>

struct TraceItem
{
public:
    enum Names {Line, Time, Memory, Target, Label, Person, Count};
    explicit TraceItem();

    quint64 line;
    QString time;
    QString memory;
    QString target;
    QString label;
    QString person;
};


#endif // TRACEITEM_H
