#ifndef HANDLE_H
#define HANDLE_H

#include <QWidget>
#include <QPainter>
#include <QDrag>
#include <QMouseEvent>
#include <QtMath>
#include <QTimer>
#include <QDebug>
class Handle : public QWidget
{
    Q_OBJECT

public:
    Handle(QWidget *parent = 0);
    ~Handle();
    enum {upleft=0,up,upright,left,stop,right,downleft,down,downright};
signals:
    void keyNumchanged(int num);
protected:
    void paintEvent(QPaintEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
  //  void resizeEvent(QResizeEvent *event)override;
private:
    int mouseX;
    int mouseY;
  int handleX;//摇杆
  int handleY;
  int handleR;
  int padX;//底盘
  int padY;
  int padR;
  double handPadDis;//两圆圆心距离
  bool mousePressed;
  QTimer *tim;
private:
   double Pointdis(int a,int b,int x,int y);//两点距离
   int getKeyNum();

};

#endif // HANDLE_H
