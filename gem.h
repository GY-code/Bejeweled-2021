#ifndef GEM_H
#define GEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMovie>
#include <QDebug>

#define LEN 118

class Gem:public QPushButton
{
    Q_OBJECT
public:
    QString path_stable[8];
    QString path_dynamic[8];
    void initialPath();
    int type;
    int x, y;
    int oriX,oriY;
    explicit Gem(int type, int len, int x, int y, QWidget *parent = nullptr, int offset=0);
    void bomb();
    QMovie* gif;
    QLabel* gifLabel;
private:

signals:
    void mouseClicked(Gem*);

};

#endif // GEM_H
