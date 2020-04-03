#include "dialog_ip.h"
#include "ui_dialog_ip.h"

Dialog_ip::Dialog_ip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ip)
{
    ui->setupUi(this);
}

Dialog_ip::~Dialog_ip()
{
    delete ui;
}
