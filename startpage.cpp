#include "startpage.h"
#include "ui_startpage.h"

StartPage::StartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPage)
{
    ui->setupUi(this);
    ShowBackground();
}

StartPage::~StartPage()
{
    delete ui;
}

void StartPage::ShowBackground(){
    QPixmap pix;
    QLabel *background = new QLabel(this);
//    QPropertyAnimation *animation = new QPropertyAnimation(background, "geometry",this);
    background->setText("aaaaaaaaa");
    setBkImg("://picture/StartPage/Background_HQ.jpg",background);
    background->show();


//    animation->setDuration(3000);
//    animation->setStartValue(QRect(background->x(), background->y(), background->width(), background->height()));
//    animation->setEndValue(QRect(background->x(), this->height() - background->height(), background->width(), background->height()));
//    animation->setEasingCurve(QEasingCurve::InOutCubic);
//    animation->start();

}

//将path的图片放置到label上，自适应label大小
void StartPage::setBkImg(QString path,QLabel *label)
{
    QImage image(path);
    if(image.isNull()){
        qDebug()<<"empty";
    }
    double ratio=(double)image.height()/(double)image.width();
    QImage image2=image.scaled(this->width(),ratio*this->width(),Qt::IgnoreAspectRatio);//重新调整图像大小以适应label
    label->setPixmap(QPixmap::fromImage(image2));//显示
    label->setGeometry(0,0,this->width(),ratio*this->width());
}
