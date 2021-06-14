#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
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
#include "string.h"
#include <QtCore/QCoreApplication>
#include <cstring>

using namespace std;


extern Client *client;

namespace Ui {
class loginPage;
//class StartPage;
}

class loginPage : public QWidget
{
  Q_OBJECT

public:
  explicit loginPage(QWidget *parent = nullptr);
  QPropertyAnimation *bkAnim;
  ~loginPage();
protected:
  virtual void keyPressEvent(QKeyEvent *ev);
private:
  Ui::loginPage *ui;
  HoverButton *returnButton;
  HoverButton *confirmButton;
  QLabel *background;
  QLabel *id,*pwd;
  QTextEdit *idText;
  QLineEdit *pwdText;


  QPropertyAnimation *  ShowBackground();
  QPropertyAnimation * ShowTitle();
  void SetButton();
  void setBkImg(QString path,QLabel *label);
  void setAdaptedImg(QString path,QLabel *label);
  void Sleep(int msec);
signals:
  void showStartPage();
};

#endif // LOGINPAGE_H
