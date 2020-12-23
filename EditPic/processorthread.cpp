#include "processorthread.h"

ProcessorThread::ProcessorThread():m_bStarted(true)
{

}

ProcessorThread::~ProcessorThread()
{

}

void ProcessorThread::run()
{

    while(m_bStarted)
    {
        m_qMutex.lock();
        if(!m_qlistImageInfo.isEmpty())
        {
            IMAGE_INFO imgInfo;
            imgInfo = m_qlistImageInfo.takeLast();
            m_qMutex.unlock();
            ProcessImg(&imgInfo);

            emit ShowPicInDebugDlg(imgInfo.qImage);
        }
        else
        {
            m_qMutex.unlock();
        }

        QThread::msleep(10);
    }
}

void ProcessorThread::InsertImg(IMAGE_INFO &imgInfo)
{
    m_qMutex.lock();
    m_qlistImageInfo.push_front(imgInfo);
    m_qMutex.unlock();
}

void ProcessorThread::ProcessImg(IMAGE_INFO *imgInfo)
{
    int n=0;
    unsigned char   *pData=imgInfo->qImage.bits();
    int             width=imgInfo->qImage.width();
    int             height=imgInfo->qImage.height();
    memcpy((char*)&n,(char*)pData+((11*width+1)*4),3);
    qDebug()<<"图片第(11,1)像素的亮度 = "<<n;
    QImage *qimg;
    if(imgInfo->nAlgoID == 0)
    {

    }
    else if(imgInfo->nAlgoID == 1)
    {
        qimg = AlgoCool(imgInfo->nDelta,&imgInfo->qImage);
        imgInfo->qImage = *qimg;
    }
    else if(imgInfo->nAlgoID == 2)
    {
        qimg = AlgoWarm(imgInfo->nDelta,&imgInfo->qImage);
        imgInfo->qImage = *qimg;
    }
    else if(imgInfo->nAlgoID == 3)
    {
        qimg = AlgoLight(imgInfo->nDelta,&imgInfo->qImage);
        imgInfo->qImage = *qimg;
    }
    else if(imgInfo->nAlgoID == 4)
    {
        qimg = AlgoGreyScale(imgInfo->nDelta,&imgInfo->qImage);
        imgInfo->qImage = *qimg;
    }
    else if(imgInfo->nAlgoID == 5)
    {
        qimg = AlgoSaturation(imgInfo->nDelta,&imgInfo->qImage);
        imgInfo->qImage = *qimg;
    }
    else if(imgInfo->nAlgoID == 6)
    {
        qimg = AlgoBlur(imgInfo->nDelta,&imgInfo->qImage);
        imgInfo->qImage = *qimg;
    }
    else if(imgInfo->nAlgoID == 7)
    {
        qimg = AlgoSharpen(imgInfo->nDelta,&imgInfo->qImage);
        imgInfo->qImage = *qimg;
    }
    else if(imgInfo->nAlgoID == 8)
    {
        qimg = AlgoDrawFrame(imgInfo->nDelta,&imgInfo->qImage);
        imgInfo->qImage = *qimg;
    }
}

