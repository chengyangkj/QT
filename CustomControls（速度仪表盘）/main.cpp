#include "CCtrlMainWindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb2312"));
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb2312"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));

    CCtrlMainWindow w;
    //QWidget w;
    w.show();

    return a.exec();
}
