#include "MainWindow.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWidget>
#include <QScopedPointer>
#include "stream/MonsterServer.h"
#include "models/TraceModel.h"
#include "controllers/MainMediator.h"
#include "models/SessionDataModel.h"
#include "stream/sessions/Sessions.h"
#include "Core.h"
#include "Repo.h"

using monster::MainWindow;
using monster::MonsterServer;

//class MonsterBootstrap : public QObject {
////Q_OBJECT
//public:
//    MonsterBootstrap(QQmlApplicationEngine* engine)
//        : QObject(), m_mediator(), m_engine(engine), m_server() {
//        connect(engine, &QQmlApplicationEngine::objectCreated,
//                this, &MonsterBootstrap::onObjectCreated);
//    }

//    void operator()() {
//        using monster::MainMediator;
//        m_engine->rootContext()->setContextProperty("mainMediator", &m_mediator);
//        m_server = QSharedPointer<MonsterServer>::create();
//        if (m_server->start()) {
//            m_mediator.connect(m_server.data(), &MonsterServer::sessionCreated,
//                                  &m_mediator, &MainMediator::onSessionCreated,
//                                  Qt::DirectConnection);
//        } else {
//            qCritical() << "Unable to start the server";
//        }
//    }

//public slots:
//    void onObjectCreated(QObject* object, const QUrl& url) {
//        m_mediator.init(object);
//        disconnect(m_engine, &QQmlApplicationEngine::objectCreated,
//                this, &MonsterBootstrap::onObjectCreated);
//    }

//private:
//    monster::MainMediator m_mediator;
//    QQmlApplicationEngine* m_engine;
//    QSharedPointer<MonsterServer> m_server;
//};


int main(int argc, char *argv[])
{
    using namespace monster;
//    qmlRegisterType<TraceModel>("DeMonsters.Debug", 1, 0, "TraceModel");
//    qmlRegisterUncreatableType<TraceItem>("DeMonsters.Debug", 1, 0, "TraceItem",
//                                          "Cannot create TraceName in QML");
    const char* uri = "DeMonsters.Debug";
    qmlRegisterType<monster::TraceModel>(uri, 1, 0, "TraceModel");
    qmlRegisterUncreatableType<monster::TraceItem>(uri, 1, 0, "TraceItem",
                                          "Cannot create TraceName in QML");

    qmlRegisterType(QUrl("qrc:qml/MainView.qml"), uri, 1, 0, "MainView");
    qmlRegisterType(QUrl("qrc:qml/TracePanel.qml"), uri, 1, 0, "MainView");


#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute( Qt::AA_UseSoftwareOpenGL );
#endif
    QApplication app(argc, argv);
    Core::start();
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("sessions", Core::sessions().data());
    engine.load(QUrl("qrc:/qml/MainView.qml"));

//    qmlRegisterType<TraceModel>("DeMonsters.Debug", 1, 0, "TraceModel");

//    QQmlApplicationEngine* engine = new QQmlApplicationEngine();
//    SessionDataModel* connectionModel = new SessionDataModel();

//    Repo::engine(engine);
//    Repo::connectionModel(connectionModel);

//    MonsterBootstrap bootstrap(engine);
//    bootstrap();

//    TraceModel* traceModel = new TraceModel(nullptr);
//    traceModel->insertRow(traceModel->rowCount());
//    traceModel->insertColumn(traceModel->columnCount());
//    traceModel->setData(traceModel->index(0, 0), 392, TraceItem::Line);

//    engine->rootContext()->setContextProperty("traceModel", traceModel);
//    engine->rootContext()->setContextProperty("connectionModel", connectionModel);

    return app.exec();
}
