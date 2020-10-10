#include "pageswitchbase.h"
#include <QPainter>

PageSwitchBase::PageSwitchBase(QWidget *parent):
    QWidget (parent)
{

}

PageSwitchBase::PageSwitchBase(int w, int h, QWidget *parent):
    QWidget (parent)
{
    this->resize(w,h);
}

void PageSwitchBase::setBackgroundColor(const QString &color)
{
    m_bg = color;
    update();
}

void PageSwitchBase::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(),QColor(m_bg));

}
