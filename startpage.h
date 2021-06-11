#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QDebug>
#include <QImage>
#include <QFile>
#include "hoverbutton.h"
#include "gamewidget.h"
#include <QTime>
#include <QTemporaryDir>
#include<qsound.h>
#include<qmediaplayer.h>
#include<qsoundeffect.h>
#include"settingpage.h"
namespace Ui {
class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    ~StartPage();
    GameWidget* gameWidget=new GameWidget;

    QPropertyAnimation *bkAnim;
    settingpage settingP;
    //volumeWidget volumeW;
     QSoundEffect* sound;
protected:
    virtual void keyPressEvent(QKeyEvent *ev);
private:
    Ui::StartPage *ui;
    HoverButton *startButton, *recordButton, *settingButton;
    //HoverButton *bright,*volume;

    QLabel *background;
    QPropertyAnimation *  ShowBackground();
    QPropertyAnimation * ShowTitle();
    void SetButton();
    void setBkImg(QString path,QLabel *label);
    void setAdaptedImg(QString path,QLabel *label);
    void Sleep(int msec);

};

#endif // STARTPAGE_H