QImage *ProcessorThread::AlgoCool(int delta, QImage * origin)//如果说暖色调的图片偏黄色，那么冷色调的图片应该就是偏蓝色了。在这个方法里面我们只增加蓝色通道的值，红色和绿色的值不变
{
    QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);
    QColor oldColor;
    int r,g,b;
    for(int x=0; x<newImage->width(); x++){
        for(int y=0; y<newImage->height(); y++){
            oldColor = QColor(origin->pixel(x,y));

            r = oldColor.red();
            g = oldColor.green();
            b = oldColor.blue()+delta;
            //we check if the new value is between 0 and 255
            b = qBound(0, b, 255);
            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return newImage;
}

QImage * ProcessorThread::AlgoWarm(int delta, QImage * origin)//当我们说一一幅暖色调的图片的时候通常是因为这张图色调偏黄。我们没有黄色的通道，但是红色和绿色混合起来就是黄色，所以我们增加这两个通道值，然后蓝色通道值不变
{
    QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

    QColor oldColor;
    int r,g,b;

    for(int x=0; x<newImage->width(); x++){
        for(int y=0; y<newImage->height(); y++){
            oldColor = QColor(origin->pixel(x,y));
            r = oldColor.red() + delta;
            g = oldColor.green() + delta;
            b = oldColor.blue();
            //we check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }

    return newImage;
}

QImage * ProcessorThread::AlgoGreyScale(int delta,QImage * origin)
//将彩色图转换成灰度图，我们首先要明白的一点就是，其实标准的灰度图就是每个像素点的三个通道的值一样或者近似，我们的策略就是将每个像素的每个通道的值都调成一样，取R,G,B值为三者的算数平均数就可以了，比如原色是RGB(169,204,69), 那么最终的RGB就是（169+204+69）/3 = 147.
{
    QImage * newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);
    for(int y = 0; y<newImage->height(); y++){
        QRgb * line = (QRgb *)origin->scanLine(y);//按行读取，效率比一个一个字节读取要高
        for(int x = 0; x<newImage->width(); x++)
        {
            int average = (qRed(line[x]) + qGreen(line[x]) + qRed(line[x]))/3;
            average += delta;
            average = qBound(0, average, 255);//将像素值范围定在0-255
            newImage->setPixel(x,y, qRgb(average, average, average));
        }
    }
    return newImage;
}

QImage *ProcessorThread::AlgoLight(int delta, QImage *origin)
//同时增加三个通道的数值变量，反之就是变暗
{
    QImage *newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);
    QColor oldColor;
    int r,g,b;
    for(int x=0; x<newImage->width(); x++)
    {
        for(int y=0; y<newImage->height(); y++)
        {
            oldColor = QColor(origin->pixel(x,y));
            r = oldColor.red() + delta;
            g = oldColor.green() + delta;
            b = oldColor.blue()+ delta;
            //we check if the new values are between 0 and 255
            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);
            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return newImage;
}

QImage *ProcessorThread::AlgoSaturation(int delta, QImage * origin)
//颜色由三个通道组成：红，绿，蓝，尽管如此，RGB不是唯一一个表示色彩的方式，在这里，使用HSL格式表示色彩 - hue（色相）, saturation（饱和度）, lightness（明度）。
//饱和的图像拥有更加生动的颜色，通常会比较好看，但不要滥用饱和度，因为很容易出现失真。
{
    QImage * newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

    QColor oldColor;
    QColor newColor;
    int h,s,l;

    for(int x=0; x<newImage->width(); x++){
        for(int y=0; y<newImage->height(); y++){
            oldColor = QColor(origin->pixel(x,y));

            newColor = oldColor.toHsl();
            h = newColor.hue();
            s = newColor.saturation()+delta;
            l = newColor.lightness();

            //we check if the new value is between 0 and 255
            s = qBound(0, s, 255);

            newColor.setHsl(h, s, l);

            newImage->setPixel(x, y, qRgb(newColor.red(), newColor.green(), newColor.blue()));
        }
    }

    return newImage;
}


//模糊这个效果相对于之前的有一点点复杂。我们会用到一个卷积滤波器，根据当前像素的颜色和相邻像素的颜色来获得一个新的颜色。同时还有一个kernel的矩阵来决定计算中相邻像素的影响程度。
//原像素会在矩阵的中心，因此我们会使用基数行的行和列。我们不会修改边缘的像素点，因为那些点没有我们需要的相邻像素点，虽然我们也可以只使用有效的像素点。
//举了例子，让我们来看看如何计算像素的RGB值。下面的三个举证代表着当前像素和邻接像素的RGB值，最中间的是当前像素。
//R = 20 102 99
//150 200 77
//170 210 105
//G = 22 33 40
//17 21 33
//8 15 24
//B = 88 70 55
//90 72 59
//85 69 50
//Kenel =  0 2 0
//2 5 2
//0 2 0
//使用滤波器进行计算：
//r = ( (102*2) + (150*2) + (200*5) + (77*2) + (210*2) ) / (2+2+5+2+2) = 159
//g = ( (33*2) + ( 17*2) + (21*5) + (33*2) + (15*2) ) / (2+2+5+2+2) = 23
//b = ( (70*2) + (90*2) + (72*5) + (59*2) + (69*2) ) / (2+2+5+2+2) = 72
//由原始的RGB(200, 21, 72)得到了RGB(159, 23, 72).  发现最大的变化是红色的通道，因为红色通道的值差距最大。
//在修改肖像照片的时候通常会使用到模糊的技术，它能后掩盖住皮肤的瑕疵。
QImage  *ProcessorThread::AlgoBlur(int delta,QImage * origin)
{
    QImage * newImage = new QImage(*origin);

    int kernel [5][5]= {{0,0,1,0,0},
                        {0,1,3,1,0},
                        {1,3,7,3,1},
                        {0,1,3,1,0},
                        {0,0,1,0,0}};
    int kernelSize = 5;
    //int sumKernel = 27+delta;
    int sumKernel = 27;
    int r,g,b;
    QColor color;

    for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++){

            r = 0;
            g = 0;
            b = 0;

            for(int i = -kernelSize/2; i<= kernelSize/2; i++){
                for(int j = -kernelSize/2; j<= kernelSize/2; j++){
                    color = QColor(origin->pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }

            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);

            newImage->setPixel(x,y, qRgb(r,g,b));

        }
    }
    return newImage;
}

//像模糊中一样，锐化一张图片也会使用一个卷积滤波器，但是kernel矩阵是不一样的，相邻像素对应的值是负的。
//锐化能够处理模糊的照片，能够提升细节。
QImage  *ProcessorThread::AlgoSharpen(int delta,QImage * origin)
{
    QImage * newImage = new QImage(* origin);
    int kernel [3][3]= {{0,-1,0},
                        {-1,5,-1},
                        {0,-1,0}};
    int kernelSize = 3;
    int sumKernel = 1;
    int r,g,b;
    QColor color;
    for(int x=kernelSize/2; x<newImage->width()-(kernelSize/2); x++){
        for(int y=kernelSize/2; y<newImage->height()-(kernelSize/2); y++)
        {
            r = 0;
            g = 0;
            b = 0;
            for(int i = -kernelSize/2; i<= kernelSize/2; i++)
            {
                for(int j = -kernelSize/2; j<= kernelSize/2; j++)
                {
                    color = QColor(origin->pixel(x+i, y+j));
                    r += color.red()*kernel[kernelSize/2+i][kernelSize/2+j];
                    g += color.green()*kernel[kernelSize/2+i][kernelSize/2+j];
                    b += color.blue()*kernel[kernelSize/2+i][kernelSize/2+j];
                }
            }
            r = qBound(0, r/sumKernel, 255);
            g = qBound(0, g/sumKernel, 255);
            b = qBound(0, b/sumKernel, 255);
            newImage->setPixel(x,y, qRgb(r,g,b));
        }
    }
    return newImage;
}

QImage * ProcessorThread::AlgoDrawFrame(int delta,QImage * origin)
{
    QString m_wstrFilePath = qApp->applicationDirPath() + "/../../EditPic/res/frame.png" ;//in windows system
    QImage * newImage = new QImage(* origin);
    QImage imgtemp(m_wstrFilePath);
    QImage qImgFrame =  imgtemp.scaled(newImage->width(),newImage->height());
    QPainter painter;
    painter.begin(newImage);
    painter.drawImage(0,0, qImgFrame);//将qImgFrame图片花在newImage上
    painter.setPen(QPen(Qt::white,10,Qt::SolidLine));//设置画笔，颜色white，画笔宽度10个像素，画笔样式为实线
    painter.drawPoint(10,10);//在点位置（10,10）处画一个白色的直径为10个像素的点（其实画出来是个边长为10的正方形）
    painter.drawLine(20,20,40,40);//绘制x
    painter.drawLine(40,20,20,40);//绘制x
    painter.end();

    return newImage;
}
