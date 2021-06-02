#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QSound>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
class HoverButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HoverButton(QWidget *parent = nullptr);
    void setImage(QString pathNormal, QString pathHover, int width, int height);
    void setSound(QString pathHover="", QString pathLeave="", QString pathPress="", QString pathRelease="");
    void setLabel(QString text,int size);
    void setCircle(int r, int x, int y, int width, int height, QString path, QString path2, QWidget *parent);
    void showContent(QString text,int size);
    QPropertyAnimation* animation = new QPropertyAnimation;

protected:
    bool event(QEvent *e) override;

private:
    int w=0, h=0,textSize;
    QSound *soundHover = nullptr, *soundPress = nullptr, *soundRelease = nullptr, *soundLeave = nullptr;
    QIcon *iconNormal=nullptr, *iconHover=nullptr;
    QLabel* label=nullptr;

};

#endif // HOVERBUTTON_H
