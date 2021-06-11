#include "PixmapSlider.h"
#include <QPixmapCache>

PixmapSlider::PixmapSlider(QWidget *parent)
    : QWidget(parent)
{
    m_bVertical = false;
    m_flag_mousePress = false;
    m_flag_ThumbPress = false;
    m_BuddySpinFocus = false;
    m_bEnable = false;
    m_nFocus = false;
    m_nPos = 0;
    m_nStep = 1;
    m_nRect = QRect(0,0,this->width(),this->height());

    m_nMarginLeft = 0;
    m_nMarginRight = 0;
    m_nMarginTop = 0;
    m_nMarginBottom = 0;

    m_nThumbHeight = 0;
    m_nThumbWidth = 0;

    setCursor(Qt::PointingHandCursor);
    setFocusPolicy(Qt::ClickFocus);
    this->setMouseTracking(true);
    QPixmapCache::setCacheLimit(1);
}

PixmapSlider::~PixmapSlider()
{

}

// 传入数值 等价于 setValue
void PixmapSlider::SetPos(int mPos,bool nFlag)
{
    if(mPos >m_nMax)
        mPos =m_nMax;

    if(mPos <m_nMin)
        mPos =m_nMin;

    m_nPos = mPos;

    if(nFlag)
        emit valueChanged(m_nPos);

    update();
}

//   设置Slider背景图：normalPic为正常底图，activePic为活动底图

void PixmapSlider::SetChannelImage(QString normalPic,QString activePic)
{
    m_nNormalChannelPic = QPixmap(normalPic);
    m_nActiveChannelPic = QPixmap(activePic);
    m_nRect.setWidth(m_nNormalChannelPic.width());
    m_nRect.setHeight(m_nNormalChannelPic.height());
    this->setFixedSize(m_nRect.width(),m_nRect.height());

    if(m_nNormalChannelPic.width() > m_nNormalChannelPic.height())
        m_bVertical = false;
    else
        m_bVertical = true;
}

//   设置推子图

void PixmapSlider::SetThumbImage(QString normalPic,QString activePic)
{
    m_nThumb_Normal = QPixmap(normalPic);
    m_nThumb_Active = QPixmap(activePic);
    m_nThumbHeight = m_nThumb_Normal.height();
    m_nThumbWidth = m_nThumb_Normal.width();
}

//   设置推子上下左右的间距

void PixmapSlider::SetMargin( int nLeft, int nTop, int nRight, int nBottom )
{
    m_nMarginLeft = nLeft;
    m_nMarginRight = nRight;
    m_nMarginTop = nTop;
    m_nMarginBottom = nBottom;
}

//   自定义控件 有效值 范围

void PixmapSlider::SetRange(int m_MinPos, int m_MaxPos)
{
    m_nMax = m_MaxPos;
    m_nMin = m_MinPos;
}
// 外部滚轮或鼠标调用 自增
void PixmapSlider::UpdatePosAdd()
{
    int mPos;
    mPos = m_nPos+m_nStep;

    if(mPos >m_nMax)
        mPos =m_nMax;

    SetPos(mPos,true);
}
// 外部滚轮或鼠标调用 自减
void PixmapSlider::UpdatePosRedu()
{
    int mPos;
    mPos = m_nPos-m_nStep;

    if(mPos <m_nMin)
        mPos =m_nMin;

    SetPos(mPos,true);
}
// 绑定编辑框，用于点击控件 焦点转移
//void PixmapSlider::SetBuddy(NumSpin *m_nSpin,bool m_Flag)
//{
//    m_nBuddySpin = m_nSpin;
//    m_BuddySpinFocus = m_Flag;
//}

void PixmapSlider::SetDisableFlg(bool nFlag)
{
    m_bEnable = nFlag;
    if(m_bEnable)
        setCursor(Qt::PointingHandCursor);
    else
        setCursor(Qt::ArrowCursor);
}

