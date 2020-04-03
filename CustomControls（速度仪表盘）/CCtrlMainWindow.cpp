#include "CCtrlMainWindow.h"
#include "ui_CCtrlMainWindow.h"
#include "CCtrlDisplayDialog.h"
#include "CCtrlProgress/CCtrlDateEdit.h"
#include <QDebug>
CCtrlMainWindow::CCtrlMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CCtrlMainWindow)
{
    ui->setupUi(this);
    connect(ui->btn_ProgLoad,SIGNAL(clicked(bool)),this,SLOT(slot_ProgLoad()));
    connect(ui->btn_DashBoard,SIGNAL(clicked(bool)),this,SLOT(slot_DashBoard()));
    connect(ui->btn_DashBoard1,SIGNAL(clicked(bool)),this,SLOT(slot_DashBoardArc()));
    connect(ui->btn_ProgWater,SIGNAL(clicked(bool)),this,SLOT(slot_ProgressWater()));

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setNullable(true);
    ui->dateEdit->setDate(QDate());

    //QImage tImg("E:/dscTest/CustomControls/3c5805c5f0a310ae63f5acf5841dd205.png");

    QFile tfile("E:/dscTest/CustomControls/3c5805c5f0a310ae63f5acf5841dd205.png");
    QPixmap tPix;//("E:/dscTest/CustomControls/3c5805c5f0a310ae63f5acf5841dd205.png","jpg");
    //tPix.fromImage(tImg);
    if(tfile.open(QFile::ReadOnly)){
        tPix.loadFromData(tfile.readAll());
    }
    ui->label->setPixmap(tPix.scaled(95,95));
    //ui->label->update();

    //m_Timer = new QTimer(this);
    //connect(m_Timer,SIGNAL(timeout()),this,SLOT(slot_TimeOut()));
    //m_Timer->start(0);
}

CCtrlMainWindow::~CCtrlMainWindow()
{
    delete ui;
}

void CCtrlMainWindow::slot_TimeOut()
{
    //qInfo()<<"CCtrlMainWindow::slot_TimeOut";
}

void CCtrlMainWindow::slot_ProgLoad()
{
    CCtrlDisplayDialog dlg(this, CCtrlDisplayDialog::DPT_PROGLOAD);
    dlg.exec();
}

void CCtrlMainWindow::slot_DashBoard()
{
    CCtrlDisplayDialog dlg(this, CCtrlDisplayDialog::DPT_DASHBOARD);
    dlg.exec();
}

void CCtrlMainWindow::slot_DashBoardArc()
{
    CCtrlDisplayDialog dlg(this, CCtrlDisplayDialog::DPT_DASHBOARDARC);
    dlg.exec();
}

void CCtrlMainWindow::slot_ProgressWater()
{
    CCtrlDisplayDialog dlg(this, CCtrlDisplayDialog::DPT_PROGRESSWATER);
    dlg.exec();
}
