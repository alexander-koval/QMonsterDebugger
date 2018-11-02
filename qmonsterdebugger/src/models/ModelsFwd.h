#ifndef MODELSFWD_H
#define MODELSFWD_H

#include <QSharedPointer>

namespace monster {

class TraceModel;
class MonitorModel;
class SessionProxy;
class SessionDataModel;

using TraceModelPtr = QSharedPointer<TraceModel>;
using MonitorModelPtr = QSharedPointer<MonitorModel>;
using SessionDataPtr = QSharedPointer<SessionProxy>;
using SessionDataModelPtr = QSharedPointer<SessionDataModel>;

}


#endif // MODELSFWD_H
