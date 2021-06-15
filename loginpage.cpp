#include "loginpage.h"
#include "ui_loginpage.h"
#include "qmessagebox.h"
//#include "startpage.h"
//#include "ui_startpage.h"


class StartPage;

loginPage::loginPage(QWidget *parent) :
                                        QWidget(parent),
                                        ui(new Ui::loginPage)
{
  ui->setupUi(this);
  returnButton = new HoverButton();
  confirmButton = new HoverButton();

  returnButton->setSound(":/music/button/button_mouseover.wav", ":/music/button/button_mouseleave.wav", ":/music/button/button_press.wav", ":/music/button/button_release.wav"); //默认音效
  confirmButton->setSound(":/music/button/button_mouseover.wav", ":/music/button/button_mouseleave.wav", ":/music/button/button_press.wav", ":/music/button/button_release.wav");
  //禁用最大化按钮、设置窗口大小固定
  this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
  this->setFixedSize(this->width(),this->height());

  id = new QLabel(this);
  pwd = new QLabel(this);
  id->setText("id");
  pwd->setText("password");

  idText = new QTextEdit(this);
  pwdText = new QLineEdit(this);

  pwdText->setEchoMode(QLineEdit::Password);

  QFont ft;
  ft.setPointSize(25);
  id->setFont(ft);
  pwd->setFont(ft);
  idText->setFont(ft);
  pwdText->setFont(ft);


  QPalette pl = idText->palette();
  pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
  idText->setPalette(pl);

  QPalette pl1 = pwdText->palette();
  pl1.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
  pwdText->setPalette(pl1);


  id->setGeometry(this->width()/2+400,this->height()/2+250,250,100);
  pwd->setGeometry(this->width()/2+400,this->height()/2+400,250,100);
  idText->setGeometry(this->width()/2+800,this->height()/2+265,400,75);
  pwdText->setGeometry(this->width()/2+800,this->height()/2+415,400,75);

  //  ranklist = new QTextBrowser(this);
  //  ranklist->setText("");
  //  //  ranklist->setText("ID\t\t\t\tSCORE\t\t\t\tRANK\n");
  //  QFont ft;
  //  ft.setPointSize(30);
  //  ranklist->setFont(ft);
  //  ranklist->setGeometry(this->width()/2+350,this->height()/2+190,1000,450);
  //  QPalette pl = ranklist->palette();
  //  pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
  //  ranklist->setPalette(pl);
  //  ranklist->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");



  //全屏
  QWidget::showFullScreen();
  //设置窗口背景黑色
  QPalette palette(this->palette());
  palette.setColor(QPalette::Background, Qt::black);
  this->setPalette(palette);
  //设置鼠标-普通
  setCursor(QCursor(QPixmap("://picture/mouse1.png")));
  //    QTimer::singleShot(1500, this, [=](){
  QParallelAnimationGroup *group = new QParallelAnimationGroup;
  group->addAnimation(ShowBackground());
  SetButton();
  returnButton->showContent("Return",30);
  confirmButton->showContent("Login",30);

  group->addAnimation(returnButton->textAnim);
  group->addAnimation(confirmButton->textAnim);

  group->addAnimation(ShowTitle());
  Sleep(200);
  group->start(QAbstractAnimation::DeleteWhenStopped);
  //    });

  id->raise();
  pwd->raise();
  idText->raise();
  pwdText->raise();

  this->hide();
}

loginPage::~loginPage()
{
  delete ui;
}


QPropertyAnimation * loginPage::ShowTitle(){
  QPixmap pix;
  QLabel *title = new QLabel(this);
  title->setGeometry(this->width()/2-903/2,-title->height(),903,200);
  setAdaptedImg(":/picture/StartPage/title.png",title);
  title->show();
  QPropertyAnimation *animation = new QPropertyAnimation(title, "geometry",this);
  animation->setDuration(2000);
  animation->setStartValue(QRect(title->x(), title->y(), title->width(), title->height()));
  animation->setEndValue(QRect(title->x(), 100, title->width(), title->height()));
  animation->setEasingCurve(QEasingCurve::OutExpo);
  return animation;

}
QPropertyAnimation *  loginPage::ShowBackground(){
  QPixmap pix;
  QLabel *background = new QLabel(this);
  bkAnim = new QPropertyAnimation(background, "geometry",this);
  setBkImg("://picture/StartPage/background.png",background);
  background->show();
  bkAnim->setDuration(2000);
  bkAnim->setStartValue(QRect(background->x(), background->y(), background->width(), background->height()));
  bkAnim->setEndValue(QRect(background->x(), this->height() - background->height(), background->width(), background->height()));
  bkAnim->setEasingCurve(QEasingCurve::InOutCubic);
  return bkAnim;
}

