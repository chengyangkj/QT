#include "mygraphicrectitem.h"

myGraphicRectItem::myGraphicRectItem(QGraphicsItem *parent):
    m_bResize(false),
    m_oldRect(QRectF(0,0,100,100)),
    m_StateFlag(DEFAULT_FLAG)
{
    m_insicedRectf = QRectF(m_oldRect.x()+4,m_oldRect.y()+4,m_oldRect.width()-8,m_oldRect.height()-8);
    m_leftRectf = QRectF(m_oldRect.x(),m_oldRect.y(),4,m_oldRect.height()-4);
    m_topRectf = QRectF(m_oldRect.x()+4,m_oldRect.y(),m_oldRect.width()-4,4);
    m_rightRectf = QRectF(m_oldRect.right()-4,m_oldRect.y()+4,4,m_oldRect.height()-8);
    m_bottomRectf = QRectF(m_oldRect.x(),m_oldRect.bottom()-4,m_oldRect.width()-4,4);
    m_rbRectf = QRectF(m_oldRect.right()-4,m_oldRect.bottom()-4,4,4);
    setToolTip("Click and drag me!");  //提示
    setCursor(Qt::ArrowCursor);   //改变光标形状,手的形状
    setFlag(QGraphicsItem::ItemIsMovable);
    //    setAcceptDrops(true);
}

QRectF myGraphicRectItem::boundingRect() const
{
    return QRectF(m_oldRect);
}

myGraphicRectItem::~myGraphicRectItem()
{

}

void myGraphicRectItem::setRectSize(QRectF mrect)
{
        m_oldRect = mrect;
        m_insicedRectf = QRectF(m_oldRect.x()+4,m_oldRect.y()+4,m_oldRect.width()-8,m_oldRect.height()-8);
        m_leftRectf = QRectF(m_oldRect.x(),m_oldRect.y(),4,m_oldRect.height()-4);
        m_topRectf = QRectF(m_oldRect.x()+4,m_oldRect.y(),m_oldRect.width()-4,4);
        m_rightRectf = QRectF(m_oldRect.right()-4,m_oldRect.y()+4,4,m_oldRect.height()-8);
        m_bottomRectf = QRectF(m_oldRect.x(),m_oldRect.bottom()-4,m_oldRect.width()-4,4);
        m_rbRectf = QRectF(m_oldRect.right()-4,m_oldRect.bottom()-4,4,4);
}

void myGraphicRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen mPen = QPen(Qt::yellow);
    painter->setPen(mPen);
    painter->drawRect(m_oldRect);
}

void myGraphicRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()== Qt::LeftButton)
    {
        m_startPos = event->pos();//鼠标左击时，获取当前鼠标在图片中的坐标，
        if(m_insicedRectf.contains(m_startPos))//在矩形内框区域时按下鼠标，则可拖动图片
        {
            setCursor(Qt::ArrowCursor);   //改变光标形状,手的形状
            m_StateFlag = MOV_RECT;//标记当前为鼠标拖动图片移动状态
        }
        else if(m_leftRectf.contains(m_startPos))
        {
            setCursor(Qt::SizeHorCursor);
            m_StateFlag = MOV_LEFT_LINE;//标记当前为用户按下矩形的左边界区域
        }
        else if(m_rightRectf.contains(m_startPos))
        {
            setCursor(Qt::SizeHorCursor);
            m_StateFlag = MOV_RIGHT_LINE;//标记当前为用户按下矩形的右边界区域
        }
        else if(m_topRectf.contains(m_startPos))
        {
            setCursor(Qt::SizeVerCursor);
            m_StateFlag = MOV_TOP_LINE;//标记当前为用户按下矩形的上边界区域
        }
        else if(m_bottomRectf.contains(m_startPos))
        {
            setCursor(Qt::SizeVerCursor);
            m_StateFlag = MOV_BOTTOM_LINE;//标记当前为用户按下矩形的下边界区域
        }
        else if(m_rbRectf.contains(m_startPos))
        {
            setCursor(Qt::SizeFDiagCursor);
            m_StateFlag = MOV_RIGHTBOTTOM_RECT;//标记当前为用户按下矩形的右下角
        }
    }
    else
    {
        QGraphicsItem::mousePressEvent(event);
    }
}

void myGraphicRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_StateFlag == MOV_RECT)
    {
        QPointF point = (event->pos() - m_startPos);
        moveBy(point.x(), point.y());
    }
    else if(m_StateFlag == MOV_LEFT_LINE)
    {
        if(event->pos().x()>(m_oldRect.right()-10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setLeft(event->pos().x());
            setRectSize(newRect);
            scene()->update();//必须要用scene()->update()，不能用update();否则会出现重影
        }
    }
    else if(m_StateFlag == MOV_TOP_LINE)
    {
        if(event->pos().y()>(m_oldRect.bottom()-10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setTop(event->pos().y());
            setRectSize(newRect);
            scene()->update();//必须要用scene()->update()，不能用update();否则会出现重影
        }
    }
    else if(m_StateFlag == MOV_RIGHT_LINE)
    {
        if(event->pos().x()<(m_oldRect.left()+10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setRight(event->pos().x());
            setRectSize(newRect);
            scene()->update();//必须要用scene()->update()，不能用update();否则会出现重影
        }
    }
    else if(m_StateFlag == MOV_BOTTOM_LINE)
    {
        if(event->pos().y()<(m_oldRect.top()+10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setBottom(event->pos().y());
            setRectSize(newRect);
            scene()->update();//必须要用scene()->update()，不能用update();否则会出现重影
        }
    }
    else if(m_StateFlag == MOV_RIGHTBOTTOM_RECT)
    {
        if(event->pos().y()<(m_oldRect.top()+10))
        {
            return;
        }
        else if(event->pos().x()<(m_oldRect.left()+10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setBottomRight(event->pos());
            setRectSize(newRect);
            scene()->update();//必须要用scene()->update()，不能用update();否则会出现重影
        }
    }
    else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void myGraphicRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    if(m_StateFlag == MOV_RECT)
    {
        m_StateFlag = DEFAULT_FLAG;
    }
    else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

QRectF myGraphicRectItem::getCrtPosRectToSceen()
{
    QRectF retRect = QRectF(m_oldRect.x()+pos().x(),m_oldRect.y()+pos().y(),m_oldRect.width(),m_oldRect.height());
    return retRect;
}
