#include "database.h"

dataBase::dataBase()
{

  QSqlDatabase database = *new QSqlDatabase;
  database = QSqlDatabase::addDatabase("QSQLITE");
  database.setDatabaseName("bwjgame.db");
  if (!database.open())
  {
    qDebug() << "Error: Failed to connect database." << database.lastError();
  }
  else
  {
    qDebug() << "Succeed to connect database." ;
  }
    QSqlQuery sql_query;

//    if(!sql_query.exec("create table users(id VARCHAR(20), password VARCHAR(20))"))
//    {
//      qDebug() << "Error: Fail to create table."<< sql_query.lastError();
//    }
//    else
//    {
//      qDebug() << "users Table created!";
//    }


//    if(!sql_query.exec("create table players(id VARCHAR(20), INTEGER score, INTERGER rank)"))
//    {
//      qDebug() << "Error: Fail to create table."<< sql_query.lastError();
//    }
//    else
//    {
//      qDebug() << "players Table created!";
//    }

//          QString insert_sql = "insert into users values (?, ?)";
//          sql_query.prepare(insert_sql);
//          sql_query.addBindValue("Liu");
//          sql_query.addBindValue("456");
//          if(!sql_query.exec())
//          {
//            qDebug() << sql_query.lastError();
//          }
//          else
//          {
//            qDebug() << "inserted Liu!";
//          }

//          QString insert_sql1 = "insert into players values (?, ?,?)";
//          sql_query.prepare(insert_sql1);
//          sql_query.addBindValue("Liu");
//          sql_query.addBindValue(30000);
//          sql_query.addBindValue(2);
//          if(!sql_query.exec())
//          {
//            qDebug() << sql_query.lastError();
//          }
//          else
//          {
//            qDebug() << "inserted score!";
//          }


//          QString insert_sql2 = "insert into users values (?, ?)";
//          sql_query.prepare(insert_sql2);
//          sql_query.addBindValue("Wu");
//          sql_query.addBindValue("123");
//          if(!sql_query.exec())
//          {
//            qDebug() << sql_query.lastError();
//          }
//          else
//          {
//            qDebug() << "inserted Liu!";
//          }

//          QString insert_sql3 = "insert into players values (?, ?,?)";
//          sql_query.prepare(insert_sql3);
//          sql_query.addBindValue("Wu");
//          sql_query.addBindValue(40000);
//          sql_query.addBindValue(1);
//          if(!sql_query.exec())
//          {
//            qDebug() << sql_query.lastError();
//          }
//          else
//          {
//            qDebug() << "inserted score!";
//          }
  ////      QSqlQuery sql_query;


  //  //          QString insert_sql = "insert into game values (?, ?, ?, ?)";
//              sql_query.prepare(insert_sql);
//              sql_query.addBindValue("wang");
//              sql_query.addBindValue("123");
//              sql_query.addBindValue(40000);
//              sql_query.addBindValue(1);
//              if(!sql_query.exec())
//              {
//                qDebug() << sql_query.lastError();
//              }
//              else
//              {
//                qDebug() << "inserted Wang!";
//              }
  //    QString insert_sql = "insert into game values (?, ?, ?, ?)";
  //    sql_query.prepare(insert_sql);
  //    sql_query.addBindValue("liu");
  //    sql_query.addBindValue("456");
  //    sql_query.addBindValue(30000);
  //    sql_query.addBindValue(2);
  //    if(!sql_query.exec())
  //    {
  //      qDebug() << sql_query.lastError();
  //    }
  //    else
  //    {
  //      qDebug() << "inserted Wang!";
  //    }

  this->inquire();

}

int dataBase::readFromUsers(QString tempId, QString tempPwd) {
    bool userFlag = false;
    bool pwdFlag = false;

    QSqlQuery sql_query;
    QString select_all_sql = "select * from users";

    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
      qDebug()<<sql_query.lastError();
    }
    else
    {
      while(sql_query.next())
      {
        QString id = sql_query.value(0).toString();
        QString password = sql_query.value(1).toString();

        if(strcmp(tempId.toStdString().c_str(),id.toStdString().c_str()) == 0) {
          //          cout << "zhaodaoyoinghu" << endl;
          userFlag = true;
          if(strcmp(tempPwd.toStdString().c_str(),password.toStdString().c_str()) == 0) {
            pwdFlag = true;

            user u;
            u.username = id;
            u.password = password;

            this->setUser(u);
            //          cout << "mimazhengque" << endl;

            break;

          }
          break;
        }


      }

      if (!userFlag) {
        return 0;
      }

      if (userFlag && !pwdFlag) {
        return 1;
      }

      return 2;
    }
}

int dataBase::readFromPlayers(QString tempId) {
  bool userFlag = false;
  QSqlQuery sql_query;
  QString select_all_sql = "select * from players";

  QString id;
  int score;
  int rank;

  sql_query.prepare(select_all_sql);
  if(!sql_query.exec())
  {
    qDebug()<<sql_query.lastError();
  }
  else
  {
    while(sql_query.next())
    {
      id = sql_query.value(0).toString();
      score = sql_query.value(1).toLongLong();
      rank = sql_query.value(2).toInt();
      //      int score = sql_query.value(2).toInt();
      //      int rank = sql_query.value(3).toInt();

      if(strcmp(tempId.toStdString().c_str(),id.toStdString().c_str()) == 0) {
        //          cout << "zhaodaoyoinghu" << endl;
        userFlag = true;
        break;
      }

    }


    if(userFlag) {
      return 0;
    } else {
      return 1;
    }
  }

}

