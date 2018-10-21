#include "LoggerUtils.h"
#include <QRegExp>

namespace monster {
namespace logutils {

QString& stripBreaks(QString& s) {
    s.remove(QRegExp("[\\n,\\t,\\r]"));
    return s;
}

QString& htmlUnescape(QString& s) {
    s.replace("&apos;", "'");
    s.replace("&quot;", "\"");
    s.replace("&lt;", "<");
    s.replace("&gt;", ">");
    s.replace("&amp;", "&");
    return s;
}



}
}
