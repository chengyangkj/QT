#ifndef PROCESSORTHREAD_H
#define PROCESSORTHREAD_H
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QPainter>
#include <QCoreApplication>
#include <QDebug>
#include"typedef.h"
class ProcessorThread:public QThread
{
        Q_OBJECT
public:
    ProcessorThread();
    ~ProcessorThread();
    void        run();//声明继承于QThread虚函数 run()
    void        InsertImg(IMAGE_INFO &imgInfo);
    void        ProcessImg(IMAGE_INFO *imgInfo);
public:
    bool                m_bStarted;
    QList<IMAGE_INFO>   m_qlistImageInfo;
private:
    QImage      *AlgoCool(int delta, QImage * origin);
    QImage      *AlgoWarm(int delta, QImage * origin);
    QImage      *AlgoGreyScale(int delta,QImage * origin);
    QImage      *AlgoLight(int delta,QImage * origin);
    QImage      *AlgoSaturation(int delta, QImage * origin);
    QImage      *AlgoBlur(int delta,QImage * origin);
    QImage      *AlgoSharpen(int delta,QImage * origin);
    QImage      *AlgoDrawFrame(int delta,QImage * origin);
private:
    QMutex      m_qMutex;
signals:
    void        ShowPicInDebugDlg(QImage img);
};

#endif // PROCESSORTHREAD_H
