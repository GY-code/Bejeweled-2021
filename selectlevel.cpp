#include "selectlevel.h"
#include "ui_selectlevel.h"

selectlevel::selectlevel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::selectlevel)
{
    ui->setupUi(this);
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
    ui->level1L->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->level2L->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->level3L->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->label->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->DoneL->setAttribute(Qt::WA_TransparentForMouseEvents);

    yellow.setColor(QPalette::WindowText,Qt::yellow);
    dyellow.setColor(QPalette::WindowText,Qt::darkYellow);
    red.setColor(QPalette::WindowText,Qt::red);

    initColor();
}

selectlevel::~selectlevel()
{
    delete ui;
}


//点击变色
void selectlevel::on_level1B_pressed()
{
    ui->level1L->setPalette(dyellow);
}


void selectlevel::on_level1B_released()
{
    level=5;
    initColor();
    ui->level1L->setPalette(red);
}

void selectlevel::on_level2B_pressed()
{
    ui->level2L->setPalette(dyellow);
}

void selectlevel::on_level2B_released()
{
    level=6;
    initColor();
    ui->level2L->setPalette(red);
}

void selectlevel::on_level3B_pressed()
{
    ui->level3L->setPalette(dyellow);
}

void selectlevel::on_level3B_released()
{
    level=7;
    initColor();
    ui->level3L->setPalette(red);
}

void selectlevel::on_DoneB_pressed()
{
    ui->DoneL->setPalette(dyellow);
}

void selectlevel::on_DoneB_released()
{
    ui->DoneL->setPalette(yellow);
    this->setVisible(false);
    this->selectDone(level);
}

//点击done关闭难度选择界面
void selectlevel::on_DoneB_clicked()
{

}

void selectlevel::initColor()
{
    ui->level1L->setPalette(yellow);
    ui->level2L->setPalette(yellow);
    ui->level3L->setPalette(yellow);
    ui->DoneL->setPalette(yellow);
}

