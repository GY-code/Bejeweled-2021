#include "startpage.h"
#include "gamewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //StartPage w;
    GameWidget w;
    w.show();

    return a.exec();
}
