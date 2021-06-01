#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    //禁用最大化按钮、设置窗口大小固定
    this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    //全屏
    QWidget::showFullScreen();



    //设置窗口背景黑色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    //背景图片 棋盘框 分数框
    setAdaptedImg(":/picture/backdrop00.jpg",ui->oriBkLbl);
    setAdaptedImg(":/picture/frame.png",ui->borderLbl);
    setAdaptedImg(":/picture/scorepod.png",ui->scoreLbl);

    //设置鼠标-普通
    setCursor(QCursor(QPixmap("://picture/mouse1.png")));


    //动画
    QPropertyAnimation* anim1 = new QPropertyAnimation(ui->borderLbl, "geometry");
    anim1->setDuration(500);
    anim1->setStartValue(QRect(610+1055, 2, 1055, 1073));
    anim1->setEndValue(QRect(610, 2, 1055, 1073));
    anim1->setEasingCurve(QEasingCurve::OutQuad);
    //anim1->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* anim2 = new QPropertyAnimation(ui->scoreLbl, "geometry");
    anim2->setDuration(500);
    anim2->setStartValue(QRect(270, 0, 327, 178));
    anim2->setEndValue(QRect(270, 50, 327, 178));
    anim2->setEasingCurve(QEasingCurve::Custom);
    //anim2->start(QAbstractAnimation::DeleteWhenStopped);

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(anim1);
    group->addAnimation(anim2);

    group->start();
}

//将path的图片放置到label上，自适应label大小
void GameWidget::setAdaptedImg(QString path,QLabel *label)
{
    QImage image(path);
    QSize size=label->size();
    QImage image2=image.scaled(size,Qt::IgnoreAspectRatio);//重新调整图像大小以适应label
    label->setPixmap(QPixmap::fromImage(image2));//显示
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::keyPressEvent(QKeyEvent *ev)
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

