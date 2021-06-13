#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <iostream>
#include <string.h>
#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QIcon>
#include <QTimer>
#include <hoverbutton.h>
#include <myprobar.h>
#include <QRandomGenerator>
#include "gem.h"
#include <QTime>
#include <QMainWindow>
#include<qsound.h>
#include<qsoundeffect.h>
#include<QTemporaryDir>
#include <QFont>
#include"settingpage.h"
#define TO_BOMB 100
class Point{
public:
    int x;
    int y;
    Point(int x1,int y1){
        x=x1;
        y=y1;
    }

};

namespace Ui {
class GameWidget;
}

class GameWidget : public QMainWindow
{
    Q_OBJECT

public:
    int DIFFICULITY=5;
    explicit GameWidget(QWidget *parent = nullptr);
    void setAdaptedImg(QString path,QLabel *label);
    void setupScene();
    QSoundEffect* sound;

protected:
    virtual void keyPressEvent(QKeyEvent *ev)override;

private:
    int FTime=0;
    int mousePosX=-1,mousePosY=-1;
    bool exitMagic=false;

    int hintArrowTimes=6;
    int score=0;
    bool is_acting=false;
    bool is_paused=false;

    QLabel* scoreTextLbl=nullptr;

    QLabel* pauseBKLbl = nullptr;
    QMovie* pauseBKgif = nullptr;
    QLabel* pauseTXLbl = nullptr;

    int fallNum=0;
    int fallCount=0;

    unsigned int gemType[8][8];//type数组
    Gem* gems[8][8];//gem对象数组
    int fallHeight[8][8];//掉落高度数组
    std::vector<Gem*> bombList; //存要消去的宝石
    int updateBombList();

    QWidget* boardWidget=nullptr;
    HoverButton *menuButton=nullptr;
    HoverButton *hintButton=nullptr;
    HoverButton *pauseButton=nullptr;
    MyProBar* progressBar=nullptr;
    QTimer *progressTimer=nullptr;
    QLabel* selectedLbl=nullptr;
    int redBordershow=0;
    double trans=0;

    QPropertyAnimation* startfallAnimation(Gem *gem, int h);
    int randomGem();
    void startGame();
    void fall();
    void fill();
    void magicFall();
    void magicFill();
    void makeStopSpin(int,int);
    void makeSpin(int,int);
    void swap(int, int, int gemX,int gemY);
    void eliminateBoard();
    Point tipsdetect();

    void fallAnimation(Gem *gem, int h);
    void fillfallAnimation(Gem *gem, int h);
    void Sleep(int msec);
    void act(Gem* gem);
    int selectedX=-1,selectedY=-1;

    void forbidAll(bool forbid);
    std::vector<Gem*> bombsToMakeMagic1;
    std::vector<Gem*> bombsToMakeMagic2;
    std::vector<Gem*> tList1;
    std::vector<Gem*> tList2;
    int getBombsToMakeMagic(int cX,int cY,std::vector<Gem*> bombsToMakeMagic,int time);
    void generateMagic(int cX,int cY,int type,int time);
    void finishAct();
    int tHeight[8][8];
    void magicCollect(int coType,int toX,int toY);
    settingpage settingP;

    Ui::GameWidget *ui;
signals:
    void showStartPage();
    void eliminateFinished();
    void myMouseMove(QMouseEvent*);
    void finishCount();
};

#endif // GAMEWIDGET_H
