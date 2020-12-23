#ifndef MYSPINBOX_H
#define MYSPINBOX_H

#include <QWidget>
#include <QSpinBox>
#include <QDebug>
class mySpinbox : public QSpinBox
{
    Q_OBJECT
public:
    explicit mySpinbox(QWidget *parent = nullptr);
private:
    void    wheelEvent(QWheelEvent *event);
signals:

public slots:
};

#endif // MYSPINBOX_H
