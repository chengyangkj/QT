#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QPixmap>
#include <QPainter>
#include <QRectF>
#include <QMouseEvent>
#include <QPointF>
#include <QDragEnterEvent>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsItem>

enum Enum_ZoomState{
    NO_STATE,
    RESET,
    ZOOM_IN,
    ZOOM_OUT
};
// class ImageWidget :public QObject, QGraphicsItem
class ImageWidget :public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    ImageWidget(QPixmap *pixmap);
    QRectF  boundingRect() const;
    void    paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void    wheelEvent(QGraphicsSceneWheelEvent *event);
    void    ResetItemPos();
    void    mousePressEvent(QGraphicsSceneMouseEvent *event);
    void    mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void    mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    qreal   getScaleValue() const;
    void    setQGraphicsViewWH(int nwidth,int nheight);
    void    hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    QPixmap getImgFromRect(QRectF rectf);
    qreal       m_scaleValue;
    qreal       m_scaleDafault;
signals:
    void    showPos(QPointF pointf,QColor qColor,qreal qrScale);
    void    mouseWheelSig(qreal qrScale);
private:
    QPixmap     m_pix;
    int         m_zoomState;
    bool        m_isMove;
    QPointF     m_startPos;

};
#endif // IMAGEWIDGET_H
