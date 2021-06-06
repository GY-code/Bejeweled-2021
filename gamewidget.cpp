#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
}
void GameWidget::setupScene(){
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
    //辅助label，不用管
    ui->menuLbl->setVisible(false);
    ui->hintLbl->setVisible(false);
    ui->pauseLbl->setVisible(false);

    menuButton = new HoverButton(this);
    menuButton->setGeometry(ui->menuLbl->geometry());
    menuButton->setImage(":/picture/3balls/ball1.png",nullptr,ui->menuLbl->width(),ui->menuLbl->height(),ui->menuLbl);
    menuButton->showContent("MENU",20);
    menuButton->show();
    hintButton = new HoverButton(this);
    hintButton->setGeometry(ui->hintLbl->geometry());
    hintButton->setImage(":/picture/3balls/ball2.png",nullptr,ui->hintLbl->width(),ui->hintLbl->height(),ui->hintLbl);
    hintButton->showContent("HINT",30);
    hintButton->show();
    pauseButton = new HoverButton(this);
    pauseButton->setGeometry(ui->pauseLbl->geometry());
    pauseButton->setImage(":/picture/3balls/ball3.png",nullptr,ui->pauseLbl->width(),ui->pauseLbl->height(),ui->pauseLbl);
    pauseButton->showContent("PAUSE",20);
    pauseButton->show();

    //设置鼠标-普通
    setCursor(QCursor(QPixmap("://picture/mouse1.png")));

    //进度条
    progressBar = new MyProBar(this);
    progressBar->setRange(0,10000);
    progressBar->setValue(10000);
    progressBar->setTextVisible(false);
    progressBar->show();

    //动画

    //棋盘
    QPropertyAnimation* anim1 = new QPropertyAnimation(ui->borderLbl, "geometry");
    anim1->setDuration(500);
    anim1->setStartValue(QRect(610+1055, 2, 1055, 1073));
    anim1->setEndValue(QRect(610, 2, 1055, 1073));
    anim1->setEasingCurve(QEasingCurve::OutQuad);
    //分数版
    QPropertyAnimation* anim2 = new QPropertyAnimation(ui->scoreLbl, "geometry");
    anim2->setDuration(500);
    anim2->setStartValue(QRect(270, 0, 327, 178));
    anim2->setEndValue(QRect(270, 80, 327, 178));
    anim2->setEasingCurve(QEasingCurve::InQuad);
    //进度条
    QPropertyAnimation* anim3 = new QPropertyAnimation(progressBar,"geometry");
    anim3->setDuration(500);
    anim3->setStartValue(QRect(655+1055,1009,980,44));
    anim3->setEndValue(QRect(655,1009,980,44));
    anim3->setEasingCurve(QEasingCurve::OutQuad);
    //菜单栏
    QPropertyAnimation* anim4 = new QPropertyAnimation(menuButton,"geometry");
    anim4->setDuration(500);
    anim4->setStartValue(QRect(menuButton->x(),menuButton->y()+1000,menuButton->width(),menuButton->height()));
    anim4->setEndValue(QRect(menuButton->x(),menuButton->y(),menuButton->width(),menuButton->height()));
    anim4->setEasingCurve((QEasingCurve::OutQuad));
    QPropertyAnimation* anim5 = new QPropertyAnimation(hintButton,"geometry");
    anim5->setDuration(500);
    anim5->setStartValue(QRect(hintButton->x(),hintButton->y()+1000,hintButton->width(),hintButton->height()));
    anim5->setEndValue(QRect(hintButton->x(),hintButton->y(),hintButton->width(),hintButton->height()));
    anim5->setEasingCurve((QEasingCurve::OutQuad));
    QPropertyAnimation* anim6 = new QPropertyAnimation(pauseButton,"geometry");
    anim6->setDuration(500);
    anim6->setStartValue(QRect(pauseButton->x(),pauseButton->y()+1000,pauseButton->width(),pauseButton->height()));
    anim6->setEndValue(QRect(pauseButton->x(),pauseButton->y(),pauseButton->width(),pauseButton->height()));
    anim6->setEasingCurve((QEasingCurve::OutQuad));

    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(anim1);
    group->addAnimation(anim2);
    group->addAnimation(anim3);
    group->addAnimation(anim4);
    group->addAnimation(anim5);
    group->addAnimation(anim6);
    group->start(QAbstractAnimation::DeleteWhenStopped);

    Sleep(500);
    initScene();

    //开始记时
    progressTimer = new QTimer(this);
    progressTimer->setInterval(15);
    progressTimer->start();
    connect(progressTimer, &QTimer::timeout, [=](){
        if(progressBar->value() == 0){

            //计时结束
        }
        else
            progressBar->setValue(progressBar->value()-1);
    });
    connect(menuButton, &HoverButton::clicked, [=](){
        this->hide();
        showStartPage();
        if(menuButton)
            delete menuButton;
        if(hintButton)
            delete hintButton;
        if(pauseButton)
            delete pauseButton;
        if(progressTimer)
            delete progressTimer;
        if(progressBar)
            delete progressBar;
        if(selectedLbl)
            delete  selectedLbl;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                delete gems[i][j];
            }
        }
        delete boardWidget;
    }) ;

}

