#include "startpage.h"
#include "ui_startpage.h"

StartPage::StartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPage)
{
    ui->setupUi(this);
    ShowBackground();
    SetButton();
    QTimer::singleShot(1000, this, [=](){
        startButton->showContent("Start",40);
    });

}

StartPage::~StartPage()
{
    delete ui;
}

void StartPage::ShowBackground(){
    QPixmap pix;
    QLabel *background = new QLabel(this);
    QPropertyAnimation *animation = new QPropertyAnimation(background, "geometry",this);
    setBkImg(":/picture/StartPage/BackgroundHQ.png",background);
    background->show();
    animation->setDuration(3000);
    animation->setStartValue(QRect(background->x(), background->y(), background->width(), background->height()));
    animation->setEndValue(QRect(background->x(), this->height() - background->height(), background->width(), background->height()));
    animation->setEasingCurve(QEasingCurve::InOutCubic);
    animation->start();

}

void StartPage::SetButton(){
      startButton=new HoverButton(this);
      startButton->setCircle(this->width()/10, this->width()/2, this->height()/2, this->width(), this->height(),\
                              ":/picture/button/ball.png", "", this);


//    recordButton = new MenuButton(this->width()/100*7, this->width()/6, this->height()/2, this->width(), this->height(),\
//                                  ":/pic/Menu/record.png", ":/pic/Menu/record_hover.png", this);
//    settingButton = new MenuButton(this->width()/100*7, this->width()/6*5, this->height()/2, this->width(), this->height(),\
//                                   ":/pic/Menu/settings.png", ":/pic/Menu/setting_hover.png", this);


//    exitButton = new HoverButton(this);
//    exitButton->setGeometry(this->width()-70, this->height()-35, 60, 30);
//    exitButton->setFlat(true);
//    exitButton->setImage(":/pic/Menu/exit.png", ":/pic/Menu/exit_hover.png", 60, 30);
//    exitButton->setSound(":/sound/button_mouseover.wav", ":/sound/button_mouseleave.wav", ":/sound/button_press.wav", ":/sound/button_release.wav");


//    //显示按钮

//    recordButton->show();
//    settingButton->show();
//    QTimer::singleShot(2000, this, [=](){
//        exitButton->setVisible(true);
//    });
//    //链接按钮功能
}

//将path的图片放置到label上，自适应label大小
void StartPage::setBkImg(QString path,QLabel *label)
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