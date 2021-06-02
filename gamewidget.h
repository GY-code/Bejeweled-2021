#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QIcon>
#include <QTimer>
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
    ~GameWidget();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *ev)override;
    //virtual void keyReleaseEvent(QKeyEvent *ev);

private:
    unsigned int gemBoard[8][8];
    Gem* gems[8][8];
    int fallboard[8][8];
    QWidget* boardWidget;
    int randomGem(bool allowMagic);
    void initScene();
    int DIFFICULITY=5;
    void fall();
    void test();
    void fallAnimation(Gem *gem, int h);
    void Sleep(int msec);


    Ui::GameWidget *ui;
};

#endif // GAMEWIDGET_H
