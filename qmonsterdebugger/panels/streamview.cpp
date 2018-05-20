#include "streamview.h"
#include "ui_streamview.h"
#include <QResizeEvent>

namespace monster {

StreamView::StreamView(QWidget *parent)
    : QWidget(parent)
    , m_view(new Ui::StreamView())
{
    m_view->setupUi(this);
}

void StreamView::resizeEvent(QResizeEvent *event)
{
    const QSize& size = event->size();
    m_view->textEdit->resize(size.width(), size.height());
}

}
