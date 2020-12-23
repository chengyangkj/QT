#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configfilemanager.h"
struct Login {
    QString userName;
    QString password;
    Login():userName(""),password("")
    {

    }
    Login(QString name,QString pwd):userName(""),password("")
    {
        userName = name;
        password = pwd;
    }
};
//struct ttest
//{
//    short    st[1024*1024];
//    short    st2[1024*1024*1024];
//};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Image(nullptr),
    m_nCrtIndex(0),
    m_nCrtAlgoID(1),
    m_myGraphicRectItem(nullptr)
{
    ui->setupUi(this);
    ConfigFileManager cfg;
    bool bret = cfg.ParseConfigFile();//解析配置文件
    cfg.SaveConfigFile();//保存配置文件
    QObject::connect(&m_processThread,&ProcessorThread::ShowPicInDebugDlg,this,&MainWindow::recvShowPicSignal);
    m_processThread.start();
    //读取ini文件：
    QString     wstrFilePath;
    #if defined(Q_OS_LINUX)
        wstrFilePath = qApp->applicationDirPath() + "/../EditPic/editpic.ini" ;//in linux
    #else
        wstrFilePath = qApp->applicationDirPath() + "/../../EditPic/editpic.ini" ;//in windows，我的工程名为EditPic，二editpic.ini放在工程源文件目录下
    #endif
    QSettings *settings=new QSettings(wstrFilePath,QSettings::IniFormat);//用QSetting获取ini文件中的数据
    settings->clear();//清空settings中的数据
    QMap<qint32,QString>    m_mapProjectNames;
    m_mapProjectNames.insert(1,"6.01FH167-DMR-A-V06");
    m_mapProjectNames.insert(2,"7.01FH167-DMR-A-V06");
    m_mapProjectNames.insert(3,"8.01FH167-DMR-A-V06");
    //写ProjectNames
    settings->beginWriteArray("ProjectNames");
    for(int i = 0;i<m_mapProjectNames.size();i++)
    {
        settings->setArrayIndex(i);
        settings->setValue("ProjectName",m_mapProjectNames.value(i+1));
    }
    settings->endArray();
    settings->setValue("ProjectNames/CrtProjectID","1");
    //delete settings;该行在非调试模式运行时会导致程序crash！！！！！！！！！！！！！！
    //读ProjectNames
     QMap<qint32,QString>    m_mapReadProjectNames;
     QSettings *settings2 = new QSettings(wstrFilePath,QSettings::IniFormat);
     int nsize = settings2->beginReadArray("ProjectNames");
     for(int i = 0;i<nsize;i++)
     {
         settings2->setArrayIndex(i);
         m_mapReadProjectNames.insert(i+1,settings2->value("ProjectName").toString());
     }
     settings2->endArray();

    //将从editpic.ini读取到的ProjectNames节点的值写到editpic2.ini文件中
    wstrFilePath = qApp->applicationDirPath() + "/../../EditPic/editpic2.ini" ;//in windows
    QSettings *settings3 = new QSettings(wstrFilePath,QSettings::IniFormat);
    settings3->clear();
    settings3->beginWriteArray("ProjectNames");
    for (int i = 0; i < m_mapReadProjectNames.size(); i++) {
        settings3->setArrayIndex(i);
        settings3->setValue("ProjectName",m_mapReadProjectNames.value(i+1));
    }
    settings3->endArray();
    //settings3->remove("ProjectNames");
//    settings2->setValue("global/name","editpic2.ini");//通过普通的方式将global节点下name键的值设置为"editpic2.ini"


//以二进制形式读取配置文件：
//    QString     wstrFilePath;
//#if defined(Q_OS_LINUX)
//    wstrFilePath = qApp->applicationDirPath() + "/../Tx2Oled/2_CAL_G.dat" ;//in linux
//#else
//    wstrFilePath = qApp->applicationDirPath() + "/../../EditPic/2_CAL_G.dat" ;//in windows
//#endif
//    QFile file(wstrFilePath);
//    if(!file.open(QIODevice::ReadOnly))
//    {
//        qDebug()<<"open 2_CAL_G.dat failed!";
//    }
//    QByteArray t = file.readAll();
//    file.close();
//    unsigned short *usData = new unsigned short[t.size()/2];
//    memcpy((char*)usData, (char*)t.data(), t.size());
//    qint32 nNum = t.size();
//    nNum = sizeof(usData);
//    QStringList slist;
//    slist<<"hello"<<"R"<<"G"<<"B";
//    ui->comboBox->addItems(slist);
//    ui->comboBox->setCurrentText("B");
    m_MySpinBox = new mySpinbox;
    m_MySpinBox->setRange(0,1000);
    m_MySpinBox->setValue(100);
    ui->verticalLayout->addWidget(m_MySpinBox);

    //test mysysinfo class
    // MySysInfo mysysInfo;
    // double nCpuRate = 0;
    // mysysInfo.GetCpuUsage(nCpuRate);
    // double nMemTotal;
    // double nMemUsed;
    // mysysInfo.GetMemUsage(nMemTotal,nMemUsed);
    // unsigned long lFreeAll;
    // unsigned long lTotalAll;
    // mysysInfo.GetdiskSpace(lFreeAll,lTotalAll);

    m_qgraphicsScene = new QGraphicsScene;//要用QGraphicsView就必须要有QGraphicsScene搭配着用

}

