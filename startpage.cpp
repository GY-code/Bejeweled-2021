#include<windows.h>
#include<stdio.h>
#include <QDesktopServices>
#include "startpage.h"
#include "ui_startpage.h"
#include "CGammaRamp.h"

StartPage::StartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPage)
{
    ui->setupUi(this);
    //循环播放背景音乐
    qDebug()<<QCoreApplication::applicationDirPath();
    sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/music/background/music-1.wav"));
    sound->setLoopCount(QSoundEffect::Infinite);
    sound->play();


    startButton=new HoverButton();
    recordButton=new HoverButton();
    settingButton=new HoverButton();

    gitButton=new HoverButton();
    documentButton=new HoverButton();
    bright=new HoverButton();
    volume=new HoverButton();

    
    startButton->setSound(":/music/button/button_mouseover.wav", ":/music/button/button_mouseleave.wav", ":/music/button/button_press.wav", ":/music/button/button_release.wav"); //默认音效
    recordButton->setSound(":/music/button/button_mouseover.wav", ":/music/button/button_mouseleave.wav", ":/music/button/button_press.wav", ":/music/button/button_release.wav"); //默认音效
    settingButton->setSound(":/music/button/button_mouseover.wav", ":/music/button/button_mouseleave.wav", ":/music/button/button_press.wav", ":/music/button/button_release.wav"); //默认音效

    //禁用最大化按钮、设置窗口大小固定
    this->setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    //全屏
    QWidget::showFullScreen();
    //设置窗口背景黑色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);
    //设置鼠标-普通
    setCursor(QCursor(QPixmap("://picture/mouse1.png")));
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(ShowBackground());
    SetButton();
    startButton->showContent("Start",40);
    recordButton->showContent("Record",20);
    settingButton->showContent("Setting",20);
    gitButton->showContent("Git",10);
    documentButton->showContent("Document",10);
    volume->showContent("volueme",10);
    bright->showContent("brightness",10);
    group->addAnimation(startButton->textAnim);
    group->addAnimation(recordButton->textAnim);
    group->addAnimation(settingButton->textAnim);
    group->addAnimation(documentButton->textAnim);
    group->addAnimation(gitButton->textAnim);

    group->addAnimation(bright->textAnim);
    group->addAnimation(volume->textAnim);
    group->addAnimation(ShowTitle());
    Sleep(200);
    group->start(QAbstractAnimation::DeleteWhenStopped);

}

StartPage::~StartPage()
{
    delete ui;
}
QPropertyAnimation * StartPage::ShowTitle(){
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
QPropertyAnimation *  StartPage::ShowBackground(){
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

void StartPage::SetButton(){
    startButton->setCircle(this->width()/10, this->width()/2, this->height()/2+100, this->width(), this->height(),\
                           ":/picture/button/ball.png", "", this);

    recordButton->setCircle(this->width()/100*5, this->width()/6, this->height()/2+100, this->width(), this->height(),\
                            ":/picture/button/ball.png", "", this);
    settingButton->setCircle(this->width()/100*5, this->width()/6*5, this->height()/2+100, this->width(), this->height(),\
                             ":/picture/button/ball.png", "", this);
    documentButton->setCircle(this->width()/50, this->width()/30, this->height()/2+400, this->width(), this->height(),\
                              ":/picture/button/ball.png", "", this);
    gitButton->setCircle(this->width()/50, this->width()/30, this->height()/2+500, this->width(), this->height(),\
                         ":/picture/button/ball.png", "", this);
    bright->setCircle(this->width()/50, this->width()/10, this->height()/2+500, this->width(), this->height(),\
                      ":/picture/button/ball.png", "", this);

    volume->setCircle(this->width()/50, this->width()/10, this->height()/2+400, this->width(), this->height(),\
                      ":/picture/button/ball.png", "", this);
    connect(startButton, &HoverButton::clicked, [=](){
        this->hide();
        sound->stop();
        gameWidget->setupScene();
        gameWidget->show();
    });

    connect(gameWidget, &GameWidget::showStartPage, [=](){
        this->show();
        sound->setLoopCount(QSoundEffect::Infinite);
        sound->play();
    }) ;
    //打开文档
    connect(documentButton, &HoverButton::clicked, [=](){
        QFile file(":/doc/Exp.doc");
        QTemporaryDir tempDir;
        tempDir.setAutoRemove(false);
        if (tempDir.isValid()) {
            QString tempFile = tempDir.path() + "/Exp.doc";
            if (QFile::copy(":/doc/Exp.doc", tempFile)) {
                //now extracted to the filesystem
                QDesktopServices::openUrl(QUrl::fromLocalFile(tempDir.path() + "/Exp.doc"));
            }
        }

    }) ;


    //访问网页
    connect(gitButton, &HoverButton::clicked, [=](){
        QDesktopServices::openUrl(QUrl(QLatin1String("https://gitee.com/guyi2020/bejeweled-2021")));
    }) ;
    //亮度调节
    connect(bright, &HoverButton::clicked, [=](){
        brightW.show();
    }) ;

    //声音调节
    connect(volume, &HoverButton::clicked, [=](){
        volumeW.show();
    }) ;

}
//将path的图片放置到label上，自适应label大小
void StartPage::setAdaptedImg(QString path,QLabel *label)
{
    QImage image(path);
    QSize size=label->size();
    QImage image2=image.scaled(size,Qt::IgnoreAspectRatio);//重新调整图像大小以适应label
    label->setPixmap(QPixmap::fromImage(image2));//显示
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

void StartPage::keyPressEvent(QKeyEvent *ev)
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
void StartPage::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
