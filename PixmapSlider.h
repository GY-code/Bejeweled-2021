#ifndef PIXMAPSLIDER_H
#define PIXMAPSLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QPainter>


class PixmapSlider : public QWidget
{
    Q_OBJECT
public:
    PixmapSlider(QWidget *parent = 0);
    ~PixmapSlider();

public:
    void SetPos(int mPos,bool nFlag = false);
    void SetRange(int m_MinPos, int m_MaxPos);
    void SetStep(int nStep){ m_nStep = nStep;}
    void UpdatePosAdd();
    void UpdatePosRedu();
    //void SetBuddy(NumSpin *m_nSpin,bool m_Flag = true);
    void SetChannelImage(QString normalPic,QString activePic);
    void SetThumbImage(QString normalPic,QString activePic);
    void SetVertical( bool bVertical=false ) { m_bVertical = bVertical; }
    void SetMargin( int nLeft, int nTop, int nRight, int nBottom );
    void SetDisableFlg(bool nFlag);

private:
    int Pos2Pixel(int nPos);
    int Pixel2Pos(int nPixel);

    void UpDataPressDown(QPoint point);

public:
    bool m_nFocus;

private:
    QPoint m_movePoint;
    bool m_flag_mousePress;   //按下鼠标左键
    bool m_flag_ThumbPress;   // 按下推子区域
    bool m_bEnable;
    int m_nMouseOffset;

    bool m_bVertical;
    int m_nStep;
    int m_nPos;
    int m_nMax;
    int m_nMin;
    int m_nThumbHeight;
    int m_nThumbWidth;

    bool m_BuddySpinFocus;
   // NumSpin *m_nBuddySpin;

    QPixmap m_nNormalChannelPic,m_nActiveChannelPic;
    QPixmap m_nThumb_Normal,m_nThumb_Active;
    QRect m_nRect;
    QRect m_nThumbRect;
    QRect fillRect;
    int m_nMarginLeft, m_nMarginRight, m_nMarginTop, m_nMarginBottom;

signals:
    void sliderClicked();
    void valueChanged(int);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);     //单击
    void mouseReleaseEvent(QMouseEvent *event);    //释放
//    void mouseDoubleClickEvent(QMouseEvent *event);   //双击
    void mouseMoveEvent(QMouseEvent *event);   //移动
//    void wheelEvent(QWheelEvent *event);    //滑轮
    void focusOutEvent(QFocusEvent *e);

};

#endif // PIXMAPSLIDER_H
