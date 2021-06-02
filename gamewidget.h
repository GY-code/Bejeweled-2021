#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QIcon>
#include <QTimer>
#include <hoverbutton.h>
#include <myprobar.h>

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
    virtual void keyPressEvent(QKeyEvent *ev);
    //virtual void keyReleaseEvent(QKeyEvent *ev);

private:
    Ui::GameWidget *ui;
};

#endif // GAMEWIDGET_H
