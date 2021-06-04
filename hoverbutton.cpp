#include "hoverbutton.h"
#include <QDebug>

HoverButton::HoverButton(QWidget *parent) : QPushButton(parent)
{
    //设置无边框
    setStyleSheet("QPushButton{border:0px;}");
}

void HoverButton::setImage(QString pathNormal, QString pathHover, int width, int height,QLabel *label){

    w = width; h =height;
    //设置正常和激活后的控件图标
    if(label){
        iconNormal = QIcon(QPixmap(pathNormal).scaled(label->width(),label->height()));
        iconHover = (pathHover != QString("") ? QIcon(QPixmap(pathHover).scaled(label->width(),label->height()))
                                              : QIcon(QPixmap(pathNormal).scaled(label->width(),label->height())));
    }else{
        iconNormal = QIcon(QPixmap(pathNormal));
        iconHover = (pathHover != QString("") ? QIcon(QPixmap(pathHover)) : QIcon(QPixmap(pathNormal)));
    }

    this->setIcon(iconNormal);
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
    textAnim->setParent(parent);
    textAnim->setTargetObject(this);
    textAnim->setDuration(2000);
    textAnim->setPropertyName("geometry");
    textAnim->setStartValue(QRect(x - r, height, 2*r, 2*r));
    textAnim->setEndValue(QRect(x - r, y - r, 2*r, 2*r));
    textAnim->setEasingCurve(QEasingCurve::InOutCubic);
    setVisible(false);
}

void HoverButton::showContent(QString text,int size){
    setVisible(true);
    setLabel(text,size);
}

bool HoverButton::event(QEvent *e) {
    if(!isEnabled())
        return QPushButton::event(e);
    switch(e->type()){
    case QEvent::Enter:
        //设置鼠标-手指
        setCursor(QCursor(QPixmap("://picture/mouse2.png")));
        setIcon(iconHover);
        if(soundHover)
            soundHover->play();
        if(label)
            label->setFont(QFont("Microsoft YaHei", (textSize*1.5), QFont::Bold));
        break;
    case QEvent::Leave:
        //设置鼠标-普通
        setCursor(QCursor(QPixmap("://picture/mouse1.png")));
        setIcon(iconNormal);
        if(soundLeave)
            soundLeave->play();
        if(label)
            label->setFont(QFont("Microsoft YaHei", textSize, QFont::Normal));
        break;
    case QEvent::MouseButtonPress:
        //设置鼠标-press
        setCursor(QCursor(QPixmap("://picture/mouse3.png")));
        if(soundPress)
            soundPress->play();
        if(label)
            label->setFont(QFont("Microsoft YaHei", textSize*1.5, QFont::Bold));
        break;
    case QEvent::MouseButtonRelease:
        //设置鼠标-release
        setCursor(QCursor(QPixmap("://picture/mouse2.png")));
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
