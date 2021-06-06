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


#define TO_BOMB 100

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    void setAdaptedImg(QString path,QLabel *label);
    void setupScene();
//    ~GameWidget();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *ev)override;

private:
    bool isActing;

    unsigned int gemType[8][8];//type数组
    Gem* gems[8][8];//gem对象数组
    int fallHeight[8][8];//掉落高度数组
    std::vector<Gem*> bombList; //存要消去的宝石


    QWidget* boardWidget=nullptr;
    HoverButton *menuButton=nullptr;
    HoverButton *hintButton=nullptr;
    HoverButton *pauseButton=nullptr;
    MyProBar* progressBar=nullptr;
    QTimer *progressTimer=nullptr;
    int randomGem(bool allowMagic);
    void initScene();
    int DIFFICULITY=5;
    void fall();
    void fill();
    void makeStopSpin();
    void makeSpin();
    void swap(int gemX,int gemY);
    void eliminateBoard();
    QPropertyAnimation* startfallAnimation(Gem *gem, int h);
    void fallAnimation(Gem *gem, int h);
    void Sleep(int msec);
    void act(Gem* gem);
    int selectedX=-1,selectedY=-1;
    QLabel* selectedLbl=nullptr;
    int updateBombList();
    int score=0;

    Ui::GameWidget *ui;
signals:
    void showStartPage();
    void eliminateFinished();
};

#endif // GAMEWIDGET_H
