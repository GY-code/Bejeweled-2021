#include "gem.h"
Gem::Gem(int type, int len, int x, int y, QWidget *parent, int offset) : QPushButton(parent), type(type), x(x), y(y)
{
    initialPath();

    //setGeometry(len*x, len*(y+offset), len, len);
    oriX = LEN*x;  oriY = LEN*(y+offset);//setGeometry移至动画，现在创建Gem需要自己setgeometry

    setVisible(true);
    setStyleSheet(QString("QPushButton{border-image:url(%1);}").arg(path_stable[type]));
    setIconSize(QSize(len, len));

    connect(this, &Gem::pressed, [=](){
        this->mouseClickedGem(this);
    });
}

void Gem::initialPath(){
    path_stable[0] = ":/picture/GameWidget/Gem/Magic.png";
    path_stable[1] = ":/picture/GameWidget/Gem/Red.png";
    path_stable[2] = ":/picture/GameWidget/Gem/orange.png";
    path_stable[3] = ":/picture/GameWidget/Gem/Green.png";
    path_stable[4] = ":/picture/GameWidget/Gem/Blue.png";
    path_stable[5] = ":/picture/GameWidget/Gem/violet.png";
    path_stable[6] = ":/picture/GameWidget/Gem/Silver.png";
    path_stable[7] = ":/picture/GameWidget/Gem/Gold.png";
    path_dynamic[0] = ":/picture/GameWidget/Gem/Magic.gif";
    path_dynamic[1] = ":/picture/GameWidget/Gem/Red.gif";
    path_dynamic[2] = ":/picture/GameWidget/Gem/orange.gif";
    path_dynamic[3] = ":/picture/GameWidget/Gem/Green.gif";
    path_dynamic[4] = ":/picture/GameWidget/Gem/Blue.gif";
    path_dynamic[5] = ":/picture/GameWidget/Gem/violet.gif";
    path_dynamic[6] = ":/picture/GameWidget/Gem/Silver.gif";
    path_dynamic[7] = ":/picture/GameWidget/Gem/Gold.gif";

    path_dynamic[8] = ":/picture/GameWidget/Gem/0000.gif";
    path_dynamic[9] = ":/picture/GameWidget/Gem/fire.gif";
}
void Gem::bomb(){
    delete this;
}
