#ifndef PAGESWITCHBASE_H
#define PAGESWITCHBASE_H

#include <QWidget>

class PageSwitchBase : public QWidget{
    Q_OBJECT
public:
    explicit PageSwitchBase(QWidget* parent = nullptr);
    explicit PageSwitchBase(int w,int h,QWidget* parent = nullptr);

    void setBackgroundColor(const QString& color);



protected:
    void paintEvent(QPaintEvent*);

private:
    QString     m_bg = "#242424";

};



#endif // PAGESWITCHBASE_H
