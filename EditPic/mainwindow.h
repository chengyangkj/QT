#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QList>
#include <QMessageBox>
#include <QImage>
#include <QGraphicsScene>
#include <QSettings>
#include <QMap>
#include "imagewidget.h"
#include "typedef.h"
#include "processorthread.h"
#include "mytiflib.h"
#include "myspinbox.h"
#include "mysysinfo.h"
#include "mygraphicrectitem.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void            recvShowPicSignal(QImage image);

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_1cold_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_sliderReleased();

    void on_pushButton_2worm_clicked();

    void on_pushButton_3light_clicked();

    void on_pushButton_4grey_clicked();

    void on_pushButton_5saturation_clicked();

    void on_pushButton_6blur_clicked();

    void on_pushButton_7sharpen_clicked();

    void on_pushButton_8frame_clicked();
    void showMousePos(QPointF pointf,QColor qColor,qreal qrScale);
    void recvGreViewMouseWheel(qreal qrScale);
    void on_pushButton_clicked();
    void on_pushButton__DrawRect_clicked();

    void on_pushButton_getpic_clicked();

public:
    void Translate16to12(QVector<unsigned short> &vData16,QVector<unsigned char> &vData12);
private:
    QGraphicsScene  *m_qgraphicsScene;
    ImageWidget     *m_Image;
    QVector<QGraphicsRectItem*> m_vQGRecItem;
//    QVector<QRect>    m_vRect;
    QVector<QPointF>  m_vPoint;
    Ui::MainWindow  *ui;
    QList<QImage>   m_qlistLoadImgs;
    qint32          m_nCrtIndex;
    qint32          m_nCrtAlgoID;
    ProcessorThread m_processThread;
    MyTifLib        m_MyTifLib;
    mySpinbox       *m_MySpinBox;
    myGraphicRectItem *m_myGraphicRectItem;
protected:
    void            closeEvent(QCloseEvent *event);
    int             add(int a,int b);
};

#endif // MAINWINDOW_H
