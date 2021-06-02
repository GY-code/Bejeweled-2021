#include "myprobar.h"
#include <QDebug>

MyProBar::MyProBar(QWidget *parent) : QProgressBar(parent)
{

}
void MyProBar::paintEvent(QPaintEvent *e)
{

    //height-40px;
    QPainter painter(this);
    QPainterPath *draw_path = new QPainterPath;
    int radius=30;
    double percent=static_cast<double>(value())/static_cast<double>(maximum());
    percent=percent/15;
    painter.setRenderHint(QPainter::Antialiasing);
    while (radius*2>height()) {
        radius--;
    }

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
    if(value()>0){
        painter.fillPath(*draw_path,QColor("#D8D8D8"));
    }else{
        painter.fillPath(*draw_path,Qt::transparent);		//若进度位0%，进度条自动隐身
    }

    draw_path = new QPainterPath;
    double x_move=(percent*width());
    double theta=acos(abs(x_move-radius)/radius);
    double y_move=(sin(theta)*radius);
    if(percent*width()<=radius){
        draw_path->moveTo(x_move,radius-y_move);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),static_cast<int>(180-theta/M_PI*180),static_cast<int>(theta/M_PI*180));
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),180,static_cast<int>(theta/M_PI*180));
        draw_path->lineTo(static_cast<int>(x_move),static_cast<int>(radius-y_move));

//        painter.setPen(QColor(0, 0, 0));
//        painter.drawArc(QRect(0,0,radius*2,radius*2),static_cast<int>(180-theta/M_PI*180)*16,static_cast<int>(theta/M_PI*180)*16);
//        painter.drawArc(QRect(0,0,radius*2,radius*2),180*16,static_cast<int>(theta/M_PI*180)*16);
//        painter.drawLine(QPointF(x_move,radius+y_move),QPointF(x_move,radius-y_move));
    }
    else if(percent*width()<radius*2){
        draw_path->moveTo(radius,0);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),90,90);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),180,90);
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),270,static_cast<int>(90-theta/M_PI*180));
        draw_path->lineTo(static_cast<int>(x_move),static_cast<int>(radius-y_move));
        draw_path->arcTo(QRect(0,0,radius*2,radius*2),90-static_cast<int>(90-theta/M_PI*180),static_cast<int>(90-theta/M_PI*180));

//        painter.setPen(QColor(0, 0, 0));
//        painter.drawArc(QRect(0,0,radius*2,radius*2),90*16,90*16);
//        painter.drawArc(QRect(0,0,radius*2,radius*2),180*16,90*16);
//        painter.drawArc(QRect(0,0,radius*2,radius*2),270*16,static_cast<int>(90-theta/M_PI*180)*16);
//        painter.drawLine(QPointF(x_move,radius+y_move),QPointF(x_move,radius-y_move));
//        painter.drawArc(QRect(0,0,radius*2,radius*2),(90-static_cast<int>(90-theta/M_PI*180))*16,static_cast<int>(90-theta/M_PI*180)*16);
    }else{
        qDebug()<<"3"<<percent;
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

    painter.fillPath(*draw_path,QColor("#67B5B7"));

}


