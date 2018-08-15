#include "MonsterTabWidget.h"
#include <QStackedWidget>
#include <QTabBar>
#include <QResizeEvent>
#include <QBoxLayout>

MonsterTabWidget::MonsterTabWidget(QWidget* parent /*= nullptr*/)
    : QWidget(parent),
      m_stack(new QStackedWidget(this)),
      m_tabBar(new QTabBar(this)),
      m_panelRect(),
      m_dirty(true),
      m_shape(QTabWidget::Rounded),
      m_pos(QTabWidget::North),
      m_alignment(0) {
//    const QRect& geom = geometry();
    m_tabBar->setObjectName(QStringLiteral("tabBar"));
    m_tabBar->setEnabled(true);
//    m_tabBar->setGeometry(geom);
    m_tabBar->setMinimumSize(minimumSize());
    m_tabBar->setExpanding(false);
    m_tabBar->setDrawBase(false);
//    m_stack->setVisible(false);
//    const QRect& barGeom = m_tabBar->geometry();
    m_stack->setObjectName(QStringLiteral("stack"));
    m_stack->setEnabled(true);
//    m_stack->setGeometry(geom);
    m_stack->setMinimumSize(minimumSize());
    setVisible(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_tabBar);
    layout->addWidget(m_stack);
    setLayout(layout);

    connect(m_tabBar, &QTabBar::currentChanged, this,
            &MonsterTabWidget::onCurrentChanged);
}

MonsterTabWidget::~MonsterTabWidget() {

}

int MonsterTabWidget::addTab(QWidget* widget, const QString& label) {
    return insertTab(-1, widget, label);
}

int MonsterTabWidget::addTab(QWidget* widget, const QIcon& icon, const QString& label) {
    return insertTab(-1, widget, icon, label);
}

int MonsterTabWidget::insertTab(int index, QWidget* widget, const QString& label) {
    index = m_tabBar->insertTab(index, label);
    m_stack->insertWidget(index, widget);
    relayout();
    return index;
}

int MonsterTabWidget::insertTab(int index, QWidget* widget, const QIcon& icon, const QString& label) {
    index = m_tabBar->insertTab(index, icon, label);
    m_stack->insertWidget(index, widget);
    relayout();
    return index;
}

void MonsterTabWidget::resizeEvent(QResizeEvent* e) {
    qDebug("W: %d H: %d", e->size().width(), e->size().height());
    QWidget::resizeEvent(e);
    relayout();
}

void MonsterTabWidget::relayout() {
//    if (isVisible()) {
//        const QRect& geom = geometry();
//        qDebug("x %d y %d width %d height %d",
//               geom.x(), geom.y(), geom.width(), geom.height());
//        m_tabBar->setGeometry(geom);
//        m_tabBar->updateGeometry();
//        qDebug("X: %d Y: %d WIDTH %d HEIGHT %d", m_tabBar->geometry().x(), m_tabBar->geometry().y(),
//               m_tabBar->geometry().width(), m_tabBar->geometry().height());
//        m_stack->setGeometry(geom);
//        m_stack->updateGeometry();
//        updateGeometry();
//    } else {
//        m_dirty = true;
//    }
}

void MonsterTabWidget::onCurrentChanged(int index) {
    qDebug("index %d", index);
    m_stack->setCurrentIndex(index);
}
