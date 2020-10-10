//#include "widget.h"
#include <QApplication>
#include "pageswitch/pageswitchview.h"
#include "pageswitchbase.h"

#include <QByteArray>
#include <QCoreApplication>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTime>
#include <QJsonObject>
#include <QJsonDocument>
void Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PageSwitchView w(800,600,TLControlInterface::MoveLimit_X);

//    QUdpSocket qus;
//    QByteArray msg;

//    QJsonObject object;
//    object.insert("ticket","");
//    object.insert("type","test");
//    QJsonDocument rectJsonDoc;
//    rectJsonDoc.setObject(object);
//    msg = rectJsonDoc.toJson(QJsonDocument::Compact);
//    for(int i=0; i<3; ++i)
//    {
//        qDebug()<<"=============sendData:"<<msg.data();
//        qus.writeDatagram(msg.data(), QHostAddress::LocalHost, 12342);
////        Sleep(10000);
//    }

    PageSwitchBase bg1;
    PageSwitchBase bg2;
    bg2.setBackgroundColor("#59c2ca");

    PageSwitchBase bg3;
    bg3.setBackgroundColor("#667e5a");

    PageSwitchBase bg4;
    bg4.setBackgroundColor("#87a565");

    w.insertWidget(&bg1);
    w.insertWidget(&bg2);
    w.insertWidget(&bg3);
    w.insertWidget(&bg4);

    w.show();

    return a.exec();
}
