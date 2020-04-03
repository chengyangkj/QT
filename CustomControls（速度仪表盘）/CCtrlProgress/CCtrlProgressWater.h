#ifndef CCTRLPROGRESSWATER_H
#define CCTRLPROGRESSWATER_H

#include <QWidget>
#include <QTimer>
#include <QColor>

class CCtrlProgressWater : public QWidget
{
    Q_OBJECT
public:
    enum PercentStyle {
        PercentStyle_Rect=0,
        PercentStyle_Circle,
        PercentStyle_Ellipse
    };
    explicit CCtrlProgressWater(QWidget *parent = nullptr, PercentStyle style=PercentStyle_Ellipse);

    void setValue(int value){
        m_ProgValue = value;
        update();
    }
    void setWaterColor(QColor color){
        m_WaterColor=color;
        update();
    }
signals:

public slots:
    void slot_Timeout();
protected:
    void paintEvent(QPaintEvent* event);

private:
    void drawBackGround(QPainter *painter, qreal hlafWidth);
    void drawEllipseValue(QPainter *painter, qreal hlafWidth);
    void drawValue(QPainter* painter, qreal hlafWidth);
    int m_ProgValue;
    int m_StyleType;

    int     m_StartAngle;
    int     m_MinValue;
    int     m_MaxValue;
    int     m_WaterDensity;
    double  m_WaterHeight;
    double  m_Offset;
    int     m_BorderWidth;
    QColor  m_BgColor;
    QColor  m_BorderColor;
    QColor  m_WaterColor;
    QTimer  *m_Timer;
};

#endif // CCTRLPROGRESSWATER_H
