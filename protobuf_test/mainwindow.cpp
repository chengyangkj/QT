#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    robot_data::RobotData dataGrame;
    //添加laser数据
    robot_data::LaserData *laser_data = dataGrame.mutable_laser_data();
    robot_data::Point *point;
    laser_data->set_location(-1);
    laser_data->set_timestamp(1001);
    for(int i=0;i<100;i++){
        point = laser_data->add_scan();
        point->set_x(0.5);
        point->set_y(1.6);
        point->set_theta(10);
    }

    //序列化
    std::string binary = dataGrame.SerializeAsString();
    QByteArray byte(binary.c_str(),binary.size());

    qDebug()<<"byte: "<<byte.toHex(' ');
    qDebug()<<"byte size:"<<byte.size()<<" "<<binary.size();

     robot_data::RobotData redataGrame;
    //反序列化
    if (false == redataGrame.ParseFromString(binary)) {
       qDebug()<<"反序列化失败！";
    }else{
        if(redataGrame.has_laser_data()){
            qDebug()<<"反序列化laser location:"<<redataGrame.mutable_laser_data()->location();
             qDebug()<<"反序列化laser timestamp:"<<redataGrame.mutable_laser_data()->timestamp();
             for(int i=0;i<redataGrame.mutable_laser_data()->scan_size();i++){
                 qDebug()<<redataGrame.mutable_laser_data()->scan(i).x()<<redataGrame.mutable_laser_data()->scan(i).y();
             }
        }else{
            qDebug()<<"无 laser data";
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
