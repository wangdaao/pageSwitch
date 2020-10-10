#ifndef PAGESWITCHMANAGER_H
#define PAGESWITCHMANAGER_H

#include <QWidget>
#include <QBoxLayout>
#include "tlcontrolinterface.h"
#include <QPropertyAnimation>

class PageSwitchManager : public QWidget ,public  TLControlInterface{
    Q_OBJECT
public:
    explicit    PageSwitchManager(QSize size,TLControlInterface::MoveLimit,QWidget* parent = nullptr);
    void        insertWidget(QWidget* w);
    void        switchPage(int page);
    void        setMoveLimitState(TLControlInterface::MoveLimit direction);
    void        updateSize(QSize& size);

protected:
    void        mousePressEvent(QMouseEvent*);
    void        mouseMoveEvent(QMouseEvent*);
    void        mouseReleaseEvent(QMouseEvent *event);

private:
    void        init(TLControlInterface::MoveLimit type);
    void        triggerMoveEvent(const QPointF&);

private:
    QBoxLayout*         m_boxLayout = nullptr;
    QPointF             m_pointPress;
    QPointF             m_lastMovePos;
    QPropertyAnimation* m_animation = nullptr;
    QWidget*            m_currentPage = nullptr;
    QSize               m_size;

};

#endif // PAGESWITCHMANAGER_H