void loginPage::SetButton(){
  returnButton->setCircle(this->width()/10, this->width()/2+300, this->height()/2+400, this->width(), this->height(),\
                           ":/picture/button/ball.png", "", this);
  confirmButton->setCircle(this->width()/10, this->width()/2-300, this->height()/2+400, this->width(), this->height(),\
                           ":/picture/button/ball.png", "", this);
  connect(returnButton, &HoverButton::clicked, [=](){
    this->hide();
    showStartPage();
    //    vector<user> tempGamers =database->showRankList();
    //    QString s = "ID\t\t\t\tSCORE\t\t\t\tRANK\n";

    //    for (auto iter = tempGamers.begin(); iter != tempGamers.end(); iter++) {
    //      //      qDebug()<<QString("id:%1    password:%2    score:%3    rank:%4").arg((*iter).username).arg((*iter).password).arg((*iter).score).arg((*iter).rank);
    //      s = s + (*iter).username + "\t\t\t\t" + QString::number((*iter).score) + "\t\t\t" + QString::number((*iter).rank)  + "\n";
    //      cout << s.toStdString() << endl;
    //    }

    //    ranklist->setText(s);
    //    this->hide();
    //    gameWidget->setupScene();
    //    gameWidget->show();
  }) ;

  //  connect(gameWidget, &GameWidget::showStartPage, [=](){
  //    this->show();
  //  }) ;

  connect(confirmButton,&HoverButton::clicked, [=]() {
    QString tempId = idText->toPlainText();
    QString tempPwd = pwdText->text();
    if(client->logined == true){
      QMessageBox msgBox;
      msgBox.setText("Already logged in user");
      msgBox.exec();
    }
    else {
      client->verifyUser(tempId, tempPwd);
      int flag = client->verifyFlag;
      if(flag == 2) {
        client->logined = true;
      }
      //    int flag = database->loginFunc(tempId,tempPwd);
      //    vector<user> tempGamers =database->showRankList();
      //    bool userFlag = false;
      //    bool pwdFlag = false;

      //    for (auto iter = tempGamers.begin(); iter != tempGamers.end(); iter++) {
      //      if(strcmp(tempId.toStdString().c_str(),(*iter).username.toStdString().c_str()) == 0) {
      //        //          cout << "zhaodaoyoinghu" << endl;
      //        userFlag = true;
      //        if(strcmp(tempPwd.toStdString().c_str(),(*iter).password.toStdString().c_str()) == 0) {
      //          pwdFlag = true;
      //          user a = *iter;
      //          database->setGamer(a);
      //          cout << "mimazhengque" << endl;
      //        }
      //      }
      //    }



      QMessageBox msgBox;   // 生成对象
      if(flag == 0) {
        msgBox.setText("The user hasn't been register");    // 设置文本
      }

      if(flag == 1) {
        msgBox.setText("The user password is wrong");    // 设置文本
      }

      if (flag == 2) {
        msgBox.setText("User successfully logged in");    // 设置文
      }

      msgBox.exec();  // 执行

      idText->setText((""));
      pwdText->setText((""));
    }


  });
}


//将path的图片放置到label上，自适应label大小
void loginPage::setAdaptedImg(QString path,QLabel *label)
{
  QImage image(path);
  QSize size=label->size();
  QImage image2=image.scaled(size,Qt::IgnoreAspectRatio);//重新调整图像大小以适应label
  label->setPixmap(QPixmap::fromImage(image2));//显示
}
//将path的图片放置到label上，自适应label大小
void loginPage::setBkImg(QString path,QLabel *label)
{
  QImage image = QImage(path);
  if(image.isNull()){
    qDebug()<<"background:empty";
  }
  double ratio=(double)image.height()/(double)image.width();
  QImage image2=image.scaled(this->width(),ratio*this->width(),Qt::IgnoreAspectRatio);//重新调整图像大小以适应label
  label->setPixmap(QPixmap::fromImage(image2));//显示
  label->setGeometry(0,0,this->width(),ratio*this->width());
}

void loginPage::keyPressEvent(QKeyEvent *ev)
{
  //Esc退出全屏
  if(ev->key() == Qt::Key_Escape)
  {
    QWidget::showNormal();
    return;
  }
  //F11全屏
  if(ev->key() == Qt::Key_F11)
  {
    QWidget::showFullScreen();
    return;
  }
  QWidget::keyPressEvent(ev);
}
void loginPage::Sleep(int msec)
{
  QTime dieTime = QTime::currentTime().addMSecs(msec);
  while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
