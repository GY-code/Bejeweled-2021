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
#include<QTime>
#include <QMainWindow>
#include<qsound.h>
#include<qsoundeffect.h>
#include<QTemporaryDir>
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
    explicit GameWidget(QWidget *parent = nullptr);
    void setAdaptedImg(QString path,QLabel *label);
    void setupScene();
    QSoundEffect* sound;
protected:
    virtual void keyPressEvent(QKeyEvent *ev)override;

private:
    int times=6;
    int score=0;
    bool is_acting=false;
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

    QPropertyAnimation* startfallAnimation(Gem *gem, int h);
    int randomGem();
    void startGame();
    int DIFFICULITY=5;
    void fall();
    void fill();
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
    QLabel* selectedLbl=nullptr;

    void forbidAll(bool forbid);

    Ui::GameWidget *ui;
signals:
    void showStartPage();
    void eliminateFinished();
};

#endif // GAMEWIDGET_H
