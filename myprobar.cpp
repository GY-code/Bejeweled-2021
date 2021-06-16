#include "myprobar.h"
#include <QDebug>

MyProBar::MyProBar(QWidget *parent) : QProgressBar(parent)
{

}
void MyProBar::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    QPainterPath *draw_path = new QPainterPath;
    int radius=height()/2;
    double percent=static_cast<double>(value())/static_cast<double>(maximum());
    painter.setRenderHint(QPainter::Antialiasing);

    draw_path = new QPainterPath;
    draw_path->moveTo(radius,0);
    draw_path->arcTo(QRect(0,0,radius*2,radius*2),90,90);
    draw_path->lineTo(0,height()-radius);
    draw_path->arcTo(QRect(0,0,radius*2,radius*2),180,90);
    draw_path->lineTo(width()-radius,height());
    draw_path->arcTo(QRect(width()-radius*2,0,radius*2,radius*2),270,90);
    draw_path->lineTo(width(),radius);
    draw_path->arcTo(QRect(width()-radius*2,0,radius*2,radius*2),0,90);
    draw_path->lineTo(radius,0);

    painter.fillPath(*draw_path,QColor(0, 0, 109));//背景色

    draw_path = new QPainterPath;
    double x_move=(percent*width());
    double theta=acos(abs(x_move-radius)/radius);
    double y_move=(sin(theta)*radius);


    if(x_move>radius*2){
        draw_path->moveTo(radius,0);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),90,90);
        draw_path->lineTo(0,height()-radius*2);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),180,90);
        draw_path->lineTo(percent*width()-radius*2,height());
        draw_path->arcTo(QRect(static_cast<int>(percent*width())-radius*2,0,radius*2,radius*2),270,90);
        draw_path->lineTo(percent*width(),radius*2);
        draw_path->arcTo(QRect(static_cast<int>(percent*width()-radius*2),0,radius*2,radius*2),0,90);
        draw_path->lineTo(radius*2,0);
    }
    else if(x_move<radius){
        draw_path->moveTo(x_move,radius-y_move);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),static_cast<int>(180-theta/M_PI*180),static_cast<int>(theta/M_PI*180));
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),180,static_cast<int>(theta/M_PI*180));
        draw_path->lineTo(static_cast<int>(x_move),static_cast<int>(radius-y_move));
    }
    else {// >=2*r
        draw_path->moveTo(radius,0);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),90,90);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),180,90);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),270,static_cast<int>(90-theta/M_PI*180));
        draw_path->lineTo(static_cast<int>(x_move),static_cast<int>(radius-y_move));
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),90-static_cast<int>(90-theta/M_PI*180),static_cast<int>(90-theta/M_PI*180));
    }


    if(percent>0.25)
        painter.fillPath(*draw_path,QColor(6, 118, 216));//前景色
    else
        painter.fillPath(*draw_path,QColor(205,38,38));//时间剩余不足时改为红色
}


