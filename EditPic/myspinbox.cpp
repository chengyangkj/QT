#include "myspinbox.h"

mySpinbox::mySpinbox(QWidget *parent)
{
    if(parent==nullptr)
    {
        qDebug()<<"parent = nullptr";
    }
}

void mySpinbox::wheelEvent(QWheelEvent *event)
{
    return;
}
