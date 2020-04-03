#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //treeWidget_rviz
    ui->treeWidget_rviz->setWindowTitle("Displays");
    ui->treeWidget_rviz->setWindowIcon(QIcon("://images/display.png"));
    //header 设置
    ui->treeWidget_rviz->setHeaderHidden(true);
    ui->treeWidget_rviz->setHeaderLabels(QStringList()<<"key"<<"value");

    //Global options
    QTreeWidgetItem *Global=new QTreeWidgetItem(QStringList()<<"Global Options");
    Global->setIcon(0,QIcon("://images/setting2.png"));

    QTreeWidgetItem* FixedFrame=new QTreeWidgetItem(QStringList()<<"Fixed Frame");
    Global->addChild(FixedFrame);

    ui->treeWidget_rviz->addTopLevelItem(Global);

    //添加combox控件
    QComboBox *frame=new QComboBox();
    frame->addItem("map");
    frame->setMaximumWidth(150);
    ui->treeWidget_rviz->setItemWidget(FixedFrame,1,frame);

    QTreeWidgetItem* bcolor=new QTreeWidgetItem(QStringList()<<"Background Color");
    Global->addChild(bcolor);
    //添加lineedit控件
    QLineEdit *colorval=new QLineEdit("255;255;255");
    colorval->setMaximumWidth(150);
    ui->treeWidget_rviz->setItemWidget(bcolor,1,colorval);

    QSpinBox *framerateval=new QSpinBox();
    framerateval->setMaximumWidth(150);
    framerateval->setRange(10,50);
    QTreeWidgetItem* framerate=new QTreeWidgetItem(QStringList()<<"Frame Rate");
    Global->addChild(framerate);
    ui->treeWidget_rviz->setItemWidget(framerate,1,framerateval);

    //grid
    QTreeWidgetItem *grid=new QTreeWidgetItem(QStringList()<<"Grid");
    grid->setIcon(0,QIcon("://images/grid.png"));

    ui->treeWidget_rviz->addTopLevelItem(grid);
    QCheckBox* gridcheck=new QCheckBox;
    ui->treeWidget_rviz->setItemWidget(grid,1,gridcheck);

    QTreeWidgetItem *gridstatus=new QTreeWidgetItem(QStringList()<<"Statue:");
    gridstatus->setIcon(0,QIcon("://images/ok.png"));
    grid->addChild(gridstatus);
    QLabel *gridstatusvalue=new QLabel("ok");
    gridstatusvalue->setMaximumWidth(150);
    ui->treeWidget_rviz->setItemWidget(gridstatus,1,gridstatusvalue);
}

MainWindow::~MainWindow()
{
    delete ui;
}
