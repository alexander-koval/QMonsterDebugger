#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "ui_traceview.h"
#include "panels/tracemodel.h"
#include <QStringListModel>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_mainView(std::make_unique<Ui::MainWindow>())
{
    m_mainView->setupUi(this);

    MonsterTabWidget* tabBar = m_mainView->tabBar;
    QWidget* tabView = new QWidget(tabBar);

    TraceModel* model = new TraceModel(this);
//    QStringListModel* model = new QStringListModel(this);
    TraceViewPtr traceView(std::make_unique<Ui::TraceView>());
    traceView->setupUi(this);
    QTableView* tableView = traceView->tableView;
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    QStringList headerLabels;
//    headerLabels << "Title" << "Director" << "Year" << "Counter" << "Rating";

    tableView->setModel(model);
    QList<TraceItem*> items;
    TraceItem *item = new TraceItem();
    item->line = 0;
    items << item;
    model->insertRow(model->rowCount());
    model->insertColumn(model->columnCount());
    model->insertRow(model->rowCount());
    model->insertColumn(model->columnCount());
    model->insertRow(model->rowCount());
    model->insertColumn(model->columnCount());
    model->insertRow(model->rowCount());
    model->insertColumn(model->columnCount());
    model->setData(model->index(model->rowCount() - 1, 0), QVariant(2));
    model->setData(model->index(model->rowCount() - 1, 1), QVariant(2));
    model->setData(model->index(model->rowCount() - 1, 0), QVariant(2));
    model->setData(model->index(model->rowCount() - 1, 1), QVariant(2));
    model->setData(model->index(model->rowCount() - 1, 0), QVariant(2));
    model->setData(model->index(model->rowCount() - 1, 1), QVariant(2));
    model->setData(model->index(model->rowCount() - 1, 0), QVariant(2));
    model->setData(model->index(model->rowCount() - 1, 1), QVariant(2));

//    tabView->setStyleSheet("background-color: red;");
//    tabView->setStyleSheet("background-color:black;");
    tabBar->setObjectName(QStringLiteral("tabBar"));    
//    tabBar->setStyleSheet("QTabBar::tab { height: 30px; width: 100px; }");
    tabBar->addTab(tabView, "Home");
    tabBar->addTab(tableView, "Blood of Titans");
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
