#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H

#include <QMainWindow>

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

private:
    Ui::selectlevel *ui;
    QPalette pe1;
    QPalette pe2;
};

#endif // SELECTLEVEL_H
