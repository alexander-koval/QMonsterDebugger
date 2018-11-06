#ifndef MONSTERAPPLICATION_H
#define MONSTERAPPLICATION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "stream/StreamFwd.h"
#include "models/ModelsFwd.h"

namespace monster {

class Core : public QObject {
    Q_OBJECT
public:
    explicit Core();

    static void start();

    static Core& core();

    static MonsterServerPtr server();

    static SessionDataModelPtr sessions();

    static const QDateTime& getStartTime();

    static QDateTime getCurrentTime();

public slots:
    void onSessionCreated(SessionPtr session);
    void onInboundMessage(MessagePack& message);

//private:
//    static MonsterServerPtr _server;
//    static SessionDataModelPtr _sessions;
};

}

#endif // MONSTERAPPLICATION_H
