#include "selectlevel.h"
#include "ui_selectlevel.h"
#include"qfont.h"
selectlevel::selectlevel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::selectlevel)
{
    ui->setupUi(this);

    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    levelL->setGeometry(260,20,91,41);
    level1L->setGeometry(110,130,51,21);
    level2L->setGeometry(250,130,81,21);
    level3L->setGeometry(420,130,51,21);
    DoneL->setGeometry(260,213,101,21);
    levelL->setParent(this);
    levelL->setVisible(true);
    level1L->setParent(this);
    levelL->setVisible(true);
    level2L->setParent(this);
    levelL->setVisible(true);
    level3L->setParent(this);
    levelL->setVisible(true);
    DoneL->setParent(this);
    DoneL->setVisible(true);

    QFont font ( "Arial Black", 12, 87);
    levelL->setFont(font);
    levelL->setFont(font);
    level1L->setFont(font);
    level2L->setFont(font);
    level3L->setFont(font);
    DoneL->setFont(font);
    //去窗口边框
    this->setWindowFlags(Qt::FramelessWindowHint | this->windowFlags());
    //把窗口背景设置为透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    //鼠标移动改变形状
    ui->level1B->setCursor(QCursor(Qt::PointingHandCursor));
    ui->level2B->setCursor(QCursor(Qt::PointingHandCursor));
    ui->level3B->setCursor(QCursor(Qt::PointingHandCursor));
    ui->DoneB->setCursor(QCursor(Qt::PointingHandCursor));
    //防止标签遮挡
    level1L->setAttribute(Qt::WA_TransparentForMouseEvents);
    level2L->setAttribute(Qt::WA_TransparentForMouseEvents);
    level3L->setAttribute(Qt::WA_TransparentForMouseEvents);
    DoneL->setAttribute(Qt::WA_TransparentForMouseEvents);

    white.setColor(QPalette::WindowText,Qt::white);
    dyellow.setColor(QPalette::WindowText,Qt::darkYellow);
    purple.setColor(QPalette::WindowText,Qt::magenta);

    initColor();
    level1L->setPalette(purple);
}

selectlevel::~selectlevel()
{
    delete ui;
}


//点击变色
void selectlevel::on_level1B_pressed()
{
    level1L->setPalette(dyellow);
}


void selectlevel::on_level1B_released()
{
    level=4;
    initColor();
    level1L->setPalette(purple);
}

void selectlevel::on_level2B_pressed()
{
    level2L->setPalette(dyellow);
}

void selectlevel::on_level2B_released()
{
    level=6;
    initColor();
    level2L->setPalette(purple);
}

void selectlevel::on_level3B_pressed()
{
    level3L->setPalette(dyellow);
}

void selectlevel::on_level3B_released()
{
    level=7;
    initColor();
    level3L->setPalette(purple);
}

void selectlevel::on_DoneB_pressed()
{
    DoneL->setPalette(dyellow);
}

void selectlevel::on_DoneB_released()
{
    DoneL->setPalette(white);
    this->setVisible(false);
    this->selectDone(level);
}

//点击done关闭难度选择界面
void selectlevel::on_DoneB_clicked()
{

}

void selectlevel::initColor()
{
    level1L->setPalette(white);
    level2L->setPalette(white);
    level3L->setPalette(white);
    levelL->setPalette(white);
    DoneL->setPalette(white);
}

void selectlevel::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0, 0, pixmap);
}
