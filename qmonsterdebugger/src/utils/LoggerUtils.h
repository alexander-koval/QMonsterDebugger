#ifndef LOGGERUTILS_H
#define LOGGERUTILS_H

#include <string>
#include <QString>
#include <QStringRef>

namespace monster {
namespace logutils {

QString& stripBreaks(QString&);

QString& htmlUnescape(QString&);

}
}

#endif // LOGGERUTILS_H
