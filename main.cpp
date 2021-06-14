#include "startpage.h"
#include "gamewidget.h"
#include <QApplication>

#include "client.h"
Client *client;

int main(int argc, char *argv[])
{
  client = new Client();
    QApplication a(argc, argv);
    StartPage w;
    //GameWidget w;
    w.show();

    return a.exec();
}
