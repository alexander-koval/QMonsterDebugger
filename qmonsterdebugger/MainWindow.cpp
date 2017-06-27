#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mainView(std::make_unique<Ui::MainWindow>())
{
    mainView->setupUi(this);
    QTabBar* tabBar = mainView->tabBar;
    QWidget* tabView = new QWidget(tabBar);
//    tabView->setStyleSheet("background-color:black;");
    tabBar->setObjectName(QStringLiteral("tabBar"));
    tabBar->setGeometry(QRect(0, 0, 1200, 800));
//    tabBar->setStyleSheet("QTabBar::tab { height: 30px; width: 100px; }");
    tabBar->addTab("Home");
    tabBar->setExpanding(false);
}

MainWindow::~MainWindow() {

}
