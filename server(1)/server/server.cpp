#include "server.h"

server::server()
{

    serverEnd = new QTcpServer();
    numberOfThread = 0;
    QObject::connect(serverEnd, &QTcpServer::newConnection, this, &server::clientHandler);
    database = new dataBase();
    serverEnd->listen(QHostAddress::LocalHost,8888);
}

void server::clientHandler() {
    auto clientSocket = serverEnd->nextPendingConnection();
    qDebug() << "Connected! Allocate a thread." << "\n";
    (new socketThread(clientSocket, database,numberOfThread))->run();
    numberOfThread++;
}

