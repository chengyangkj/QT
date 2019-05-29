#ifndef DIALOG_IP_H
#define DIALOG_IP_H

#include <QDialog>

namespace Ui {
class Dialog_ip;
}

class Dialog_ip : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ip(QWidget *parent = 0);
    ~Dialog_ip();

private:
    Ui::Dialog_ip *ui;
};

#endif // DIALOG_IP_H
