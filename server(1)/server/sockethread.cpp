#include "sockethread.h"
socketThread::socketThread(QTcpSocket * clientSocket, dataBase *database,int id)
{
    this->clientSocket = clientSocket;
    this->idThread = id;
    this->database = database;
    QObject::connect(clientSocket, &QTcpSocket::readyRead, this, &socketThread::readData);
    QObject::connect(clientSocket,&QTcpSocket::disconnected, this, &socketThread::disconnect);
}

void socketThread::readData() {
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
        content.append(QString::number(information).toLocal8Bit());
        qDebug() << "send: "<< content << " in NO." << idThread << " THREAD" << "\n";
        clientSocket->write(content);
    }
    if (instruction[0] == "VERIFY"){
        int information = database->loginFunc(instruction[1], instruction[2]);//0 unregistered 1 wrong password 2 successfully 4 has logined
        QByteArray content;
        content.append("VER_RESULT");
        content.append('&');
        content.append(QString::number(information).toLocal8Bit());
        qDebug() << "send: "<< content << " in NO." << idThread << " THREAD" << "\n";
        clientSocket->write(content);
    }
    if (instruction[0] == "PROFILE"){
        auto list = database->showUserRankList();
        QByteArray content;
        content.append("PRO_RESULT");
        content.append('&');
        content.append(list.toLocal8Bit());
        qDebug() << "send: "<< content << " in NO." << idThread << " THREAD" << "\n";
        clientSocket->write(content);
    }
    if (instruction[0] == "RANKLIST"){
        auto list = database->showRankList();
        QByteArray content;
        content.append("RAN_RESULT");
        content.append('&');
        content.append(list.toLocal8Bit());
        qDebug() << "send: "<< content << " in NO." << idThread << " THREAD" << "\n";
        clientSocket->write(content);
    }
    if (instruction[0] == "UPDATE"){
        database->update(instruction[1], instruction[2].toInt());
        qDebug() << "update: "<< instruction[1] << " " << instruction[2] << " in NO." << idThread << " THREAD" << "\n";
    }
}

void socketThread::disconnect() {
  qDebug() << "Disconnected NO." << idThread << " THREAD"<<"\n";
  this->terminate();
}

void socketThread::run() {

}

