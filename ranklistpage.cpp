#include "ranklistpage.h"
#include "ui_ranklistpage.h"
//#include "startpage.h"
//#include "ui_startpage.h"
#include<windows.h>
#include<stdio.h>
#include <QDesktopServices>
#include "CGammaRamp.h"
#include "iostream"


//class StartPage;

rankListPage::rankListPage(QWidget *parent) :
                                              QWidget(parent),
                                              ui(new Ui::rankListPage)
{
  ui->setupUi(this);
  returnButton = new HoverButton();

  returnButton->setSound(":/music/button/button_mouseover.wav", ":/music/button/button_mouseleave.wav", ":/music/button/button_press.wav", ":/music/button/button_release.wav"); //默认音效
  //禁用最大化按钮、设置窗口大小固定
  this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
  this->setFixedSize(this->width(),this->height());

  labelRanklist = new QLabel(this);
  labelUserRanklist = new QLabel(this);

  labelRanklist->setText("Total Rank List");
  labelUserRanklist->setText("User Rank List");

  QFont ftr;
  ftr.setPointSize(30);
  labelRanklist->setFont(ftr);
  labelUserRanklist->setFont(ftr);

  labelRanklist->setGeometry(this->width()/2+100,this->height()/2-30,1000,450);
  labelUserRanklist->setGeometry(this->width()/2+1000,this->height()/2-30,1000,450);


  ranklist = new QTextBrowser(this);
  //  ranklist->setText("");
  ranklist->setText("ID\t\t\t\tSCORE\t\t\t\tRANK\n");
  QFont ft;
  ft.setPointSize(20);
  ranklist->setFont(ft);
  ranklist->setGeometry(this->width()/2+100,this->height()/2+250,1000,450);
  QPalette pl = ranklist->palette();
  pl.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
  ranklist->setPalette(pl);
  ranklist->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");

  userRanklist = new QTextBrowser(this);
  //  ranklist->setText("");
  userRanklist->setText("ID\t\tSCORE\t\t\n");
  QFont ft1;
  ft1.setPointSize(20);
  userRanklist->setFont(ft1);
  userRanklist->setGeometry(this->width()/2+1000,this->height()/2+250,1000,450);
  QPalette pl1 = ranklist->palette();
  pl1.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
  userRanklist->setPalette(pl);
  userRanklist->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");


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

  group->addAnimation(returnButton->textAnim);

  group->addAnimation(ShowTitle());
  Sleep(200);
  group->start(QAbstractAnimation::DeleteWhenStopped);
  //    });

  //  vector<player> tempGamers =database->showRankList();
  client->getProfile();
  client->getRankList();
  QString s = client->ranklist;
  QString s1 = client->userlist;
  //  for (auto iter = tempGamers.begin(); iter != tempGamers.end(); iter++) {
  //    //      qDebug()<<QString("id:%1    password:%2    score:%3    rank:%4").arg((*iter).username).arg((*iter).password).arg((*iter).score).arg((*iter).rank);
  //    s = s + (*iter).username + "\t\t\t\t" + QString::number((*iter).score) + "\t\t\t\t" + QString::number((*iter).rank)  + "\n";
  //    cout << s.toStdString() << endl;
  //  }

  labelRanklist->raise();
  labelUserRanklist->raise();

  ranklist->setText(s);
  ranklist->raise();

  userRanklist->setText(s1);
  userRanklist->raise();

  this->hide();
}

rankListPage::~rankListPage()
{
  delete ui;
}

void rankListPage::setUserRankList(QString s) {
  userRanklist->setText(s);
}

void rankListPage::setRankList(QString s) {
  ranklist->setText(s);
}

QPropertyAnimation * rankListPage::ShowTitle(){
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
QPropertyAnimation *  rankListPage::ShowBackground(){
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

void rankListPage::SetButton(){
  returnButton->setCircle(this->width()/10, this->width()/2, this->height()/2+400, this->width(), this->height(),\
                           ":/picture/button/ball.png", "", this);

  connect(returnButton, &HoverButton::clicked, [=](){
    this->hide();

    showStartPage();
    //    vector<user> tempGamers =database->showRankList();
    //    QString s = "ID\t\t\t\tSCORE\t\t\t\tRANK\n";

    //    for (auto iter = tempGamers.begin(); iter != tempGamers.end(); iter++) {
    //      //      qDebug()<<QString("id:%1    password:%2    score:%3    rank:%4").arg((*iter).username).arg((*iter).password).arg((*iter).score).arg((*iter).rank);
    //      s = s + (*iter).username + "\t\t\t\t" + QString::number((*iter).score) + "\t\t\t\t" + QString::number((*iter).rank)  + "\n";
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


}


//将path的图片放置到label上，自适应label大小
void rankListPage::setAdaptedImg(QString path,QLabel *label)
{
  QImage image(path);
  QSize size=label->size();
  QImage image2=image.scaled(size,Qt::IgnoreAspectRatio);//重新调整图像大小以适应label
  label->setPixmap(QPixmap::fromImage(image2));//显示
}
//将path的图片放置到label上，自适应label大小
void rankListPage::setBkImg(QString path,QLabel *label)
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

void rankListPage::keyPressEvent(QKeyEvent *ev)
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
void rankListPage::Sleep(int msec)
{
  QTime dieTime = QTime::currentTime().addMSecs(msec);
  while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
