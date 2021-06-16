#ifndef SOCKETHREAD_H
#define SOCKETHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include "database.h"
#include <QString>
#include <QByteArray>
class socketThread : public QThread
{
    Q_OBJECT
public:
    socketThread(QTcpSocket * clientSocket, dataBase * database,int id);
    void run();
private slots:
    void readData();
    void disconnect();
private:
    QTcpSocket * clientSocket;
    dataBase * database;
    int idThread;
};

#endif // SOCKETHREAD_H
