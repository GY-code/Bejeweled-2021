#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>
class Client:public QObject
{
  Q_OBJECT
public:
  Client();
  bool registerNewUser(QString userName, QString password);
  bool verifyUser(QString userName, QString password);
  void getProfile();
  void getRankList();
  void update(int score);
  QString ranklist;
  QString userlist;
  int verifyFlag;
  int registerFlag;
private:
  QTcpSocket * socket;
  QString username;
  QString password;
private slots:
  void readDataSlot();
};

#endif // CLIENT_H
