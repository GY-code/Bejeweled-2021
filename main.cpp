#include "startpage.h"
#include "gamewidget.h"
#include <QSplashScreen>
#include <QApplication>

#include "client.h"
Client *client;
void sleep(int msec){
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QImage image(":/picture/splash.jpg");
    QSize size(1920,1080);
    QImage image2=image.scaled(size,Qt::IgnoreAspectRatio);
    QSplashScreen splash(QPixmap::fromImage(image2));
    splash.setWindowFlag(Qt::WindowStaysOnTopHint);
    splash.showMessage("Loading client and networks...",Qt::AlignHCenter|Qt::AlignTop,Qt::white);
    splash.show();
    client = new Client();
    sleep(500);
    splash.showMessage("Loading widgets and display settings...",Qt::AlignHCenter|Qt::AlignTop,Qt::white);
    StartPage w;
    //GameWidget w;
    w.show();
    splash.showMessage("Loading finished...",Qt::AlignHCenter|Qt::AlignTop,Qt::white);
    sleep(500);

    splash.finish(&w);
    return a.exec();
}

