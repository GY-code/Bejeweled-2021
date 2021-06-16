#ifndef DATABASE_H
#define DATABASE_H

#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "iostream"

using namespace::std;

typedef struct {
  QString username;
  QString password;
} user ;

typedef struct {
  QString username;
  int score;
  int rank;
} player;


class dataBase
{
public:
  dataBase();
  void update(QString username,int score);
  void inquire();
  QString showRankList();
  QString showUserRankList();
  vector<player> getPlayers();
  int readFromUsers(QString id,QString pwd);
  int readFromPlayers(QString id);
  int loginFunc(QString id,QString pwd);
  int registerFunc(QString id,QString pwd);
  player getPlayer();
  void setPlayer(player a);
  void setUser(user a);

private:
  vector<user> users;
  vector<player> players;
  user usr;
  player gamer;
};

#endif // DATABASE_H
