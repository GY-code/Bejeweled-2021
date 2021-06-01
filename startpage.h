#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QDebug>
#include <QImage>
#include <QFile>
#include "hoverbutton.h"
namespace Ui {
class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    ~StartPage();

private:
    Ui::StartPage *ui;
    HoverButton *exitButton,*startButton, *recordButton, *settingButton;

    void ShowBackground();
    void SetButton();
    void setBkImg(QString path,QLabel *label);
};

#endif // STARTPAGE_H
