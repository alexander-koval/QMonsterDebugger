#include "MainWindow.hpp"
#include <QApplication>
#include <memory>
#include "streaming/monsterserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    std::unique_ptr<MonsterServer> server = std::make_unique<MonsterServer>(&a);
    if (server->start()) {
        w.show();
    } else {
        qCritical() << "Unable to start the server";
    }

    return a.exec();
}
