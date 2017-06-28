#ifndef MONSTERTABWIDGET_HPP
#define MONSTERTABWIDGET_HPP

#include <QTableWidget>

class QTabBar;
class QStackedWidget;
class MonsterTabWidget : public QWidget {
    Q_OBJECT
public:
    explicit MonsterTabWidget(QWidget* parent = nullptr);
    MonsterTabWidget(const MonsterTabWidget& that) = delete;
    virtual ~MonsterTabWidget();

    int addTab(QWidget* widget, const QString& label);
    int addTab(QWidget* widget, const QIcon& icon, const QString& label);

    int insertTab(int index, QWidget* widget, const QString& label);
    int insertTab(int index, QWidget* widget, const QIcon& icon, const QString& label);

    MonsterTabWidget& operator =(const MonsterTabWidget& that) = delete;

    void resizeEvent(QResizeEvent* e);

    void relayout();

public slots:
    void onTabClicked(int index);

private:

private:
    QStackedWidget* m_stack;
    QTabBar* m_tabBar;
    QRect m_panelRect;
    bool m_dirty;
    QTabWidget::TabShape m_shape;
    QTabWidget::TabPosition m_pos;
    int m_alignment;
};

#endif // MONSTERTABWIDGET_HPP
