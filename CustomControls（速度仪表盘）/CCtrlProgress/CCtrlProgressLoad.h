#ifndef CCTRLPROGRESSLOAD_H
#define CCTRLPROGRESSLOAD_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

class CCtrlProgressLoad : public QWidget
{
    Q_OBJECT
public:
    enum DIS_TYPE{
        ROUNDED,
        ELLIPSE
    };
    explicit CCtrlProgressLoad(QWidget *parent = nullptr,DIS_TYPE disType = ROUNDED);

    bool isAnimated () const {
        return m_Timer->isActive();
    }
    bool isDisplayedWhenStopped() const {
        return m_DisplayedWhenStopped;
    }

    void startAnimation();
    void stopAnimation();
    void setAnimationDelay(int delay){
        m_Delay=delay;
    }
    void setDisplayedWhenStopped(bool state){
        m_DisplayedWhenStopped = state;
        update();
    }
    void setColor(const QColor &color) {
        m_Color = color;
    }
    void setProgress(int progress);

    void setSizePara(qreal para) {
        m_SizePara = para;
    }
protected:
    virtual void paintEvent(QPaintEvent * event);
    virtual void resizeEvent(QResizeEvent * event);

public slots:
    void slot_TimeOut();
private:
    DIS_TYPE m_DisType;
    int      m_Angle;
    int      m_Delay;
    qreal    m_SizePara;
    bool     m_DisplayedWhenStopped;
    QColor   m_Color;
    QLabel   *m_Label;
    QTimer   *m_Timer;
};

#endif // CCTRLPROGRESSLOAD_H
