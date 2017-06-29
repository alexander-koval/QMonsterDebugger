#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_mainView(std::make_unique<Ui::MainWindow>())
{
    m_mainView->setupUi(this);
    MonsterTabWidget* tabBar = m_mainView->tabBar;
    QWidget* tabView = new QWidget(tabBar);
//    tabView->setStyleSheet("background-color: red;");
//    tabView->setStyleSheet("background-color:black;");
    tabBar->setObjectName(QStringLiteral("tabBar"));    
//    tabBar->setStyleSheet("QTabBar::tab { height: 30px; width: 100px; }");
    tabBar->addTab(tabView, "Home");
    tabBar->addTab(new QWidget(), "Blood of Titans");
    relayout();
}

MainWindow::~MainWindow() {

}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    relayout();
}

void MainWindow::relayout() {
    MonsterTabWidget* tabBar = m_mainView->tabBar;
    tabBar->setGeometry(QRect(0, 0, this->width(), this->height()));
}
