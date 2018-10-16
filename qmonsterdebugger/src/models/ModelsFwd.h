#ifndef MODELSFWD_H
#define MODELSFWD_H

#include <QSharedPointer>

namespace monster {

class SessionProxy;
class SessionDataModel;

using SessionDataPtr = QSharedPointer<SessionProxy>;
using SessionDataModelPtr = QSharedPointer<SessionDataModel>;

}


#endif // MODELSFWD_H
