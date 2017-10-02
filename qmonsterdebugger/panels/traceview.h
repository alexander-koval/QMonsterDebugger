#ifndef TRACEVIEW_H
#define TRACEVIEW_H

#include <QWidget>

namespace Ui {
class TraceView;
}

class QResizeEvent;

class TraceView : public QWidget
{
    Q_OBJECT
public:
    explicit TraceView(QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    Ui::TraceView* m_view;

signals:


public slots:
};

#endif // TRACEVIEW_H
