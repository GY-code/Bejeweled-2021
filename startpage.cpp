#include<windows.h>
#include<stdio.h>
#include <QDesktopServices>
#include "startpage.h"
#include "ui_startpage.h"
#include "CGammaRamp.h"
#include "qmessagebox.h"

StartPage::StartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartPage)
{
    ui->setupUi(this);
//select=new selectlevel();
    //循环播放背景音乐
    qDebug()<<QCoreApplication::applicationDirPath();
    sound=new QSoundEffect(this);
    sound->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath()+"/music/background/music-1.wav"));
    sound->setLoopCount(QSoundEffect::Infinite);
    sound->play();


    startButton=new HoverButton();
    recordButton=new HoverButton();
    settingButton=new HoverButton();
    loginButton = new HoverButton();
    registerButton = new HoverButton();
    logoutButton = new HoverButton();

    
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
    loginButton->showContent("login",10);
    registerButton->showContent("register",10);
    logoutButton->showContent("logout",10);

    group->addAnimation(startButton->textAnim);
    group->addAnimation(recordButton->textAnim);
    group->addAnimation(settingButton->textAnim);
    group->addAnimation(loginButton->textAnim);
    group->addAnimation(registerButton->textAnim);
    group->addAnimation(logoutButton->textAnim);

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
    loginButton->setCircle(this->width()/50, this->width()/10, this->height()/2+500, this->width(), this->height(),\
                      ":/picture/button/ball.png", "", this);
    registerButton->setCircle(this->width()/50, this->width()/30, this->height()/2+500, this->width(), this->height(),\
                      ":/picture/button/ball.png", "", this);
    logoutButton->setCircle(this->width()/50, this->width()/10, this->height()/2+400, this->width(), this->height(),\
                      ":/picture/button/ball.png", "", this);

    //语言切换
    connect(&settingP,&settingpage::selectLan,[=](int index){
        this->ForGameL=index;
    });
     connect(select,&selectlevel::selectDone,[=](int difficulty){
        this->hide();
        sound->stop();
        gameWidget->DIFFICULITY=difficulty;
        gameWidget->setupScene(this->ForGameL);
        gameWidget->show();
    });

    //语言切换
    connect(&settingP,&settingpage::selectLan,[=](int index){

        if(index==0){
            select->level1L->setText("简单");
            select->level2L->setText("普通");
            select->level2L->setGeometry(260,130,81,21);
            select->level3L->setText("困难");
            select->levelL->setText("设置");
            select->DoneL->setText("开始");
        }else{
            select->level1L->setText("Easy");
            select->level2L->setText("Medium");
            select->level3L->setText("Hard");
            select->levelL->setText("Settings");
            select->DoneL->setText("Done");
        }
    });

    connect(startButton, &HoverButton::clicked, [=](){
        select->setParent(this);
        select->setGeometry(700,400,800,555);
        select->setVisible(true);
    });

    connect(gameWidget, &GameWidget::showStartPage, [=](){
        this->show();
        sound->setLoopCount(QSoundEffect::Infinite);
        sound->play();
    }) ;


    //打开设置界面
    connect(settingButton, &HoverButton::clicked, [=](){
        settingP.setParent(this);
        settingP.setGeometry(560,262,800,555);
        settingP.show();
    }) ;

    //语言切换
    connect(&settingP,&settingpage::selectLan,[=](int index){

        if(index==0){
            startButton->showContent("开始",40);
            recordButton->showContent("记录",20);
            settingButton->showContent("设置",20);
            loginButton->showContent("登录",10);
            registerButton->showContent("注册",10);
            logoutButton->showContent("登出",10);
        }

        if(index==1){
            startButton->showContent("Start",40);
            recordButton->showContent("Record",20);
            settingButton->showContent("Settings",20);
            loginButton->showContent("login",10);
            registerButton->showContent("register",10);
            logoutButton->showContent("logout",10);
        }
    });

    connect(recordButton, &HoverButton::clicked, [=](){
      this->hide();
      sound->stop();
      client->getProfile();
      client->getRankList();
      QString s = client->ranklist;
      QString s1 = client->userlist;
      ranklist->setRankList(s);
      ranklist->setUserRankList(s1);
      ranklist->show();

    }) ;

    connect(loginButton, &HoverButton::clicked, [=](){
      this->hide();
      sound->stop();
      login->show();

    }) ;

    connect(registerButton, &HoverButton::clicked, [=](){
      this->hide();
      sound->stop();
      regist->show();

    }) ;

    connect(logoutButton, &HoverButton::clicked, [=](){
      QMessageBox msgBox;   // 生成对象
      if(client->logined == true) {
        client->logined = false;
        msgBox.setText("The user log out");    // 设置文本
      } else {
        msgBox.setText("No user log in");
      }

      msgBox.exec();
    }) ;

    connect(ranklist, &rankListPage::showStartPage, [=](){
      this->show();
      sound->setLoopCount(QSoundEffect::Infinite);
      sound->play();
    }) ;

    connect(login, &loginPage::showStartPage, [=](){
      this->show();
      sound->setLoopCount(QSoundEffect::Infinite);
      sound->play();
    }) ;

    connect(regist, &registerPage::showStartPage, [=](){
      this->show();
      sound->setLoopCount(QSoundEffect::Infinite);
      sound->play();
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

//主窗口关闭则选择界面关闭
void StartPage::closeEvent(QCloseEvent *event)
{
    select->close();
}

