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

namespace Ui {
class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    ~StartPage();
    GameWidget* gameWidget;
    QPropertyAnimation *bkAnim;
protected:
    virtual void keyPressEvent(QKeyEvent *ev);
private:
    Ui::StartPage *ui;
    HoverButton *startButton, *recordButton, *settingButton;
    QLabel *background;
    void ShowBackground();
    void ShowTitle();
    void SetButton();
    void setBkImg(QString path,QLabel *label);
    void setAdaptedImg(QString path,QLabel *label);

};

#endif // STARTPAGE_H
