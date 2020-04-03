#include "CCtrlProgressWater.h"
#include <QPainter>
#include <qmath.h>

CCtrlProgressWater::CCtrlProgressWater(QWidget *parent, PercentStyle style) :
    QWidget(parent),
    m_StyleType(style),
    m_Timer(NULL)
{
    m_ProgValue=0;
    m_MinValue=0;
    m_MaxValue=100;

    m_StartAngle=0;
    m_WaterDensity = 2;
    m_WaterHeight  = 0.02;
    m_Offset       = 0;
    m_BorderWidth  = 10;
    m_BgColor = QColor(160,160,160);
    m_BorderColor = QColor(32,178,170);
    m_WaterColor    = QColor(135,206,250);
    m_Timer = new QTimer(this);
    connect(m_Timer, SIGNAL(timeout()),this,SLOT(slot_Timeout()));
    m_Timer->setSingleShot(false);
    m_Timer->start(100);
}

void CCtrlProgressWater::slot_Timeout(){
    m_Offset += 0.6;
    update();
}

void CCtrlProgressWater::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    qreal width = qMin((this->width()>>1), (this->height()>>1));

    p.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);

    drawBackGround(&p, width);
    drawValue(&p, width);
}

void CCtrlProgressWater::drawBackGround(QPainter *painter, qreal hlafWidth)
{
    int startX = 0;
    QPainterPath bigCircle;
    QPainterPath smallCircle;
    if (m_StyleType == PercentStyle_Rect) {
        bigCircle.addRoundRect(startX, startX, (hlafWidth*2), (hlafWidth*2),8);
        smallCircle.addRect(m_BorderWidth, m_BorderWidth, ((hlafWidth-m_BorderWidth)*2), ((hlafWidth-m_BorderWidth)*2));
    } else if (m_StyleType == PercentStyle_Circle) {
        bigCircle.addEllipse(startX, startX, (hlafWidth*2), (hlafWidth*2));
        smallCircle.addEllipse(m_BorderWidth, m_BorderWidth, ((hlafWidth-m_BorderWidth)*2), ((hlafWidth-m_BorderWidth)*2));
    } else if (m_StyleType == PercentStyle_Ellipse) {
        bigCircle.addEllipse(startX, startX, (hlafWidth*2), (hlafWidth*2));
        smallCircle.addEllipse(m_BorderWidth, m_BorderWidth, ((hlafWidth-m_BorderWidth)*2), ((hlafWidth-m_BorderWidth)*2));
    }
    QPainterPath path = bigCircle - smallCircle;

    painter->save();
    painter->setPen(m_BorderColor);
    painter->setBrush(m_BorderColor);
    painter->drawPath(path);
    painter->restore();

    painter->save();
    painter->setBrush(m_BgColor);
    if (m_StyleType == PercentStyle_Rect) {
        painter->drawRect(m_BorderWidth, m_BorderWidth, ((hlafWidth-m_BorderWidth)*2), ((hlafWidth-m_BorderWidth)*2));
    } else if (m_StyleType == PercentStyle_Circle) {
        painter->drawEllipse(m_BorderWidth, m_BorderWidth, ((hlafWidth-m_BorderWidth)*2), ((hlafWidth-m_BorderWidth)*2));
    } else if (m_StyleType == PercentStyle_Ellipse) {
        painter->drawEllipse(m_BorderWidth, m_BorderWidth, ((hlafWidth-m_BorderWidth)*2), ((hlafWidth-m_BorderWidth)*2));
    }
    painter->restore();
}

