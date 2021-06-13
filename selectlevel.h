#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H

#include <QMainWindow>
#include<qpainter.h>

namespace Ui {
class selectlevel;
}

class selectlevel : public QMainWindow
{
    Q_OBJECT

public:
    explicit selectlevel(QWidget *parent = nullptr);
    ~selectlevel();

private slots:
    void on_level1B_pressed();

    void on_level1B_released();

    void on_level2B_pressed();

    void on_level3B_pressed();

    void on_DoneB_pressed();

    void on_level2B_released();

    void on_level3B_released();

    void on_DoneB_released();

    void on_DoneB_clicked();

    void initColor();
private:
    Ui::selectlevel *ui;
    QPalette yellow;
    QPalette dyellow;
    QPalette red;
    int level=5;
    void paintEvent(QPaintEvent *);
 //   StartPage* start=new StartPage();
signals:
    void selectDone(int difficulty);
};

#endif // SELECTLEVEL_H
