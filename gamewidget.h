#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

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
    //virtual void keyReleaseEvent(QKeyEvent *ev);

private:
    unsigned int gemBoard[8][8];
    Gem* gems[8][8];
    int fallboard[8][8];
    QWidget* boardWidget=nullptr;
    HoverButton *menuButton=nullptr;
    HoverButton *hintButton=nullptr;
    HoverButton *pauseButton=nullptr;
    int randomGem(bool allowMagic);
    void initScene();
    int DIFFICULITY=5;
    void fall();
    QPropertyAnimation* fallAnimation(Gem *gem, int h);
    void Sleep(int msec);
    void act(Gem* gem);
    int selectedX=-1,selectedY=-1;
    QLabel* selectedLbl=nullptr;



    Ui::GameWidget *ui;
signals:
    void showStartPage();
};

#endif // GAMEWIDGET_H
