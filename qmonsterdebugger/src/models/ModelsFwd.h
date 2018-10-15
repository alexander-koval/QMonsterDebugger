#ifndef MODELSFWD_H
#define MODELSFWD_H

#include <QSharedPointer>

namespace monster {

class SessionData;
class SessionDataModel;

using SessionDataPtr = QSharedPointer<SessionData>;
using SessionDataModelPtr = QSharedPointer<SessionDataModel>;

}


#endif // MODELSFWD_H
