#ifndef RANKLISTPAGE_H
#define RANKLISTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QtGui/QTextLine>
#include <QPropertyAnimation>
#include <QDebug>
#include <QImage>
#include <QFile>
#include "hoverbutton.h"
#include "gamewidget.h"
#include <QTime>
#include <QTemporaryDir>
#include <QTextBrowser>
#include "client.h"
//#include "startpage.h"
//#include "ui_startpage.h"
extern Client *client;

namespace Ui {
class rankListPage;
//class StartPage;
}

class rankListPage : public QWidget
{
  Q_OBJECT

public:
  explicit rankListPage(QWidget *parent = nullptr);
  QPropertyAnimation *bkAnim;
  void setUserRankList(QString s);
  void setRankList(QString s);
  ~rankListPage();
protected:
  virtual void keyPressEvent(QKeyEvent *ev);
private:
  Ui::rankListPage *ui;
  HoverButton *returnButton;
  QLabel *background;
  QTextBrowser *ranklist;
  QTextBrowser *userRanklist;
  QLabel *labelRanklist;
  QLabel *labelUserRanklist;

  QPropertyAnimation *  ShowBackground();
  QPropertyAnimation * ShowTitle();
  void SetButton();
  void setBkImg(QString path,QLabel *label);
  void setAdaptedImg(QString path,QLabel *label);
  void Sleep(int msec);
signals:
  void showStartPage();
};

#endif // RANKLISTPAGE_H
