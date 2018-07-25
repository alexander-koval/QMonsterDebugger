#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "panels/traceview.h"
#include "panels/StreamView.h"
#include "streaming/sessions/session.h"
#include "streaming/monsterserver.h"
#include <QResizeEvent>
#include <QAction>

namespace monster {
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_mainView(std::make_unique<Ui::MainWindow>()),
    m_traceView(std::make_unique<TraceView>(this)),
    m_streamView(std::make_unique<StreamView>(this)),
    m_server(nullptr)
{
    m_mainView->setupUi(this);

    MonsterTabWidget* tabBar = m_mainView->tabBar;
    QWidget* tabView = new QWidget(tabBar);
//    tabView->setStyleSheet("background-color: red;");
//    tabView->setStyleSheet("background-color:black;");
    tabBar->setObjectName(QStringLiteral("tabBar"));
    tabBar->addTab(tabView, "Home");
    tabBar->addTab(m_traceView.get(), "Blood of Titans");
    tabBar->addTab(m_streamView.get(), "File Stream");

    QMenu* menu = new QMenu("Edit", this);
    QAction* editAction = menu->addAction("Edit");
    connect(editAction, SIGNAL(triggered()), this, SLOT(onShowOptionsDialog()));
    this->menuBar()->addMenu(menu);
    menu = new QMenu("View", this);
    QAction* viewAction = menu->addAction("View");
    connect(viewAction, SIGNAL(triggered()), this, SLOT(onShowOptionsDialog()));
    this->menuBar()->addMenu(menu);
    menu = new QMenu("Extra", this);
    QAction* extraAction = menu->addAction("Options");
    connect(extraAction, SIGNAL(triggered()), this, SLOT(onShowOptionsDialog()));
    this->menuBar()->addMenu(menu);

    relayout();

}

MainWindow::~MainWindow() {
}

void MainWindow::onShowOptionsDialog()
{
    qDebug("SHOW_OPTIONS_DIALOG");
}

void MainWindow::onSessionCreated(MainWindow::SessionPtr session) {

    int kkk = 0;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    relayout();
}

void MainWindow::relayout() {
    MonsterTabWidget* tabBar = m_mainView->tabBar;
    tabBar->setGeometry(QRect(0, 0, this->width(), this->height()));
}
}
