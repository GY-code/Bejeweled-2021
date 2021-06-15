#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "database.h"

class server : public QObject
{
public:
    server();
private:
    QTcpServer * serverEnd;
    QTcpSocket * clientSocket;
    dataBase * database;
private slots:
    void clientHandler();
    void readData();
    void disconnect();
};

#endif // SERVER_H
