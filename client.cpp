#include "client.h"

Client::Client()
{
  socket = new QTcpSocket();
  QObject::connect(socket,&QTcpSocket::readyRead,this,&Client::readDataSlot);
  logined = false;

}

bool Client::registerNewUser(QString userName, QString password){
    socket->connectToHost("127.0.0.1",8888);
  this->username = userName;
  this->password = password;
  QByteArray content;
  content.append("REGISTER");
  content.append('&');
  content.append(userName.toLocal8Bit());
  content.append('&');
  content.append(password.toLocal8Bit());
  socket->write(content);

  if(socket->waitForReadyRead(1000)==false){
  }
  return false;
}

bool Client::verifyUser(QString userName, QString password){
    socket->connectToHost("127.0.0.1",8888);
  this->username = userName;
  this->password = password;
  QByteArray content;
  content.append("VERIFY");
  content.append('&');
  content.append(userName.toLocal8Bit());
  content.append('&');
  content.append(password.toLocal8Bit());
  socket->write(content);
  if(socket->waitForReadyRead(1000)==false){
  }
}
void Client::getProfile(){
    socket->connectToHost("127.0.0.1",8888);
  QByteArray content;
  content.append("PROFILE");
  socket->write(content);
  if(socket->waitForReadyRead(1000)==false){
  }
}

void Client::getRankList() {
    socket->connectToHost("127.0.0.1",8888);
  QByteArray content;
  content.append("RANKLIST");
  socket->write(content);
  if(socket->waitForReadyRead(1000)==false){
  }
}

void Client::readDataSlot() {
  auto buffer = socket->readAll();
  auto instruction = buffer.split('&');
  for(int i = 0; i < instruction.size(); i++) {
    qDebug() << instruction[i] << "\n";
  }
  if (instruction[0] == "REG_RESULT"){
    registerFlag = instruction[1].toInt();
  }
  if (instruction[0] == "VER_RESULT"){
    verifyFlag = instruction[1].toInt();
  }
  if (instruction[0] == "PRO_RESULT"){
    userlist = instruction[1];
  }
  if (instruction[0] == "RAN_RESULT"){
    ranklist = instruction[1];
  }
  if (instruction[0] == "UPD_RESULT"){

  }
  socket->abort();
}

void Client::update(int score) {
  socket->connectToHost("127.0.0.1",8888);
  QByteArray content;
  content.append("UPDATE");
  content.append('&');
  content.append(username.toLocal8Bit());
  content.append('&');
  content.append(QString::number(score).toLocal8Bit());
  qDebug() << content << "\n";
  socket->write(content);
}
