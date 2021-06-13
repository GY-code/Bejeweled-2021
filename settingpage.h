#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QMainWindow>
#include"PixmapSlider.h"
#include<QLabel>
static int index=0;
namespace Ui {
class settingpage;
}

class settingpage : public QMainWindow
{

    Q_OBJECT

public:
    explicit settingpage(QWidget *parent = nullptr);
    ~settingpage();

private slots:


    void on_Help_clicked();

    void on_Web_clicked();

    void on_Done_clicked();
    void paintEvent(QPaintEvent *event);


    bool SetVolumeLevel(int level);
    void onVolumeValueChanged(int);
    void onSpinValueChanged(int i);



    void on_LangB_clicked();

private:
    Ui::settingpage *ui;

    PixmapSlider * slider1;
    PixmapSlider * slider2;


signals:
    void selectLan(int index);
};

#endif // SETTINGPAGE_H
