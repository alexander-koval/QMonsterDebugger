#include "MainWindow.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QScopedPointer>
#include "stream/monsterserver.h"
#include "panels/TraceModel.h"

using monster::MainWindow;
using monster::MonsterServer;

int main(int argc, char *argv[])
{
    using namespace monster;
//    QApplication a(argc, argv);

//    MainWindow w;

    QGuiApplication app(argc, argv);    
    QQmlApplicationEngine engine;
    TraceModel* traceModel = new TraceModel(nullptr);
    traceModel->insertRow(traceModel->rowCount());
    traceModel->insertColumn(traceModel->columnCount());
    traceModel->setData(traceModel->index(0, 0), 392, TraceItem::Line);


    engine.rootContext()->setContextProperty("traceModel", traceModel);
    engine.load(QUrl("qrc:/qml/MainView.qml"));

//    monster::reset_main_window(&w);
    QScopedPointer<MonsterServer> server(new MonsterServer(&app));
    if (server->start()) {
//        w.connect(server.data(), &MonsterServer::sessionCreated,
//                  &w, &MainWindow::onSessionCreated,
//                  Qt::DirectConnection);
//        w.show();
    } else {
        qCritical() << "Unable to start the server";
    }

    return app.exec();
}
