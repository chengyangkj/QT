#ifndef MYGRAPHICRECTITEM_H
#define MYGRAPHICRECTITEM_H
#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QRect>
#include <QPainter>
enum STATE_FLAG{
    DEFAULT_FLAG=0,
    MOV_LEFT_LINE,//标记当前为用户按下矩形的左边界区域
    MOV_TOP_LINE,//标记当前为用户按下矩形的上边界区域
    MOV_RIGHT_LINE,//标记当前为用户按下矩形的右边界区域
    MOV_BOTTOM_LINE,//标记当前为用户按下矩形的下边界区域
    MOV_RIGHTBOTTOM_RECT,//标记当前为用户按下矩形的右下角
    MOV_RECT//标记当前为鼠标拖动图片移动状态
};
class myGraphicRectItem:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    myGraphicRectItem(QGraphicsItem *parent = nullptr);
    //myGraphicRectItem(QRectF m_OriginRect = QRectF(0,0,100,100));
    QRectF  boundingRect() const;
    ~myGraphicRectItem();
    void setRectSize(QRectF mrect);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QRectF getCrtPosRectToSceen();
private:
    QRectF  m_oldRect;
    bool    m_bResize;
    QRectF  m_insicedRectf;
    QRectF  m_leftRectf;
    QRectF  m_topRectf;
    QRectF  m_rightRectf;
    QRectF  m_bottomRectf;
    QRectF  m_rbRectf;
    QPointF m_startPos;
    STATE_FLAG m_StateFlag;
protected:

};

#endif // MYGRAPHICRECTITEM_H