//将path的图片放置到label上，自适应label大小
void GameWidget::setAdaptedImg(QString path,QLabel *label)
{
    QImage image(path);
    QSize size=label->size();

    QImage image2=image.scaled(size,Qt::IgnoreAspectRatio);//重新调整图像大小以适应label
    label->setPixmap(QPixmap::fromImage(image2));//显示
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
    //if(allowMagic && QRandomGenerator::global()->bounded(0, 85) == 1)        //Magic方块1/85生成概率
    //return 0;
    return QRandomGenerator::global()->bounded(1, DIFFICULITY+1);
}

void GameWidget::initScene(){
    boardWidget = new QWidget(this);
    boardWidget->show();
    boardWidget->setGeometry(665, 44, 952, 952);
    QRandomGenerator::global()->fillRange(gemType[0], 64);
    //掉落动画
    QParallelAnimationGroup *group=new QParallelAnimationGroup;
    for(int j = 7; j >=0; --j){
        for(int i = 0; i <8 ; ++i){
            gemType[i][j] = gemType[i][j] % DIFFICULITY + 1;
            gems[i][j] = new Gem(gemType[i][j], 118, i, j , boardWidget);
            group->addAnimation(startfallAnimation(gems[i][j],j+1));
            //gems[i][j]->installEventFilter(this);
            connect(gems[i][j], &Gem::mouseClicked, this, &GameWidget::act);
        }
    }
    group->start(QAbstractAnimation::DeleteWhenStopped);

    QTimer::singleShot(2500,this,[=](){
        int s = updateBombList();
        eliminateBoard();
        Sleep(2500);
        while(s!=0){
            s = updateBombList();
            eliminateBoard();
            Sleep(2500);
        }
    });

}

QPropertyAnimation* GameWidget::startfallAnimation(Gem *gem, int h){
    //每一行的掉落动画
    QPropertyAnimation* animation = new QPropertyAnimation(gem, "geometry", boardWidget);
    animation->setDuration((int)(sqrt((8-h)*300+550)*20));//
    animation->setStartValue(QRect(gem->oriX, gem->oriY-118*h-(8-h)*30, LEN, LEN));//
    animation->setEndValue(QRect(gem->oriX, gem->oriY, LEN, LEN));
    animation->setEasingCurve(QEasingCurve::Linear);
    return animation;
}

void GameWidget::fallAnimation(Gem *gem, int h){
    QPropertyAnimation* animation = new QPropertyAnimation(gem, "geometry", this);
    animation->setDuration(500);
    animation->setStartValue(gem->geometry());
    animation->setEndValue(QRect(gem->geometry().x(), gem->geometry().y() + LEN*h, gem->width(), gem->height()));
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

void GameWidget::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void GameWidget::fall(){
    for(int i = 0; i < 8; ++i)
        for(int j = 7; j >= 0; --j){
            if(fallHeight[i][j] != -1 && fallHeight[i][j] != 0 && gemType[i][j] != 100){
                gemType[i][j + fallHeight[i][j]] = gemType[i][j];
                gems[i][j]->setY(gems[i][j]->y + fallHeight[i][j]);
                gems[i][j + fallHeight[i][j]] = gems[i][j];
                gemType[i][j] = 100;
                fallAnimation(gems[i][j], fallHeight[i][j]);
            }
        }
}

void GameWidget::fill(){
    QTimer::singleShot(100, this, [=](){
        int lack[8] = {0};

        for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j)
                if(fallHeight[i][j] == -1)
                    lack[i]++;
                else if(fallHeight[i][j] != 0){
                    lack[i] += fallHeight[i][j];
                    break;
                }
        }

        for(int i = 0; i < 8; ++i)
            for(int j = 0; j < lack[i]; ++j){
                gems[i][lack[i]-j-1] = new Gem(randomGem(true), LEN, i, lack[i]-j-1, boardWidget, -lack[i]);
                gems[i][lack[i]-j-1]->setGeometry(LEN*i, LEN*(-j-1), LEN, LEN);
                gemType[i][lack[i]-j-1] = gems[i][lack[i]-j-1]->type;
                //gems[i][lack[i]-j-1] -> installEventFilter(this);
                connect(gems[i][lack[i]-j-1], &Gem::mouseClicked, this, &GameWidget::act);
            }

        for(int i = 0; i < 8; ++i)
            for(int j = 0; j < lack[i]; ++j){
                fallAnimation(gems[i][lack[i]-j-1], lack[i]);
            }
    });
}