void CCtrlProgressWater::drawEllipseValue(QPainter *painter, qreal hlafWidth)
{

    qreal degRotate=0.1;
    if(m_ProgValue>0){
        qreal angleStep = 1.0*(360.0-m_StartAngle) / 100; //每一个份数的角度
        degRotate = angleStep*100*(m_ProgValue/100.0)+angleStep;
    }

    int startX = hlafWidth;
    QRectF rect(-startX, -startX, hlafWidth*2, hlafWidth*2);
    QPainterPath path;
    path.arcTo(rect, 360-m_StartAngle, -degRotate);

    // QRectF(-120, -120, 240, 240)
    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(10, 10, -10, -10));

    // path为扇形 subPath为椭圆
    path -= subPath;
    painter->save();
    painter->translate(hlafWidth,hlafWidth);
    painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
    painter->restore();
}
#define M_PI 3.14
void CCtrlProgressWater::drawValue(QPainter* painter, qreal hlafWidth)
{
    int height = hlafWidth*2;
    int width = hlafWidth*2;
    int side = hlafWidth*2;//qMin(width, height);
    //起始点坐标和结束点坐标
    int startX = m_BorderWidth;
    int startY = m_BorderWidth;
    int endX = width - m_BorderWidth;
    int endY = height - m_BorderWidth;
    //圆形的区域要重新计算
    if (m_StyleType == PercentStyle_Circle) {
        side = side - m_BorderWidth * 2;
        startX = (width - side) / 2;
        startY = (height - side) / 2;
        endX = (width + side) / 2;
        endY = (height + side) / 2;
    }
    //计算当前值所占百分比
    double percent = 1 - (double)(m_ProgValue - m_MinValue) / (m_MaxValue - m_MinValue);
    //正弦曲线公式 y = A * sin(ωx + φ) + k
    //w表示周期,可以理解为水波的密度,值越大密度越大(浪越密集 ^_^),取值 密度*M_PI/宽度
    double w = m_WaterDensity * M_PI / endX;
    //A表示振幅,可以理解为水波的高度,值越大高度越高(越浪 ^_^),取值高度的百分比
    double A = endY * m_WaterHeight;
    //k表示y轴偏移,可以理解为进度,取值高度的进度百分比
    double k = endY * percent;
    //圆形的区域要重新计算
    if (m_StyleType == PercentStyle_Circle) {
        k = (side * percent) + startY;
    }
    //第一条波浪路径集合
    QPainterPath waterPath1;
    //第二条波浪路径集合
    QPainterPath waterPath2;
    //移动到左上角起始点
    waterPath1.moveTo(startX, endY);
    waterPath2.moveTo(startX, endY);
    m_Offset += 0.6;
    if (m_Offset > (endX / 2)) {
        m_Offset = 0;
    }
    for(int x = startX; x <= endX; x++) {
        //第一条波浪Y轴
        double waterY1 = (double)(A * qSin(w * x + m_Offset)) + k;
        //第二条波浪Y轴
        double waterY2 = (double)(A * qSin(w * x + m_Offset + (endX / 2 * w))) + k;
        //如果当前值为最小值则Y轴为右下角Y轴
        if (m_ProgValue == m_MinValue) {
            waterY1 = endY;
            waterY2 = endY;
        }
        //如果当前值为最大值则Y轴为右上角Y轴
        if (m_ProgValue == m_MaxValue) {
            waterY1 = startY;
            waterY2 = startY;
        }
        //将两个点连接成线
        waterPath1.lineTo(x, waterY1);
        waterPath2.lineTo(x, waterY2);
    }
    //移动到右下角结束点,整体形成一个闭合路径
    waterPath1.lineTo(endX, endY);
    waterPath2.lineTo(endX, endY);
    //大路径
    QPainterPath bigPath;
    if (m_StyleType == PercentStyle_Rect) {
        bigPath.addRect(startX, startY, endX, endY);
    } else if (m_StyleType == PercentStyle_Circle) {
        bigPath.addEllipse(startX, startY, side, side);
    } else if (m_StyleType == PercentStyle_Ellipse) {
        drawEllipseValue(painter, hlafWidth);
        bigPath.addEllipse(startX, startY, width - m_BorderWidth * 2, height - m_BorderWidth * 2);
    }
    //新路径,用大路径减去波浪区域的路径,形成遮罩效果
    QPainterPath path;
    QColor waterColor1 = m_WaterColor;
    waterColor1.setAlpha(100);
    QColor waterColor2 = m_WaterColor;
    waterColor2.setAlpha(200);
    painter->save();
    painter->setPen(Qt::NoPen);
    //第一条波浪挖去后的路径
    path = bigPath.intersected(waterPath1);
    painter->setBrush(waterColor1);
    painter->drawPath(path);
    //第二条波浪挖去后的路径
    path = bigPath.intersected(waterPath2);
    painter->setBrush(waterColor2);
    painter->drawPath(path);
    painter->restore();
}