int dataBase::loginFunc(QString tempId, QString tempPwd) {

  int flag = readFromUsers(tempId,tempPwd);
  if(flag == 2) {
    user a;
    a.username = tempId;
    a.password = tempPwd;
    setUser(a);

    player b;
    b.username = tempId;
    b.score = 0;
    b.rank = 0;
    setPlayer(b);
  }

  return flag;

}

int dataBase::registerFunc(QString tempId, QString tempPwd) {
  int flag = readFromPlayers(tempId);
  QSqlQuery sql_query;

  if (flag == 0) {
    return 0;
  }else {
      QString insert_sql = "insert into users values (?, ?)";
      sql_query.prepare(insert_sql);
      sql_query.addBindValue(tempId);
      sql_query.addBindValue(tempPwd);
      if(!sql_query.exec())
      {
        qDebug() << sql_query.lastError();
      }
      else
      {
        qDebug() << "inserted !";
      }

      return 1;
    }
}



void dataBase::inquire() {
  QSqlQuery sql_query;
  QString select_all_sql = "select * from users";
  sql_query.prepare(select_all_sql);
  if(!sql_query.exec())
  {
    qDebug()<<sql_query.lastError();
  }
  else
  {
    while(sql_query.next())
    {
      QString id = sql_query.value(0).toString();
      QString password = sql_query.value(1).toString();
      user u;
      u.username = id;
      u.password = password;
      this->users.push_back(u);
      qDebug()<<QString("id:%1    password:%2    ").arg(id).arg(password);
    }
  }

  QString select_all_sql1 = "select * from players";
  sql_query.prepare(select_all_sql1);
  if(!sql_query.exec())
  {
    qDebug()<<sql_query.lastError();
  }
  else
  {
    while(sql_query.next())
    {
      QString id = sql_query.value(0).toString();
      int score = sql_query.value(1).toInt();
      int rank = sql_query.value(2).toInt();
      player u;
      u.username = id;
      u.score = score;
      u.rank = rank;
      this->players.push_back(u);
      qDebug()<<QString("id:%1    score:%2   rank:%3 ").arg(id).arg(score).arg(rank);
    }
  }

}
bool compare(player a, player b)
{
  return a.score > b.score;
}

void dataBase::update(QString username,int score) {


  QSqlQuery sql_query;

    QString insert_sql = "insert into players values (?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(username);
    sql_query.addBindValue(score);
    sql_query.addBindValue(0);
    if(!sql_query.exec())
    {
      qDebug() << sql_query.lastError();
    }
    else
    {
      qDebug() << "inserted !";
    }

}
//void dataBase::updateDataBase() {
//  QSqlQuery query;
//  query.exec("DELETE FROM game");

//  for (auto iter = gamers.begin(); iter != gamers.end(); iter++) {
//    qDebug()<<QString("id:%1    password:%2    score:%3    rank:%4").arg((*iter).username).arg((*iter).password).arg((*iter).score).arg((*iter).rank);

//    QString insert_sql = "insert into game values (?, ?, ?, ?)";
//    query.prepare(insert_sql);
//    query.addBindValue((*iter).username);
//    query.addBindValue((*iter).password);
//    query.addBindValue((*iter).score);
//    query.addBindValue((*iter).rank);
//    query.exec();

//  }

//}

QString dataBase::showRankList(){
  users.clear();
  players.clear();
  this->inquire();
  sort(players.begin(),players.end(),compare);
  int i = 1;
  vector<player>::iterator iter;


  QString s = "ID\t\tSCORE\t\tRANK\n";

  for (iter = players.begin(); iter != players.end(); iter++) {
    (*iter).rank = i;
     s = s + (*iter).username + "\t\t" + QString::number((*iter).score) + "\t\t" + QString::number((*iter).rank)  + "\n";
    i++;
    //      qDebug()<<QString("id:%1    password:%2    score:%3    rank:%4").arg((*iter).username).arg((*iter).password).arg((*iter).score).arg((*iter).rank);
  }
  return s;
}

QString dataBase::showUserRankList(){

  users.clear();
  players.clear();
  this->inquire();

  QString s = "";
  QString name = usr.username;

  vector<player> tempPlayer;

  vector<player>::iterator iter;
  for (iter = players.begin(); iter != players.end(); iter++) {
    if(strcmp(name.toStdString().c_str(),(*iter).username.toStdString().c_str()) == 0) {
      tempPlayer.push_back((*iter));
    }
    //      qDebug()<<QString("id:%1    password:%2    score:%3    rank:%4").arg((*iter).username).arg((*iter).password).arg((*iter).score).arg((*iter).rank);
  }

  s = "id\t\tscore\n";
  sort(tempPlayer.begin(),tempPlayer.end(),compare);
  for (iter = tempPlayer.begin(); iter != tempPlayer.end(); iter++) {
    s = s + (*iter).username + "\t\t" + QString::number((*iter).score) + "\n";
    //      qDebug()<<QString("id:%1    password:%2    score:%3    rank:%4").arg((*iter).username).arg((*iter).password).arg((*iter).score).arg((*iter).rank);
  }

  if (strcmp(s.toStdString().c_str(),"") == 0) {
    s = "No data";
  }

  return s;
}

vector<player> dataBase::getPlayers() {
  return players;
}

player dataBase::getPlayer() {
  return gamer;
}

void dataBase::setPlayer(player a) {
  gamer = a;
}

void dataBase::setUser(user a) {
  usr = a;
}

