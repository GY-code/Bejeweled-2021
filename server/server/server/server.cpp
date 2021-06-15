#include "server.h"

server::server()
{
    database = new dataBase();
    serverEnd = new QTcpServer();
    QObject::connect(serverEnd, &QTcpServer::newConnection, this, &server::clientHandler);

    serverEnd->listen(QHostAddress::LocalHost,8888);
}

void server::clientHandler() {
    clientSocket = serverEnd->nextPendingConnection();
    QObject::connect(clientSocket, &QTcpSocket::readyRead, this, &server::readData);
    QObject::connect(clientSocket,&QTcpSocket::disconnected, this, &server::disconnect);
}

void server::readData() {
    QString buffer = clientSocket->readAll();
    qDebug() << buffer << "\n";
    QStringList instruction = buffer.split('&');
    for(int i = 0; i < instruction.size(); i++) {
        qDebug() << instruction[i] << "\n";
    }
    if (instruction[0] == "REGISTER"){
        int information = database->registerFunc(instruction[1], instruction[2]);//0 registered 1 unregistered
        QByteArray content;
        content.append("REG_RESULT");
        content.append('&');
        content.append(QString::number(information));
        
        clientSocket->write(content);
    }
    if (instruction[0] == "VERIFY"){
        int information = database->loginFunc(instruction[1], instruction[2]);//0 unregistered 1 wrong password 2 successfully 4 has logined
        QByteArray content;
        content.append("VER_RESULT");
        content.append('&');
        content.append(QString::number(information));
        qDebug() << "send: "<< content << "\n";
        clientSocket->write(content);
    }
    if (instruction[0] == "PROFILE"){
        auto list = database->showUserRankList();
        QByteArray content;
        content.append("PRO_RESULT");
        content.append('&');
        content.append(list);
        qDebug() << "send: "<< content << "\n";
        clientSocket->write(content);
    }
    if (instruction[0] == "RANKLIST"){
        auto list = database->showRankList();
        QByteArray content;
        content.append("RAN_RESULT");
        content.append('&');
        content.append(list);
        qDebug() << "send: "<< content << "\n";
        clientSocket->write(content);
    }
    if (instruction[0] == "UPDATE"){
        database->update(instruction[1], instruction[2].toInt());
    }
}

void server::disconnect() {
  qDebug() << "Disconnected" << "\n";
}

