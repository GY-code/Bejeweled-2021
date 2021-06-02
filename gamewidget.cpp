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


    //窗口基本设置
    setWindowFlag(Qt::Window);  //设置为独立窗口
    setWindowTitle("Bejeweled");
    setWindowIcon(QIcon("://picture/app_icon.ico"));

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

    ui->progressBar->setGeometry(660,1010,960,45);
    ui->progressBar->setRange(0,4000);
    ui->progressBar->setValue(4000);
    ui->progressBar->setTextVisible(false);
    ui->progressBar->setAlignment(Qt::AlignCenter);
    ui->progressBar->setStyleSheet("QProgressBar::chunk{background-color:rgb(74, 149, 223)}");

    QTimer *progressTimer = new QTimer(this);
    progressTimer->setInterval(10);
    progressTimer->start();
    connect(progressTimer, &QTimer::timeout, [=](){
        if(ui->progressBar->value() == 0){
        }
            //end();
        else
            ui->progressBar->setValue(ui->progressBar->value()-1);
    });

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
    test();
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

//关于宝石生成
//关于宝石的随机数生成
int GameWidget::randomGem(bool allowMagic){
    if(allowMagic && QRandomGenerator::global()->bounded(0, 85) == 1)        //Magic方块1/85生成概率
        return 0;
    return QRandomGenerator::global()->bounded(1, DIFFICULITY+1);
}
void GameWidget::test(){
    QPushButton *test=new QPushButton(this);
    this->setStyleSheet("QPushButton{background-color:rgb(200,101,102,100);}");
//        anim1->setEndValue(QRect(610, 2, 1055, 1073));
    test->setGeometry(665, 45, 952, 952);
    test->show();
}
void GameWidget::initScene(){
    boardWidget = new QWidget(this);
    boardWidget->show();
    boardWidget->setGeometry(1665, 2, 1055, 1073);
    QRandomGenerator::global()->fillRange(gemBoard[0], 64);
    for(int i = 0; i < 7; ++i)
        for(int j = 0; j <7 ; ++j){
            gemBoard[i][j] = gemBoard[i][j] % DIFFICULITY + 1;
            gems[i][j] = new Gem(gemBoard[i][j], 130, i, j, boardWidget);
            gems[i][j]->installEventFilter(this);
//            connect(gems[i][j], &Gem::mouseClicked, this, &GameWidget::act);
        }
    for(int i = 0; i < 7; ++i)
        for(int j = 7; j >= 0; --j){
                fallboard[i][j]=j;
        }
}
void GameWidget::initfall(){

    for(int i = 0; i < 7; ++i)
        for(int j = 7; j >= 0; --j){
                fallAnimation(gems[i][j], fallboard[i][j]);
        }
}


void GameWidget::fallAnimation(Gem *gem, int h){
    QPropertyAnimation* animation = new QPropertyAnimation(gem, "geometry", this);
    animation->setDuration(500);
    animation->setStartValue(gem->geometry());
    animation->setEndValue(QRect(gem->geometry().x(), gem->geometry().y() + 130*h+2, gem->width(), gem->height()));
    animation->setEasingCurve(QEasingCurve::InQuad);
    animation->start();
    QTimer::singleShot(1000, this, [=](){
        delete animation;
    });
}

bool GameWidget::eventFilter(QObject *watched, QEvent *event){              //动画进行中禁用点击事件
    if(watched->metaObject()->className() == QStringLiteral("Gem"))
        if((event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick))
            return true;
    return QWidget::eventFilter(watched, event);
}

