#ifndef CCTRLDISPLAYDIALOG_H
#define CCTRLDISPLAYDIALOG_H

#include <QDialog>

namespace Ui {
class CCtrlDisplayDialog;
}
class CCtrlProgressLoad;
class CCtrlDashBoard;
class CCtrlProgressWater;
class CCtrlDisplayDialog : public QDialog
{
    Q_OBJECT

public:
    enum DisplayType {
        DPT_PROGLOAD=0,
        DPT_DASHBOARD,
        DPT_DASHBOARDARC,
        DPT_PROGRESSWATER
    };
    explicit CCtrlDisplayDialog(QWidget *parent = 0,DisplayType disType=DPT_PROGLOAD);
    ~CCtrlDisplayDialog();
public slots:
    void slot_SliderValue(int value);
protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::CCtrlDisplayDialog *ui;
    DisplayType        m_DisType;
    CCtrlProgressLoad  *m_ProgLoad;
    CCtrlDashBoard     *m_DashBoard;
    CCtrlProgressWater *m_ProgWater;
};

#endif // CCTRLDISPLAYDIALOG_H