//交换按钮位置
void GameWidget::swap(int gemX,int gemY){
    //处理宝石交换
    int xVal1 = gems[selectedX][selectedY]->x*118;int yVal1 = gems[selectedX][selectedY]->y*118;
    int width1 = gems[selectedX][selectedY]->width();int height1 = gems[selectedX][selectedY]->height();

    int xVal2 = gems[gemX][gemY]->x*118;int yVal2 = gems[gemX][gemY]->y*118;
    int width2 = gems[gemX][gemY]->width();int height2 = gems[gemX][gemY]->height();

    //宝石
    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    QPropertyAnimation *anim1 = new QPropertyAnimation(gems[selectedX][selectedY],"geometry",boardWidget);
    anim1->setDuration(300);
    anim1->setStartValue(QRect(xVal1,yVal1,width1,height1));
    anim1->setEndValue(QRect(xVal2,yVal2,width2,height2));
    anim1->setEasingCurve(QEasingCurve::Linear);
    //宝石动图
    QPropertyAnimation *anim11 = new QPropertyAnimation(gems[selectedX][selectedY]->gifLabel,"geometry",boardWidget);
    anim11->setDuration(300);
    anim11->setStartValue(QRect(xVal1,yVal1,width1,height1));
    anim11->setEndValue(QRect(xVal2,yVal2,width2,height2));
    anim11->setEasingCurve(QEasingCurve::Linear);
    //被交换宝石
    QPropertyAnimation *anim2 = new QPropertyAnimation(gems[gemX][gemY],"geometry",boardWidget);
    anim2->setDuration(300);
    anim2->setStartValue(QRect(xVal2,yVal2,width2,height2));
    anim2->setEndValue(QRect(xVal1,yVal1,width1,height1));
    anim2->setEasingCurve(QEasingCurve::Linear);

    group->addAnimation(anim1);
    group->addAnimation(anim11);
    group->addAnimation(anim2);
    group->start();
}

void GameWidget::makeSpin(){
    gems[selectedX][selectedY]->setStyleSheet(QString("QPushButton{background-color:transparent;border:0px;}"));
    gems[selectedX][selectedY]->gifLabel = new QLabel(gems[selectedX][selectedY]);
    gems[selectedX][selectedY]->gifLabel->setGeometry(0,0,gems[selectedX][selectedY]->width(), gems[selectedX][selectedY]->height());
    gems[selectedX][selectedY]->gif = new QMovie(gems[selectedX][selectedY]->path_dynamic[gems[selectedX][selectedY]->type], QByteArray(), gems[selectedX][selectedY]);
    gems[selectedX][selectedY]->gif->setScaledSize(QSize(gems[selectedX][selectedY]->width(), gems[selectedX][selectedY]->height()));
    gems[selectedX][selectedY]->gifLabel->setMovie(gems[selectedX][selectedY]->gif);
    gems[selectedX][selectedY]->gifLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    gems[selectedX][selectedY]->gifLabel->show();
    gems[selectedX][selectedY]->gif->start();
}

