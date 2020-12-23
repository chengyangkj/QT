#include "imagewidget.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QGraphicsSceneDragDropEvent>
#include <QDrag>
#include <math.h>

ImageWidget::ImageWidget(QPixmap *pixmap)
{
    m_pix = *pixmap;
    setAcceptDrops(true);//If enabled is true, this item will accept hover events; otherwise, it will ignore them. By default, items do not accept hover events.
    m_scaleValue = 0;
    m_scaleDafault = 0;
    m_isMove = false;
//    setToolTip("Click and drag me!");  //提示
    setCursor(Qt::CrossCursor);   //改变光标形状
}

QRectF ImageWidget::boundingRect() const
{
    return QRectF(-m_pix.width() / 2, -m_pix.height() / 2,
                  m_pix.width(), m_pix.height());
}

void ImageWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                    QWidget *)
{
    painter->drawPixmap(-m_pix.width() / 2, -m_pix.height() / 2, m_pix);
}

void ImageWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()== Qt::LeftButton)
    {
        m_startPos = event->pos();//鼠标左击时，获取当前鼠标在图片中的坐标，
        m_isMove = true;//标记鼠标左键被按下
    }
    else if(event->button() == Qt::RightButton)
    {
        ResetItemPos();//右击鼠标重置大小
    }

}

void ImageWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_isMove)
    {
        QPointF point = (event->pos() - m_startPos)*m_scaleValue;
        moveBy(point.x(), point.y());
    }
}

void ImageWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    m_isMove = false;//标记鼠标左键已经抬起
}


void ImageWidget::wheelEvent(QGraphicsSceneWheelEvent *event)//鼠标滚轮事件
{
    if((event->delta() > 0)&&(m_scaleValue >= 50))//最大放大到原始图像的50倍
    {
        return;
    }
    else if((event->delta() < 0)&&(m_scaleValue <= m_scaleDafault))//图像缩小到自适应大小之后就不继续缩小
    {
        ResetItemPos();//重置图片大小和位置，使之自适应控件窗口大小
    }
    else
    {
        qreal qrealOriginScale = m_scaleValue;
        if(event->delta() > 0)//鼠标滚轮向前滚动
        {
            m_scaleValue*=1.1;//每次放大10%
        }
        else
        {
            m_scaleValue*=0.9;//每次缩小10%
        }
        setScale(m_scaleValue);
        if(event->delta() > 0)
        {
            moveBy(-event->pos().x()*qrealOriginScale*0.1, -event->pos().y()*qrealOriginScale*0.1);//使图片缩放的效果看起来像是以鼠标所在点为中心进行缩放的
        }
        else
        {
            moveBy(event->pos().x()*qrealOriginScale*0.1, event->pos().y()*qrealOriginScale*0.1);//使图片缩放的效果看起来像是以鼠标所在点为中心进行缩放的
        }
    }
    int nImgWidth = m_pix.width();
    int nImgHeight = m_pix.height();
    QPointF moustPoint;
    moustPoint.setX(event->pos().x()+nImgWidth*1.0/2);
    moustPoint.setY(event->pos().y()+nImgHeight*1.0/2);
    //QPoint pt = moustPoint.toPoint();
    QPoint pt;
    pt.setX(int(moustPoint.x()));
    pt.setY(int(moustPoint.y()));
    QColor qColor = m_pix.toImage().pixelColor(pt);
    emit showPos(moustPoint,qColor,m_scaleValue);
    emit mouseWheelSig(m_scaleValue);

}

void ImageWidget::setQGraphicsViewWH(int nwidth, int nheight)//将主界面的控件QGraphicsView的width和height传进本类中，并根据图像的长宽和控件的长宽的比例来使图片缩放到适合控件的大小
{
    int nImgWidth = m_pix.width();
    int nImgHeight = m_pix.height();
    qreal temp1 = nwidth*1.0/nImgWidth;
    qreal temp2 = nheight*1.0/nImgHeight;
    if(temp1>temp2)
    {
        m_scaleDafault = temp2;
    }
    else
    {
        m_scaleDafault = temp1;
    }
    setScale(m_scaleDafault);
    m_scaleValue = m_scaleDafault;
}

void ImageWidget::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    int nImgWidth = m_pix.width();
    int nImgHeight = m_pix.height();
    QPointF moustPoint;
    moustPoint.setX(event->pos().x()+nImgWidth*1.0/2);
    moustPoint.setY(event->pos().y()+nImgHeight*1.0/2);
    //QPoint pt = moustPoint.toPoint();
    QPoint pt;
    pt.setX(int(moustPoint.x()));
    pt.setY(int(moustPoint.y()));
    QColor qColor = m_pix.toImage().pixelColor(pt);
    emit showPos(moustPoint,qColor,m_scaleValue);
}

QPixmap ImageWidget::getImgFromRect(QRectF rectf)//rectf是外界传进来的以QGraphicsScene为坐标基准的矩形区域（即界面上看到的图片显示区域的正中央为（0,0）点）
{
    qreal nwidthOffset = pos().x();//pos()为当前m_pic图片正中央相对于显示控件的正中央（0,0）点偏移的位置
    qreal nheightOffset = pos().y();
    QRectF temprectf = QRectF(rectf.x()/m_scaleValue+m_pix.width()/2-nwidthOffset/m_scaleValue,rectf.y()/m_scaleValue+m_pix.height()/2-nheightOffset/m_scaleValue,rectf.width()/m_scaleValue,rectf.height()/m_scaleValue);
    //temprectf是将rectf转换为当前m_pic图片中的对应位置区域
    QPixmap retPixmap = m_pix.copy(temprectf.toRect());//拷贝m_pic图片中的对应区域
    return retPixmap;
}

void ImageWidget::ResetItemPos()//重置图片位置
{
    m_scaleValue = m_scaleDafault;//缩放比例回到一开始的自适应比例
    setScale(m_scaleDafault);//缩放到一开始的自适应大小
    setPos(0,0);
    emit mouseWheelSig(m_scaleValue);
}

qreal ImageWidget::getScaleValue() const
{
    return m_scaleValue;
}
