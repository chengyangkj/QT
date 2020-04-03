#ifndef CCTRLMAINWINDOW_H
#define CCTRLMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class CCtrlMainWindow;
}

class CCtrlMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CCtrlMainWindow(QWidget *parent = 0);
    ~CCtrlMainWindow();
public slots:
    void slot_ProgLoad();
    void slot_DashBoard();
    void slot_DashBoardArc();
    void slot_ProgressWater();
    void slot_TimeOut();
private:
    Ui::CCtrlMainWindow *ui;
    QTimer *m_Timer;
};

#endif // CCTRLMAINWINDOW_H
