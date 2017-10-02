#ifndef STEAMVIEW_H
#define STEAMVIEW_H

#include <QWidget>

namespace Ui {
class StreamView;
}

class StreamView : public QWidget
{
    Q_OBJECT
public:
    explicit StreamView(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::StreamView* m_view;

signals:

public slots:
};

#endif // STEAMVIEW_H
