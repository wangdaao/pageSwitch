#include "pageswitchview.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

PageSwitchView::PageSwitchView(QWidget *parent):
    QWidget (parent)
{
    m_pushButton  = new QPushButton();
    m_pushButton->resize(100,50);
    m_pushButton->setText("Clicked");
    m_pushButton->setStyleSheet("QPushButton{background:yellow}");
    init();
}

PageSwitchView::PageSwitchView(int w, int h, TLControlInterface::MoveLimit type, QWidget *parent):
    QWidget(parent),m_moveType(type)
{
    this->resize(w,h);
    m_size = QSize(w,h);
    init();
}


void PageSwitchView::insertWidget(QWidget *w)
{
    m_switchManager->insertWidget(w);
}

void PageSwitchView::switchPage(int page)
{
    m_switchManager->switchPage(page);
}

void PageSwitchView::setMoveLimit(TLControlInterface::MoveLimit direction)
{
    m_switchManager->setMoveLimitState(direction);
}

void PageSwitchView::resizeEvent(QResizeEvent *)
{
    m_size = this->size();
   qDebug()<<"width of PageSwitchView'pos"<<this->width();
   qDebug()<<"height of PageSwitchView'pos"<<this->height();
    m_switchManager->updateSize(m_size);
}


void PageSwitchView::init()
{
    m_switchManager = new PageSwitchManager(m_size,m_moveType,this);
}


