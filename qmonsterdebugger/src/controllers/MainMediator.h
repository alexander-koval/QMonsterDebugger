#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QSharedPointer>
#include <QVector>
#include <QAbstractTableModel>
#include "stream/StreamFwd.h"

class QQuickWidget;

namespace monster {
class TraceModel;
using TraceModelPtr = QSharedPointer<TraceModel>;
class MainMediator : public QObject
{
    Q_OBJECT
public:
    MainMediator();

    void init(QObject* mainView);

signals:
    void sessionCreated(QString title);

public slots:
    void onShowOptionsDialog();
    void onSessionCreated(SessionPtr session);
    void onInboundMessage(MessagePack& message);
private:
    QObject* m_mainView;
    QVector<TraceModelPtr> m_traceModels;
    SessionPtr m_session;
};

}

#endif // MAINCONTROLLER_H