MainWindow::~MainWindow()
{
    if(m_qgraphicsScene)
    {
        delete m_qgraphicsScene;
    }
    delete ui;
}

void MainWindow::recvShowPicSignal(QImage image)
{
    QPixmap ConvertPixmap=QPixmap::fromImage(image);//The QPixmap class is an off-screen image representation that can be used as a paint device
    m_qgraphicsScene->clear();
    m_myGraphicRectItem = nullptr;
    m_Image = new ImageWidget(&ConvertPixmap);//实例化类ImageWidget的对象m_Image，该类继承自QGraphicsItem，是自己写的类
    QObject::connect(m_Image,&ImageWidget::showPos,this,&MainWindow::showMousePos);
    QObject::connect(m_Image,&ImageWidget::mouseWheelSig,this,&MainWindow::recvGreViewMouseWheel);
    int nwith = ui->ImageGraphic->width();//获取界面控件Graphics View的宽度
    int nheight = ui->ImageGraphic->height();//获取界面控件Graphics View的高度
    m_Image->setQGraphicsViewWH(nwith,nheight);//将界面控件Graphics View的width和height传进类m_Image中
    m_Image->setAcceptHoverEvents(true);
    //test QGraphicsRectItem
    m_vPoint.clear();
    m_vPoint.push_back(QPointF(-500/2,-500/2));
    m_vPoint.push_back(QPointF(-500/2,500/2));
    m_vPoint.push_back(QPointF(500/2,-500/2));
    m_vPoint.push_back(QPointF(500/2,500/2));
    m_vPoint.push_back(QPointF(0,0));
    m_vQGRecItem.clear();
    QPen pen(Qt::red);//设置矩形标记的颜色
    pen.setWidth(5);//设置矩形标记的边宽度
    for(int i=0;i<m_vPoint.size();i++)
    {

        QGraphicsRectItem *pQGRectItem = new QGraphicsRectItem(m_vPoint[i].x()-20,m_vPoint[i].y()-20,40,40,m_Image);
        pQGRectItem->setPen(pen);
        m_vQGRecItem.push_back(pQGRectItem);
    }
    //test QGraphicsRectItem
    m_qgraphicsScene->addItem(m_Image);//将1QGraphicsItem类对象放进QGraphicsScene中
    for(int i=0;i<m_vQGRecItem.size();i++)
    {
        m_qgraphicsScene->addItem(m_vQGRecItem[i]);
    }
    ui->ImageGraphic->setSceneRect(QRectF(-(nwith/2),-(nheight/2),nwith,nheight));//使视窗的大小固定在原始大小，不会随图片的放大而放大（默认状态下图片放大的时候视窗两边会自动出现滚动条，并且视窗内的视野会变大），防止图片放大后重新缩小的时候视窗太大而不方便观察图片
    ui->ImageGraphic->setScene(m_qgraphicsScene);//Sets the current scene to scene. If scene is already being viewed, this function does nothing.
    ui->ImageGraphic->setFocus();//将界面的焦点设置到当前Graphics View控件
    ui->ImageGraphic->setMouseTracking(true);
}