void PixmapSlider::paintEvent(QPaintEvent *e)  //从QWidget子类化一个Widget，为了能够使用样式表则需要为自定义Widget提供paintEvent事件
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    if( m_bVertical) {
        fillRect = m_nRect.adjusted(0, 0, 0, Pos2Pixel(m_nMin + (m_nMax - m_nPos))-m_nRect.height());
        m_nThumbRect = QRect(m_nMarginLeft,Pos2Pixel(m_nMin + (m_nMax - m_nPos)) - m_nThumbHeight/2,m_nThumbWidth,m_nThumbHeight);

    }else{
        fillRect = m_nRect.adjusted(0, 0, Pos2Pixel(m_nPos)-m_nRect.width(), 0);
        m_nThumbRect = QRect(Pos2Pixel(m_nPos) - m_nThumbWidth/2,m_nMarginTop,m_nThumbWidth,m_nThumbHeight);

    }
    //画背景
    p.drawPixmap(m_nRect, m_nNormalChannelPic);
    p.drawPixmap(fillRect, m_nActiveChannelPic, fillRect);

    // 画滑块
    if(m_nFocus)
        p.drawPixmap(m_nThumbRect,m_nThumb_Active);
    else
        p.drawPixmap(m_nThumbRect,m_nThumb_Normal);
}


void PixmapSlider::mousePressEvent(QMouseEvent *event)       //单击实现
{
    if (event->button() == Qt::LeftButton && !m_bEnable)  //按下鼠标左键
    {
        m_flag_mousePress = true;

        if(m_nThumbRect.contains(event->pos()))
            m_flag_ThumbPress = true;

        if( m_bVertical ) {
            if( abs( event->pos().y() - Pos2Pixel( m_nMin + (m_nMax - m_nPos) ) ) <= m_nThumbHeight / 2 )
                m_nMouseOffset = event->pos().y() - Pos2Pixel( m_nMin + (m_nMax - m_nPos) );
            else
                m_nMouseOffset = 0;

        } else {
            if( abs( event->pos().x() - Pos2Pixel( m_nPos ) ) <= m_nThumbWidth / 2 )
                m_nMouseOffset = event->pos().x() - Pos2Pixel( m_nPos );
            else
                m_nMouseOffset = 0;
        }

        UpDataPressDown(event->pos());

//        if(m_BuddySpinFocus)
//        {
//            m_nFocus = true;
//            if(!m_nBuddySpin->hasFocus())
//                m_nBuddySpin->setFocus();
//        }else{
//            m_nFocus = true;
//            this->setFocus();
//        }
        emit sliderClicked();
    }
    QWidget::mousePressEvent(event);
}

void PixmapSlider::UpDataPressDown(QPoint point)
{
    if( !m_flag_mousePress)
        return;

    int nPixel;

    // Boundary check
    if( m_bVertical ) {

        nPixel = point.y() - m_nMouseOffset;

        if( nPixel > m_nRect.height() - m_nMarginBottom - m_nThumbHeight/2 )
            nPixel = m_nRect.height() - m_nMarginBottom - m_nThumbHeight/2;

        if( nPixel < m_nMarginTop + m_nThumbHeight/2 )
            nPixel = m_nMarginTop + m_nThumbHeight/2;

    } else {

        nPixel = point.x() - m_nMouseOffset;

        if( nPixel < m_nMarginLeft + m_nThumbWidth/2 )
            nPixel = m_nMarginLeft + m_nThumbWidth/2;

        if( nPixel > m_nRect.width() - m_nMarginRight - m_nThumbWidth/2 )
            nPixel = m_nRect.width() - m_nMarginRight - m_nThumbWidth/2;
    }
    // Apply change
    if(m_bVertical)
    {
        if( Pos2Pixel(m_nPos) != nPixel )
        {
            if(((m_nMin + (m_nMax - m_nPos))-Pixel2Pos(nPixel)) >0)
                SetPos(m_nPos+m_nStep,true);
            else
                SetPos(m_nPos-m_nStep,true);
        }
    }else{
        if( Pos2Pixel(m_nPos) != nPixel )
        {
            if((m_nPos-Pixel2Pos(nPixel)) >0)
                SetPos(m_nPos-m_nStep,true);
            else
                SetPos(m_nPos+m_nStep,true);
        }
    }
}

