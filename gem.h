#ifndef GEM_H
#define GEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMovie>
class Gem:public QPushButton
{
    Q_OBJECT
public:
    QString path_stable[8];
    QString path_dynamic[8];
    void initialPath();
    int type;
    int x, y;
    explicit Gem(int type, int len, int x, int y, QWidget *parent = nullptr, int offset=0);
    void bomb();
private:
    QMovie* gif;
    QLabel* gifLabel;

signals:
    void mouseClicked(Gem*);

};

#endif // GEM_H
