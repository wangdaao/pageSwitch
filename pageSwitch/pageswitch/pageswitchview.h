#ifndef PAGESWITCHVIEW_H
#define PAGESWITCHVIEW_H

#include <QWidget>
#include<QPushButton>
#include "pageswitchmanager.h"

class PageSwitchView : public QWidget{
    Q_OBJECT
public:
    explicit    PageSwitchView(QWidget* parent = nullptr);
    explicit    PageSwitchView(int w,int h,TLControlInterface::MoveLimit type,QWidget* parent = nullptr);
    void        insertWidget(QWidget* w);
    void        switchPage(int page);
    void        setMoveLimit(TLControlInterface::MoveLimit direction);

protected:
    void resizeEvent(QResizeEvent*);

private:
    void        init();

private:
    QSize               m_size;
    PageSwitchManager*  m_switchManager = nullptr;
    TLControlInterface::MoveLimit  m_moveType;
    QPushButton* m_pushButton = nullptr;
};


#endif // PAGESWITCHVIEW_H
