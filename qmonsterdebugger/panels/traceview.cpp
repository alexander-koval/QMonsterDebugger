#include "traceview.h"
#include "ui_traceview.h"
#include "panels/tracemodel.h"
#include <QStringListModel>
#include <QResizeEvent>

TraceView::TraceView(QWidget *parent)
    : QWidget(parent)
    , m_view(new Ui::TraceView())
{
    m_view->setupUi(this);
    TraceModel* traceModel = new TraceModel(this);

    QList<TraceItem*> items;
    TraceItem *item = new TraceItem();
    item->line = 0;
    QStringList headerLabels;
    headerLabels << "Title" << "Director" << "Year" << "Counter" << "Rating";
    items << item;

    QStringListModel* model = new QStringListModel(this);
    model->setStringList(headerLabels);
    traceModel->insertRow(traceModel->rowCount());
    traceModel->insertColumn(traceModel->columnCount());
    traceModel->insertRow(traceModel->rowCount());
    traceModel->insertColumn(traceModel->columnCount());
    traceModel->insertRow(traceModel->rowCount());
    traceModel->insertColumn(traceModel->columnCount());
    traceModel->insertRow(traceModel->rowCount());
    traceModel->insertColumn(traceModel->columnCount());
    traceModel->setData(traceModel->index(traceModel->rowCount() - 1, 0), QVariant(2));
    traceModel->setData(traceModel->index(traceModel->rowCount() - 1, 1), QVariant(2));
    traceModel->setData(traceModel->index(traceModel->rowCount() - 1, 0), QVariant(2));
    traceModel->setData(traceModel->index(traceModel->rowCount() - 1, 1), QVariant(2));
    traceModel->setData(traceModel->index(traceModel->rowCount() - 1, 0), QVariant(2));
    traceModel->setData(traceModel->index(traceModel->rowCount() - 1, 1), QVariant(2));
    traceModel->setData(traceModel->index(traceModel->rowCount() - 1, 0), QVariant(2));
    traceModel->setData(traceModel->index(traceModel->rowCount() - 1, 1), QVariant(2));

    QTableView* tableView = m_view->tableView;
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->setModel(traceModel);
}

void TraceView::resizeEvent(QResizeEvent *event)
{
    const QSize& size = event->size();
    m_view->tableView->resize(size.width(), size.height());
}


