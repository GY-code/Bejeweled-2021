#include "hoverbutton.h"
#include <QDebug>

HoverButton::HoverButton(QWidget *parent) : QPushButton(parent)
{
    //设置无边框
    setStyleSheet("QPushButton{border:0px;}");
    setSound();
}

void HoverButton::setImage(QString pathNormal, QString pathHover, int width, int height){
    if(iconNormal)
        delete iconNormal;
    if(iconHover)
        delete iconHover;

    w = width; h =height;
    //设置正常和激活后的控件图标
    iconNormal = new QIcon(pathNormal);
    iconHover = (pathHover != QString("") ? new QIcon(pathHover) : new QIcon(pathNormal));

    this->setIcon(*iconNormal);
    this->setIconSize(QSize(width, height));
}

void HoverButton::setSound(QString pathHover, QString pathLeave, QString pathPress, QString pathRelease){
    //设置覆盖、按压、释放、离开音效
    soundHover = (pathHover != QString("") ? new QSound(pathHover, this) : nullptr);
    soundPress = (pathPress != QString("") ? new QSound(pathPress, this) : nullptr);
    soundRelease = (pathRelease != QString("") ? new QSound(pathRelease, this) : nullptr);
    soundLeave = (pathLeave != QString("") ? new QSound(pathLeave, this) : nullptr);
}

void HoverButton::setLabel(QString text,int size){
    //设置label
    textSize=size;
    label = new QLabel(text, this);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
    label->setGeometry(0,0, w, h);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("Microsoft YaHei", size, QFont::Normal));
    label->setStyleSheet("QLabel{color:white;}");
    label->setVisible(true);
}
void HoverButton::setCircle(int r, int x, int y, int width, int height, QString path, QString path2, QWidget *parent)
{
    setParent(parent);
    setGeometry(x - r, y - r, 2*r, 2*r);
    setImage(path, path2, 2*r, 2*r);
//    setSound(":/music/button/button_mouseover.wav", ":/music/button/button_mouseleave.wav", ":/music/button/button_press.wav", ":/music/button/button_release.wav"); //默认音效
    animation->setParent(parent);
    animation->setTargetObject(this);
    animation->setDuration(2000);
    animation->setPropertyName("geometry");
    animation->setStartValue(QRect(x - r, height, 2*r, 2*r));
    animation->setEndValue(QRect(x - r, y - r, 2*r, 2*r));
    animation->setEasingCurve(QEasingCurve::InOutCubic);
    setVisible(false);

}

void HoverButton::showContent(QString text,int size){
    setVisible(true);
    animation->start();
    QTimer::singleShot(2000, this, [=](){
        setLabel(text,size);
    });
}


bool HoverButton::event(QEvent *e) {
    if(!isEnabled())
        return QPushButton::event(e);

    switch(e->type()){
    case QEvent::Enter:
        setIcon(*iconHover);
        if(soundHover)
            soundHover->play();
        if(label)
            label->setFont(QFont("Microsoft YaHei", textSize*1.5, QFont::Bold));
        break;
    case QEvent::Leave:
        setIcon(*iconNormal);
        if(soundLeave)
            soundLeave->play();
        if(label)
            label->setFont(QFont("Microsoft YaHei", textSize, QFont::Normal));
        break;
    case QEvent::MouseButtonPress:
        if(soundPress)
            soundPress->play();
        if(label)
            label->setFont(QFont("Microsoft YaHei", textSize*1.5, QFont::Bold));
        break;
    case QEvent::MouseButtonRelease:
        if(soundRelease)
            soundRelease->play();
        if(label)
            label->setFont(QFont("Microsoft YaHei", textSize, QFont::Normal));
        break;
    default:
        break;
    }
    return QPushButton::event(e);
}
