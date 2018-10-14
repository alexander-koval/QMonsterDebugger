#include "MainWindow.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <QScopedPointer>
#include "stream/monsterserver.h"
#include "panels/TraceModel.h"
#include "controllers/MainMediator.h"
#include "models/ConnectionModel.h"
#include "Repo.h"

using monster::MainWindow;
using monster::MonsterServer;

class MonsterBootstrap : public QObject {
//Q_OBJECT
public:
    MonsterBootstrap(QQmlApplicationEngine* engine)
        : QObject(), m_mediator(), m_engine(engine), m_server() {
        connect(engine, &QQmlApplicationEngine::objectCreated,
                this, &MonsterBootstrap::onObjectCreated);
    }

    void operator()() {
        using monster::MainMediator;
        m_engine->rootContext()->setContextProperty("mainMediator", &m_mediator);
        m_server = QSharedPointer<MonsterServer>::create();
        if (m_server->start()) {
            m_mediator.connect(m_server.data(), &MonsterServer::sessionCreated,
                                  &m_mediator, &MainMediator::onSessionCreated,
                                  Qt::DirectConnection);
        } else {
            qCritical() << "Unable to start the server";
        }
    }

public slots:
    void onObjectCreated(QObject* object, const QUrl& url) {
        m_mediator.init(object);
        disconnect(m_engine, &QQmlApplicationEngine::objectCreated,
                this, &MonsterBootstrap::onObjectCreated);
    }

private:
    monster::MainMediator m_mediator;
    QQmlApplicationEngine* m_engine;
    QSharedPointer<MonsterServer> m_server;
};


int main(int argc, char *argv[])
{
    using namespace monster;
    QGuiApplication app(argc, argv);    

    qmlRegisterType<TraceModel>("DeMonsters.Debug", 1, 0, "TraceModel");
    qmlRegisterType<ConnectionItem>("DeMonsters.Debug", 1, 0, "ConnectionItem");

    QQmlApplicationEngine* engine = new QQmlApplicationEngine();
    ConnectionModel* connectionModel = new ConnectionModel();

    Repo::engine(engine);
    Repo::connectionModel(connectionModel);

    MonsterBootstrap bootstrap(engine);
    bootstrap();

    TraceModel* traceModel = new TraceModel(nullptr);
    traceModel->insertRow(traceModel->rowCount());
    traceModel->insertColumn(traceModel->columnCount());
    traceModel->setData(traceModel->index(0, 0), 392, TraceItem::Line);

    engine->rootContext()->setContextProperty("traceModel", traceModel);
    engine->rootContext()->setContextProperty("connectionModel", connectionModel);

    engine->load(QUrl("qrc:/qml/MainView.qml"));

    return app.exec();
}
