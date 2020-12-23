#ifndef TYPEDEF_H
#define TYPEDEF_H
#include<QImage>
struct IMAGE_INFO
{
    QImage  qImage;
    int     nAlgoID;//选择用哪种处理方法
    int     nDelta;//处理系数
};
#endif // TYPEDEF_H