void PixmapSlider::mouseReleaseEvent(QMouseEvent *event)     //释放实现
{
    Q_UNUSED(event);

    m_flag_mousePress = false;
    m_flag_ThumbPress = false;

    QWidget::mouseReleaseEvent(event);
}

void PixmapSlider::focusOutEvent(QFocusEvent *e)
{
    Q_UNUSED(e);
    m_nFocus = false;
    update();
}

void PixmapSlider::mouseMoveEvent(QMouseEvent *event)     //移动实现
{
    if(m_flag_ThumbPress)
    {
        int nPixel;
        if( m_bVertical ) {

            nPixel = event->pos().y() - m_nMouseOffset;

            if( nPixel > m_nRect.height() - m_nMarginBottom - m_nThumbHeight/2 )
                nPixel = m_nRect.height() - m_nMarginBottom - m_nThumbHeight/2;

            if( nPixel < m_nMarginTop + m_nThumbHeight/2 )
                nPixel = m_nMarginTop + m_nThumbHeight/2;

        } else {

            nPixel = event->pos().x() - m_nMouseOffset;

            if( nPixel < m_nMarginLeft + m_nThumbWidth/2 )
                nPixel = m_nMarginLeft + m_nThumbWidth/2;

            if( nPixel > m_nRect.width() - m_nMarginRight - m_nThumbWidth/2 )
                nPixel = m_nRect.width() - m_nMarginRight - m_nThumbWidth/2;
        }

        // Apply change
        if(m_bVertical)
        {
            if(Pixel2Pos(m_nMin + (m_nMax - m_nPos)) <= 0)
                SetPos( m_nMin + (m_nMax - Pixel2Pos( nPixel )) ,true);

            if( Pos2Pixel(m_nMax - m_nPos) != nPixel )
                SetPos( m_nMin + (m_nMax - Pixel2Pos( nPixel )) ,true);

        }else{
            if(Pixel2Pos(m_nPos) <= 0)
                SetPos( Pixel2Pos( nPixel ) ,true);

            if( Pos2Pixel(m_nPos) != nPixel )
                SetPos( Pixel2Pos( nPixel ) ,true);
        }
    }
    QWidget::mouseMoveEvent(event);
}

int PixmapSlider::Pos2Pixel(int nPos)
{
    if( m_bVertical) {

        return
            m_nMarginTop + m_nThumbHeight/2 +
            (int)(
            ( m_nRect.height() - m_nMarginTop - m_nMarginBottom - m_nThumbHeight ) *
            ((double) ( nPos - m_nMin ) / ( m_nMax - m_nMin ) )
            );

    } else {

        return (int)(
            ( m_nRect.width() - m_nMarginLeft - m_nMarginRight - m_nThumbWidth ) *
            ((double) ( nPos - m_nMin ) / ( m_nMax - m_nMin ) )
            ) + m_nMarginLeft + m_nThumbWidth/2;
    }
}

int PixmapSlider::Pixel2Pos(int nPixel)
{
    if( m_bVertical) {

        return (int)(
            m_nMin +
            (double)( nPixel - m_nMarginTop - m_nThumbHeight/2) /
            ( m_nRect.height() - m_nMarginBottom - m_nMarginTop - m_nThumbHeight ) *
            ( m_nMax - m_nMin )
            );

    } else {
        return (int)(
            m_nMin +
            (double)( nPixel - m_nMarginLeft - m_nThumbWidth/2 ) /
            ( m_nRect.width() - m_nMarginLeft - m_nMarginRight - m_nThumbWidth ) *
            ( m_nMax - m_nMin )
            );
    }
}