void MainWindow::showMousePos(QPointF pointf, QColor qColor, qreal qrScale)
{
    QString sMousePos;
    sMousePos = QString("X:%1,Y:%2,GrayLevel:%3").arg(pointf.x()).arg(pointf.y()).arg(qColor.red());
    ui->ImageGraphic->setToolTip(sMousePos);
    //m_GraphicView->setWindowTitle(sMousePos);
    QString sScale = QString::number(qrScale*100, 'f', 2);
    sScale = "  Scaling : "+ sScale +"%";
    //QString sScale = QString("  Scaling : %1 %").arg(qrScale*100);
    ui->labelScaling->setText(sScale);

}

void MainWindow::recvGreViewMouseWheel(qreal qrScale)
{
    qreal tempScale = m_Image->m_scaleDafault/qrScale;
    for(int i=0;i<m_vQGRecItem.size();i++)
    {
        m_vQGRecItem[i]->setScale(tempScale);
        QRectF rect = m_vQGRecItem[i]->rect();
        m_vQGRecItem[i]->setRect(m_vPoint[i].x()/tempScale-20,m_vPoint[i].y()/tempScale-20,rect.width(),rect.height());
    }
}
void MainWindow::on_pushButton_open_clicked()
{
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->setWindowTitle("Choose Pictures");
    QStringList qstrFilters;
    qstrFilters<<"Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)";
    qstrFilters<<"Any files (*)";
    fileDlg->setNameFilters(qstrFilters);//设置文件过滤器
    fileDlg->setFileMode(QFileDialog::ExistingFiles);//设置能选择多个文件，如果是单个文件就写成QFileDialog::ExistingFile
    if(fileDlg->exec() == QDialog::Accepted)
    {
        QStringList strPathList = fileDlg->selectedFiles();
        if(!m_qlistLoadImgs.empty())
        {
            m_qlistLoadImgs.clear();
        }
        QPixmap pixmapTemp;
        for(int i = 0;i<strPathList.count();i++)//导入一张461kb图片后，该循环增加内存占用8972kb
        {
            pixmapTemp.load(strPathList[i]);
            m_qlistLoadImgs.push_back(pixmapTemp.toImage());
        }
        if(!ui->checkBox->isChecked())
        {
            if(!m_qlistLoadImgs.isEmpty())
            {
                m_nCrtIndex = 0;
                recvShowPicSignal(m_qlistLoadImgs.at(m_nCrtIndex));
            }
        }
        else
        {
            //test 测试导入16位深tiff灰度图，解析其数据，并进行归一化成8位深灰度图显示
            QVector<unsigned char> vdata;
            int nwidth = m_qlistLoadImgs.at(0).width();
            int nheight = m_qlistLoadImgs.at(0).height();
            vdata.resize(nwidth*nheight);
            memcpy((char*)&vdata[0],(char*)m_qlistLoadImgs[0].bits(),vdata.size()*sizeof(unsigned char));
            MY_TIFF myTIFF;
            m_MyTifLib.ParseTIFF(strPathList[0],myTIFF);
            int nRetWidth,nRetHeight;
            nRetWidth = myTIFF.tImgInfo.nWidth;
            nRetHeight = myTIFF.tImgInfo.nHeight;
            QImage imageFromAlgo(nRetWidth,nRetHeight,QImage::Format_Grayscale8);//The image is stored using 1-bit per pixel.
            unsigned char   *pRetImgData=imageFromAlgo.bits();
            if((myTIFF.tImgInfo.nDepth == 12)||(myTIFF.tImgInfo.nDepth == 16))
            {
                int nmax,nmin;
                nmax = myTIFF.vShortData.at(0);
                nmin = nmax;
                for(int i=0;i<(nRetWidth*nRetHeight-1);i++)
                {
                    if(nmax<myTIFF.vShortData.at(i+1))
                    {
                        nmax = myTIFF.vShortData.at(i+1);
                    }
                    if(nmin>myTIFF.vShortData.at(i+1))
                    {
                        nmin = myTIFF.vShortData.at(i+1);
                    }
                }
                for(int i=0;i<(nRetWidth*nRetHeight);i++)
                {
                    *(pRetImgData+i) = myTIFF.vShortData.at(i)*1.0f/(nmax-nmin)*255;//把16位深的数据归一化成8位深的数据
                }
            }
            else if(myTIFF.tImgInfo.nDepth == 8)
            {
                memcpy(pRetImgData,(char*)&myTIFF.vUcharData[0],nRetWidth*nRetHeight*sizeof(unsigned char));
            }
            recvShowPicSignal(imageFromAlgo);
            //memcpy(pRetImgData,m_tSolverMainData.sData4Display.ucpData4Display,nRetWidth*nRetHeight*sizeof(unsigned char));
            //test
        }


    }
    else
    {
        QMessageBox mesg;
        mesg.warning(this,"警告","打开图片失败!");
    }
    fileDlg->close();
    delete fileDlg;
    fileDlg = nullptr;
}

