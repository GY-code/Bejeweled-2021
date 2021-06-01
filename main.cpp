#include "startpage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartPage w;
    w.show();

    return a.exec();
}
