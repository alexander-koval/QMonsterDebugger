#include "MainWindow.h"
#include <QApplication>
#include <QScopedPointer>
#include "stream/monsterserver.h"

using monster::MainWindow;
using monster::MonsterServer;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    monster::reset_main_window(&w);
    QScopedPointer<MonsterServer> server(new MonsterServer(&a));
    if (server->start()) {
        w.connect(server.data(), &MonsterServer::sessionCreated,
                  &w, &MainWindow::onSessionCreated,
                  Qt::DirectConnection);
        w.show();
    } else {
        qCritical() << "Unable to start the server";
    }

    return a.exec();
}
