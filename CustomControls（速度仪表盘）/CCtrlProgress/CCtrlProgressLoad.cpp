#include "CCtrlProgressLoad.h"
#include <QPainter>

CCtrlProgressLoad::CCtrlProgressLoad(QWidget *parent,DIS_TYPE disType) :
    QWidget(parent),
    m_DisType(disType),
    m_Angle(0),
    m_Delay(40),
    m_SizePara(0.7),
    m_DisplayedWhenStopped(false),
    m_Color(Qt::black),
    m_Label(NULL),
    m_Timer(NULL)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFocusPolicy(Qt::NoFocus);

    if(ELLIPSE == m_DisType)
    {
        m_Label = new QLabel(this);
        m_Label->setObjectName("m_label");
    }
    m_Timer = new QTimer();
    m_Timer->setSingleShot(false);
    connect(m_Timer,SIGNAL(timeout()),this,SLOT(slot_TimeOut()));
}

void CCtrlProgressLoad::startAnimation()
{
    if(!m_Timer->isActive()){
        m_Angle=0;
        m_Timer->start(m_Delay);
    }
}

void CCtrlProgressLoad::stopAnimation()
{
    if(m_Timer->isActive()){
        m_Timer->stop();
        update();
    }
}
void CCtrlProgressLoad::setProgress(int progress)
{
    m_Label->setText(QString("%1%").arg(progress));
}
void CCtrlProgressLoad::slot_TimeOut()
{
    m_Angle = (m_Angle+30)%360;
    update();
}
void CCtrlProgressLoad::resizeEvent(QResizeEvent * )
{
    if(ELLIPSE == m_DisType)
    {
        int width = qMin(this->width(),this->height())/2;
        m_Label->setStyleSheet(QString("QLabel#m_label{color:rgb(161,161,164);font: %1pt \"Andalus\";}").arg(width/4));
        m_Label->setFixedSize(width*m_SizePara,width*m_SizePara);
        m_Label->move(this->width()/2-width*.30,this->height()/2-width*.30);
    }
}

void CCtrlProgressLoad::paintEvent(QPaintEvent * /*event*/)
{
    if (!m_DisplayedWhenStopped && !isAnimated())
        return;
    QPainter p(this);
    qreal width = qMin(this->width()/2, this->height()/2);

    p.setRenderHint(QPainter::Antialiasing);
    if(ROUNDED == m_DisType)
    {
        qreal outerRadius = (width-1)*m_SizePara;
        qreal innerRadius = (width-1)*m_SizePara*0.38;

        qreal capsuleHeight = outerRadius - innerRadius;
        qreal capsuleWidth  = (width > 32 ) ? capsuleHeight *.23 : capsuleHeight *.35;
        qreal capsuleRadius = capsuleWidth/2;

        for (int i=0; i<12; i++)
        {
            QColor color = m_Color;
            color.setAlphaF(1.0f - (i/12.0f));
            p.setPen(Qt::NoPen);

            p.setBrush(color);
            p.save();
            p.translate(rect().center());
            p.rotate(m_Angle - i*30.0f);
            p.drawRoundedRect(-capsuleWidth*0.5, -(innerRadius+capsuleHeight), capsuleWidth, capsuleHeight, capsuleRadius, capsuleRadius);
            p.restore();
        }
    }
    else
    {
        qreal outerRadius = (width-1)*m_SizePara;
        qreal innerRadius = (width-1)*m_SizePara*0.80;
        qreal capsuleHeight = outerRadius - innerRadius;
        qreal capsuleWidth  = capsuleHeight;

        int red=0;
        int green=0;
        int blue=0;
        for (int i=0; i<12; i++)
        {
            QColor color(red,green,blue);
            red+=20;
            green+=20;
            blue+=20;

            color.setAlphaF(1.0f - (i/12.0f));
            p.setPen(Qt::NoPen);

            p.setBrush(color);
            p.save();
            p.translate(rect().center());
            p.rotate(m_Angle - i*30.0f);
            p.drawEllipse(-capsuleWidth, -(innerRadius+capsuleHeight), capsuleWidth, capsuleHeight);
            p.restore();
        }
    }
}