void MainWindow::on_pushButton_1cold_clicked()
{
    m_nCrtAlgoID = 1;
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_processThread.m_bStarted = false;
    m_processThread.wait();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)//每次slider滑动一格都会触发该函数
{
//    if(!m_qlistLoadImgs.empty())
//    {
//        IMAGE_INFO imageInfo;
//        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
//        imageInfo.nDelta = position;//ui->horizontalSlider->value();
//        imageInfo.nAlgoID = m_nCrtAlgoID;
//        m_processThread.InsertImg(imageInfo);
//    }
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::on_pushButton_2worm_clicked()//暖色调调节
{
    m_nCrtAlgoID = 2;
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::on_pushButton_3light_clicked()//亮度调节
{
    m_nCrtAlgoID = 3;
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::on_pushButton_4grey_clicked()
{
    m_nCrtAlgoID = 4;
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::on_pushButton_5saturation_clicked()
{
    m_nCrtAlgoID = 5;
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::on_pushButton_6blur_clicked()
{
    m_nCrtAlgoID = 6;
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::on_pushButton_7sharpen_clicked()
{
    m_nCrtAlgoID = 7;
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::on_pushButton_8frame_clicked()
{
    m_nCrtAlgoID = 8;
    if(!m_qlistLoadImgs.empty())
    {
        IMAGE_INFO imageInfo;
        imageInfo.qImage = m_qlistLoadImgs.at(m_nCrtIndex);
        imageInfo.nDelta = ui->horizontalSlider->value();
        imageInfo.nAlgoID = m_nCrtAlgoID;
        m_processThread.InsertImg(imageInfo);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog *fileDlg = new QFileDialog(this);
    fileDlg->setWindowTitle("Choose Pictures");
    QStringList qstrFilters;
    qstrFilters<<"Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm)";
    qstrFilters<<"Any files (*)";
    fileDlg->setNameFilters(qstrFilters);//设置文件过滤器
    fileDlg->setFileMode(QFileDialog::ExistingFile);//设置能选择多个文件，如果是单个文件就写成QFileDialog::ExistingFile
    if(fileDlg->exec() == QDialog::Accepted)
    {
        QStringList strPathList = fileDlg->selectedFiles();
        QFile file(strPathList.at(0));
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox mesg;
            mesg.warning(this,"警告","打开图片失败!");
        }
        QByteArray t = file.readAll();//读取文件中所有数据，存放到t中
        file.close();
        int nFileSize = t.size();
        int nNum = nFileSize%3;//数据按照每3个字节进行一次转换，此处计算循环的次数
        if(nNum!=0)
        {
            nNum = nFileSize/3+1;
        }
        else
        {
            nNum = nFileSize/3;
        }
        QVector<unsigned short> vShortData;
        for(int i=0;i<nNum;i++)//数据按照每3个字节进行一次转换
        {
            unsigned char c1,c2,c3;//从内存里读取到的3个字节数据
            unsigned char n8bit;//转换时候临时使用
            unsigned short n16bit;//转换时候临时使用
            unsigned short n1,n2;//转换后的数据
            memcpy((char*)&c1,(char*)(t.data()+3*i),1*sizeof(char));
            memcpy((char*)&c2,(char*)(t.data()+3*i+1),1*sizeof(char));
            //memcpy((char*)&c3,(char*)(t.data()+3*i+2),1*sizeof(char));
            //转换二进制数据中第一个字节
            n16bit = c1;
            n16bit = n16bit<<4;
            n1 = n16bit;
            //转换二进制数据中第二个字节的前4位
            n8bit = c2<<4;
            n8bit = n8bit>>4;
            n16bit = n8bit;
            n1 = n1+n16bit;
            //转换二进制数据中第二个字节的后4位和第三个字节
            memcpy((char*)&n2,(char*)(t.data()+3*i+1),2*sizeof(char));
            n2 = n2>>4;
            vShortData.append(n1);//将转换后的数据存到vShortData中
            vShortData.append(n2);
        }

        //start write file :
//        QByteArray ba;
//        ba.resize(vShortData.size()*2);
//        memcpy((char*)ba.data(),(char*)&vShortData[0],ba.size()*sizeof(char));//将之前的代码处理后得到的QVector<unsigned short>类型的变量vShortData中的数据拷贝到 QByteArray ba;中
//        QFile writefile("1.dat");//如果文件不存在，则创建该文件。路径在执行文件的上一级路径下。
//        writefile.open(QIODevice::ReadWrite);
//        QDataStream out(&writefile);
//        //一下为5中写文件的方式，有些会在文件开头出多写入4个字节表示长度，有些不会，需要仔细区分！
//        //out << ba;//这种方式会在生成的文件一开始多处4个字节，表示QDataStream的长度
//        //out.writeBytes(ba.data(),ba.size());//这种方式也会在文件头多出4个字节
//        //out.writeRawData(ba.data(),ba.size());//这种方式保存的数据为实际ba中的内容，不会有任何多余字节
//        //writefile.write(ba);//这种方式也不会有多余字节
//        writefile.write(ba.data(),ba.size());//这种方式也不会有多余字节
//        writefile.close();
        //test Translate16to12
        QVector<unsigned char> tc;
        Translate16to12(vShortData,tc);
    }
    else
    {
        QMessageBox mesg;
        mesg.warning(this,"警告","打开图片失败!");
    }
    fileDlg->close();
    delete fileDlg;
    fileDlg = nullptr;


}

void MainWindow::Translate16to12(QVector<unsigned short> &vData16,QVector<unsigned char> &vData12)
{
    if(vData16.isEmpty())
    {
        return;
    }
    int nNum12 = vData16.size()/2*3;
    vData12.resize(nNum12);
    int nCircleTime = vData16.size()/2;
    for (int i=0;i<nCircleTime;i++)
    {
        unsigned short n1,n2;//16位的数据
        unsigned char c1,c2,c3;//
        n1 = vData16.at(i*2);
        n2 = vData16.at(i*2+1);
        c1 = n1>>4;//获取c1的值

        n1 = n1<<12;
        n1 = n1>>12;

        c3 = n2>>4;//获取c3的值

        n2 = n2<<12;
        n2 = n2>>8;

        c2 = n2+n1;//获取c2的值
        memcpy((char*)&vData12[3*i],(char*)&c1,sizeof(char));
        memcpy((char*)&vData12[3*i+1],(char*)&c2,sizeof(char));
        memcpy((char*)&vData12[3*i+2],(char*)&c3,sizeof(char));
    }
    //start write file :把数据写到本地，便于与原来的12位深数据进行对比
        QByteArray ba;
        ba.resize(vData12.size());
        memcpy((char*)ba.data(),(char*)&vData12[0],ba.size()*sizeof(char));//将之前的代码处理后得到的QVector<unsigned short>类型的变量vShortData中的数据拷贝到 QByteArray ba;中
        QFile writefile("2.dat");//如果文件不存在，则创建该文件。路径在执行文件的上一级路径下。
        writefile.open(QIODevice::ReadWrite);
        QDataStream out(&writefile);
        writefile.write(ba.data(),ba.size());//这种方式也不会有多余字节
        writefile.close();
}

void MainWindow::on_pushButton__DrawRect_clicked()
{
    m_myGraphicRectItem = new myGraphicRectItem();//实例化myGraphicRectItem
    m_myGraphicRectItem->setRectSize(QRectF(-100,-100,200,200));//设置矩形大小，以m_qgraphicsScene的中心为原点，边长200的正方形
    m_qgraphicsScene->addItem(m_myGraphicRectItem);//将绘制的矩形添加到m_qgraphicsScene场景中
    m_qgraphicsScene->setFocusItem(m_myGraphicRectItem);
}

void MainWindow::on_pushButton_getpic_clicked()
{
    if(m_Image)
    {
        if(m_myGraphicRectItem)
        {
            QPixmap pix = m_Image->getImgFromRect(m_myGraphicRectItem->getCrtPosRectToSceen());
            //test save pic
            QString wstrFilePath = qApp->applicationDirPath() + "/savePic.png" ;
            pix.save(wstrFilePath,"PNG");
            //test save pic
        }
    }
}