void GameWidget::act(Gem* gem){
    int len = 118;
    int gemX = gem->x;
    int gemY = gem->y;

    //如果当前没有宝石被选中，则让点击的宝石选中
    if(selectedX==-1 && selectedY==-1){
        selectedX = gemX;
        selectedY = gemY;

        //加选框
        selectedLbl = new QLabel(boardWidget);
        QImage image("://picture/GameWidget/selected.png");
        selectedLbl->setPixmap(QPixmap::fromImage(image));
        selectedLbl->setGeometry(len*selectedX, len*selectedY, len, len);
        selectedLbl->setAttribute(Qt::WA_TransparentForMouseEvents);
        selectedLbl->show();
        //让选中宝石旋转
        makeSpin();

    }
    //如果有宝石选中，并点击了邻居宝石，则让宝石交换
    else if(  ( (selectedX==gemX)&&(abs(selectedY-gemY)==1)  )
              || ( (selectedY==gemY)&&(abs(selectedX-gemX)==1) ) ){



        //去选框
        selectedLbl->clear();

        //让选中宝石与(gemX,gemY)交换
        swap(gemX,gemY);

        //静止
        makeStopSpin();

        //在对象矩阵中交换
        std::swap(gems[gemX][gemY],gems[selectedX][selectedY]);
        std::swap(gems[gemX][gemY]->x,gems[selectedX][selectedY]->x);
        std::swap(gems[gemX][gemY]->y,gems[selectedX][selectedY]->y);

        int currentScore = updateBombList();//将这次的分数返回，如果是0就回退
        if(currentScore == 0) {
            Sleep(500);
            std::swap(gemX,selectedX);
            std::swap(gemY,selectedY);
            swap(gemX,gemY);
            Sleep(500);
            //静止
            makeStopSpin();

            //在对象矩阵中交换
            std::swap(gems[gemX][gemY],gems[selectedX][selectedY]);
            std::swap(gems[gemX][gemY]->x,gems[selectedX][selectedY]->x);
            std::swap(gems[gemX][gemY]->y,gems[selectedX][selectedY]->y);
        }
        score += currentScore;//加上分数
        Sleep(500);

        eliminateBoard();
        Sleep(2000);
        while(currentScore!=0){
            currentScore = updateBombList();
            eliminateBoard();
            Sleep(2000);
            score += currentScore;//加上分数
        }

        selectedX=-1;
        selectedY=-1;
    }
    //如果当前有选中的宝石，点击了非邻居宝石，则取消选中
    else
    {
        //去选框
        selectedLbl->clear();
        //静止
        makeStopSpin();

        selectedX=-1;
        selectedY=-1;
    }
}

//在调用eliminate()后使用
void GameWidget::eliminateBoard(){
    if(bombList.size()==0)
        return;
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j)
            fallHeight[i][j]=0;

    //计算当前页面宝石要掉落的高度
    for(int i=0;i<static_cast<int>(bombList.size());i++){
        gemType[bombList[i]->x][bombList[i]->y] = 100;
        fallHeight[bombList[i]->x][bombList[i]->y] = -1;
        for(int k = bombList[i]->y - 1; k >= 0; --k)
            if(fallHeight[bombList[i]->x][k] != -1)
                fallHeight[bombList[i]->x][k]++;
    }

    //消去宝石
    for(int i=0;i<static_cast<int>(bombList.size());i++)
        bombList[i]->bomb();

    //当前页面宝石掉落
    fall();

    //随机生成新宝石并掉落
    fill();
}

void GameWidget::makeStopSpin(){
    gems[selectedX][selectedY]->gif->stop();
    gems[selectedX][selectedY]->gifLabel->clear();

    gems[selectedX][selectedY]->setStyleSheet(QString("QPushButton{border-image:url(%1);}").arg(gems[selectedX][selectedY]->path_stable[gems[selectedX][selectedY]->type]));
    gems[selectedX][selectedY]->setIconSize(QSize(LEN, LEN));
}



//检测宝石并消除符合条件的宝石，返回分数
int GameWidget::updateBombList() {
    QString str = "";
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
        {
            str+=QString::number(gems[i][j]->type)+" ";
        }
        str+="fuck";
    }
    qDebug()<<str;

    int score = 0;//消除一个加10分
    int eliminating[8][8];//要消除的坐标
    memset(eliminating, 0, sizeof(eliminating));
    for(int i=0;i<8;i++){
        int start=0,end=0;
        //当start超过5，没有检测的必要，必然连着的超不过三个
        while(start<=5){
            while(gems[i][start]->type==gems[i][end]->type){
                end++;
            }
            end--;
            if(end-start>=2){
                for(int j=start;j<=end;j++){
                    eliminating[i][j]=1;
                }
            }
            end++;
            start=end;
        }
    }
    for(int i=0;i<8;i++){
        int start=0,end=0;
        //当start超过5，没有检测的必要，必然连着的超不过三个
        while(start<=5){
            while(gems[start][i]->type==gems[end][i]->type){
                end++;
            }
            end--;
            if(end-start>=2){
                for(int j=start;j<=end;j++){
                    eliminating[j][i]=1;
                }
            }
            end++;
            start=end;
        }
    }

    str="";
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
        {
            str+=QString::number(eliminating[i][j])+" ";
        }
        str+="fuck";
    }

    qDebug()<<str;

    str = "";
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
        {
            str+=QString::number(gems[i][j]->type)+" ";
        }
        str+="fuck";
    }
    qDebug()<<str;

    bombList.clear();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(eliminating[i][j] != 0){
                bombList.push_back(gems[i][j]);
                score += 10;//每个加10分
            }
        }
    }
    return score;
}
