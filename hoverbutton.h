#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>
#include <QSound>
#include <QLabel>

class HoverButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HoverButton(QWidget *parent = nullptr);
    void setImage(QString pathNormal, QString pathHover, int width, int height);
    void setSound(QString pathHover="", QString pathLeave="", QString pathPress="", QString pathRelease="");
    void setLabel(QString text);



protected:
    bool event(QEvent *e) override;

private:
    int w=0, h=0;
    QSound *soundHover = nullptr, *soundPress = nullptr, *soundRelease = nullptr, *soundLeave = nullptr;
    QIcon *iconNormal=nullptr, *iconHover=nullptr;
    QLabel* label=nullptr;

};

#endif // HOVERBUTTON_H
