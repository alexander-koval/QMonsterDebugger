#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QSharedPointer>

class QQuickWidget;

namespace monster {
class Session;
class MonsterServer;
class MessagePack;
class MainMediator : public QObject
{
    Q_OBJECT
    using SessionPtr = QSharedPointer<Session>;
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
    SessionPtr m_session;
};

}

#endif // MAINCONTROLLER_H
