#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QMainWindow>
#include"PixmapSlider.h"
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


private:
    Ui::settingpage *ui;

    PixmapSlider * slider1;
    PixmapSlider * slider2;

};

#endif // SETTINGPAGE_H
