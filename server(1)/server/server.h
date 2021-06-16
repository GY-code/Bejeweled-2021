#ifndef SERVER_H
#define SERVER_H

#include "sockethread.h"
class server : public QObject
{
public:
    server();
private:
    QTcpServer * serverEnd;
    int numberOfThread;
    dataBase * database;
private slots:
    void clientHandler();
};

#endif // SERVER_H
