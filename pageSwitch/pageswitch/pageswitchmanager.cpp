#include "PageSwitchManager.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

PageSwitchManager::PageSwitchManager(QSize size,TLControlInterface::MoveLimit type,QWidget *parent):
    QWidget(parent),m_size(size)
{
    init(type);
}

void PageSwitchManager::insertWidget(QWidget *w)
{
    if(!m_currentPage)  m_currentPage = w;

    switch (moveLimit())
    {
    case MoveLimit_X:
        this->resize(m_size.width() * m_boxLayout->count(),m_size.height());
        break;
    case MoveLimit_Y:
        this->resize(m_size.width(),m_size.height() * m_boxLayout->count());
        break;
    }
    m_boxLayout->addWidget(w);
}

void PageSwitchManager::switchPage(int page)
{
    if(m_boxLayout->count() <=0) return;
    int index = page<0 ? 0:(page>m_boxLayout->count()-1 ? m_boxLayout->count()-1 : page);
    qDebug() << "===>lls<===" << __FUNCTION__ <<  index;
    m_currentPage = m_boxLayout->itemAt(index)->widget();
    m_animation->setStartValue(this->pos());
    m_animation->setEndValue(-m_currentPage->pos());
    m_animation->start();
}

void PageSwitchManager::setMoveLimitState(TLControlInterface::MoveLimit direction)
{
    setMoveLimit(direction);

    switch(direction)
    {
    case  MoveLimit_X:
        m_boxLayout->setDirection(QBoxLayout::LeftToRight);
        break;
    case MoveLimit_Y:
        m_boxLayout->setDirection(QBoxLayout::TopToBottom);
        break;

    default:{

    }
    }
}

void PageSwitchManager::updateSize(QSize &size)
{
    m_size = size;
    switch (moveLimit()){
    case MoveLimit_X:
        this->resize(m_size.width() * m_boxLayout->count(),m_size.height());
        break;
    case MoveLimit_Y:
        this->resize(m_size.width(),m_size.height() * m_boxLayout->count());
        break;
    }
//    for(int i = 0;i < m_boxLayout->count()-1;i++)
//    {
//        qDebug()<<"pos of "<<i<<"m_boxLayout============="<<m_boxLayout->itemAt(i)->widget()->pos();
//        qDebug()<<"width of "<<i<<"m_boxLayout============="<<m_boxLayout->itemAt(i)->widget()->width();
//        qDebug()<<"height of "<<i<<"m_boxLayout============="<<m_boxLayout->itemAt(i)->widget()->height();
//    }
    qDebug() << "===================" << m_currentPage->pos();
    switchPage(m_boxLayout->indexOf(m_currentPage));
}

void PageSwitchManager::mousePressEvent(QMouseEvent *event)
{
    if(m_animation->state() == QAbstractAnimation::Running) m_animation->stop();

    m_pointPress = event->screenPos();
    m_lastMovePos = m_pointPress;
    setDragMode(Mode_Click);
}

void PageSwitchManager::mouseMoveEvent(QMouseEvent *event)
{
    if(dragMode() == Mode_Click || dragMode() == Mode_NoDrag )
    {
        if(qAbs(m_pointPress.y() - event->screenPos().y()) > modeChangeThreshold() ){
            if(m_pointPress.y() > event->screenPos().y()){
                setDragMode(Mode_DragY_ToBottom);
            }else{
                setDragMode(Mode_DragY_ToTop);
            }
        }else if(qAbs(m_pointPress.x() - event->screenPos().x()) > modeChangeThreshold()){
            if(m_pointPress.x() > event->screenPos().x()){
                setDragMode(Mode_DragX_ToLeft);
            }else{
                setDragMode(Mode_DragX_ToRight);
            }
        }
    }else if(dragMode() >= Mode_DragX_ToLeft){
        triggerMoveEvent(event->screenPos());
    }
}

void PageSwitchManager::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_pointPress == m_lastMovePos) return;

    switch (moveLimit()){
    case MoveLimit_X:
    {
        int instance =  m_lastMovePos.x() - m_pointPress.x();
        if(qAbs(instance) > m_size.width()/3)
        {
            if(instance >0)
            {
                switchPage(m_boxLayout->indexOf(m_currentPage) - 1);
            }
            else {
                switchPage(m_boxLayout->indexOf(m_currentPage) + 1);
            }
        }
        else
        {
             switchPage(m_boxLayout->indexOf(m_currentPage));
        }
    }
        break;

    case MoveLimit_Y:
        int instance =  m_lastMovePos.y() - m_pointPress.y();
        if(qAbs(instance) > m_size.height()/3)
        {
            if(instance >0)
            {
                switchPage(m_boxLayout->indexOf(m_currentPage) - 1);
            }
            else {
                switchPage(m_boxLayout->indexOf(m_currentPage) + 1);
            }
        }
        else
        {
             switchPage(m_boxLayout->indexOf(m_currentPage));
        }
        break;

    }
}

void PageSwitchManager::init(TLControlInterface::MoveLimit type)
{
    m_boxLayout = new QBoxLayout(QBoxLayout::LeftToRight,this);
    m_boxLayout->setMargin(0);
    m_boxLayout->setSpacing(0);
    setMoveFlag(TLControlInterface::Flag_MoveSelf);
    setMoveLimitState(type);

    m_animation = new QPropertyAnimation(this,"pos",this);
    m_animation->setDuration(800);
    m_animation->setEasingCurve(QEasingCurve::OutQuart);
}

void PageSwitchManager::triggerMoveEvent(const QPointF &currentPos)
{
    QPoint p;
    if(moveLimit() & MoveLimit_X){
        p.setX((currentPos - m_lastMovePos).x());
    }
    if(moveLimit() & MoveLimit_Y){
        p.setY((currentPos - m_lastMovePos).y());
    }
    m_lastMovePos = currentPos;
    if(moveFlag()  == Flag_MoveSelf){
        this->move(this->pos().x() + p.x(),this->pos().y() + p.y());
    }else if(moveFlag() == Flag_MoveByOutSide){
//        emit sigMoveByAsk(p);
    }

}
