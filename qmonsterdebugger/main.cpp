#include "MainWindow.hpp"
#include <QApplication>
#include <QScopedPointer>
#include "streaming/monsterserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QScopedPointer<MonsterServer> server(new MonsterServer(&a));
    if (server->start()) {
        w.show();
    } else {
        qCritical() << "Unable to start the server";
    }

    return a.exec();
}
