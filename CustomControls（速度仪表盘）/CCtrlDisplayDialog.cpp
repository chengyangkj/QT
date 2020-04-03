#include "CCtrlDisplayDialog.h"
#include "ui_CCtrlDisplayDialog.h"
#include "CCtrlProgress/CCtrlProgressLoad.h"
#include "CCtrlProgress/CCtrlDashBoard.h"
#include "CCtrlProgress/CCtrlProgressWater.h"

#define DBG_MSG qWarning("[DBG_MSG] FILE : %s, FUNCTION : %s, LINE : %d",__FILE__,__FUNCTION__,__LINE__)
CCtrlDisplayDialog::CCtrlDisplayDialog(QWidget *parent,DisplayType disType) :
    QDialog(parent),
    ui(new Ui::CCtrlDisplayDialog),
    m_DisType(disType),
    m_ProgLoad(NULL),
    m_DashBoard(NULL),
    m_ProgWater(NULL)
{
    ui->setupUi(this);
DBG_MSG;
    switch(m_DisType)
    {
    case DPT_PROGLOAD:
        this->setWindowTitle("ProgressLoad");
        m_ProgLoad = new CCtrlProgressLoad(ui->content);//,CCtrlProgressLoad::ELLIPSE);
        m_ProgLoad->setGeometry(ui->content->rect());
        ui->sld_Value->hide();
        m_ProgLoad->startAnimation();
        break;
    case DPT_DASHBOARD:
        this->setWindowTitle("DashBoard");
        m_DashBoard =new CCtrlDashBoard(ui->content);
        m_DashBoard->setValue(10);
        ui->sld_Value->show();
        m_DashBoard->setGeometry(ui->content->rect());
        break;
    case DPT_DASHBOARDARC:
        this->setWindowTitle("DashBoardArc");
        m_DashBoard =new CCtrlDashBoard(ui->content,CCtrlDashBoard::ST_ARCBAR);
        ui->sld_Value->show();
        m_DashBoard->setGeometry(ui->content->rect());
        break;
    case DPT_PROGRESSWATER:
        m_ProgWater = new CCtrlProgressWater(ui->content);
        //m_ProgWater = new CCtrlProgressWater(ui->content,CCtrlProgressWater::PercentStyle_Rect);
        //m_ProgWater = new CCtrlProgressWater(ui->content,CCtrlProgressWater::PercentStyle_Circle);
        ui->sld_Value->show();
        m_ProgWater->setGeometry(ui->content->rect());
        break;
    }
    connect(ui->sld_Value,SIGNAL(valueChanged(int)),this,SLOT(slot_SliderValue(int)));
}

CCtrlDisplayDialog::~CCtrlDisplayDialog()
{
    delete ui;
}

void CCtrlDisplayDialog::resizeEvent(QResizeEvent * event)
{
    switch(m_DisType)
    {
    case DPT_PROGLOAD:
        m_ProgLoad->setGeometry(ui->content->rect());
        break;
    case DPT_DASHBOARD:
    case DPT_DASHBOARDARC:
        m_DashBoard->setGeometry(ui->content->rect());
        break;
    case DPT_PROGRESSWATER:
        m_ProgWater->setGeometry(ui->content->rect());
        break;
    }
}


void CCtrlDisplayDialog::slot_SliderValue(int value)
{
    switch(m_DisType)
    {
    case DPT_DASHBOARD:
    case DPT_DASHBOARDARC:
        m_DashBoard->setValue(value);
        break;
    case DPT_PROGRESSWATER:
        m_ProgWater->setValue(value);
        break;
    }
}
