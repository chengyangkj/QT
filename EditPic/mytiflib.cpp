#include "mytiflib.h"

MyTifLib::MyTifLib()
{

}

MyTifLib::~MyTifLib()
{

}

bool MyTifLib::ParseTIFF(QString sFilePath, MY_TIFF &myTIFF)
{
    QFile file(sFilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }
    QByteArray t = file.readAll();
    file.close();
    memcpy((char*)&myTIFF.tMyIFH.nByteOrder,t.data(),2*sizeof(char));
    memcpy((char*)&myTIFF.tMyIFH.nVersion,t.data()+2,2*sizeof(char));
    memcpy((char*)&myTIFF.tMyIFH.nOffset2FirstIFD,t.data()+4,4*sizeof(char));
    memcpy((char*)&myTIFF.tMyIFD.nIDNum,t.data()+myTIFF.tMyIFH.nOffset2FirstIFD,2*sizeof(char));
    myTIFF.tMyIFD.vMyDE.resize(myTIFF.tMyIFD.nIDNum);
    for (int i=0;i<myTIFF.tMyIFD.nIDNum;i++)
    {
        memcpy((char*)&myTIFF.tMyIFD.vMyDE[i].nTagID,t.data()+myTIFF.tMyIFH.nOffset2FirstIFD+2+12*i,2*sizeof(char));
        memcpy((char*)&myTIFF.tMyIFD.vMyDE[i].nType,t.data()+myTIFF.tMyIFH.nOffset2FirstIFD+2+12*i+2,2*sizeof(char));
        memcpy((char*)&myTIFF.tMyIFD.vMyDE[i].nLength,t.data()+myTIFF.tMyIFH.nOffset2FirstIFD+2+12*i+4,4*sizeof(char));
        memcpy((char*)&myTIFF.tMyIFD.vMyDE[i].nValueOffset,t.data()+myTIFF.tMyIFH.nOffset2FirstIFD+2+12*i+8,4*sizeof(char));
        if(myTIFF.tMyIFD.vMyDE[i].nTagID == 0x0100)//表示图像宽度
        {
            myTIFF.tImgInfo.nWidth = myTIFF.tMyIFD.vMyDE[i].nValueOffset;
        }
        if(myTIFF.tMyIFD.vMyDE[i].nTagID == 0x0101)//表示图像高
        {
            myTIFF.tImgInfo.nHeight = myTIFF.tMyIFD.vMyDE[i].nValueOffset;
        }
        if(myTIFF.tMyIFD.vMyDE[i].nTagID == 0x0102)//表示图像每个像素深度，即占多少位宽
        {
            myTIFF.tImgInfo.nDepth = myTIFF.tMyIFD.vMyDE[i].nValueOffset;
        }
        if(myTIFF.tMyIFD.vMyDE[i].nTagID == 0x0103)//表示图像数据是否压缩
        {
            if(myTIFF.tMyIFD.vMyDE[i].nValueOffset == 5)
            {
                myTIFF.tImgInfo.bCompressed = true;
            }
            else
            {
                myTIFF.tImgInfo.bCompressed = false;
            }
        }
        if(myTIFF.tMyIFD.vMyDE[i].nTagID == 0x0111)//图像数据起始字节相对于文件开始处的偏移量
        {
            myTIFF.tImgInfo.nDataOffset = myTIFF.tMyIFD.vMyDE[i].nValueOffset;
        }
        if(myTIFF.tMyIFD.vMyDE[i].nTagID == 0x0117)//图像数据字节总数
        {
            myTIFF.tImgInfo.nDataSize = myTIFF.tMyIFD.vMyDE[i].nValueOffset;
        }
    }
    if(myTIFF.tImgInfo.bCompressed)
    {
        return false;
    }
    if(myTIFF.tImgInfo.nDepth == 16)
    {
        //TODO:
        myTIFF.vShortData.resize(myTIFF.tImgInfo.nWidth*myTIFF.tImgInfo.nHeight);
        if(myTIFF.vShortData.size()<1)
        {
            return false;
        }
        memcpy((char*)&myTIFF.vShortData[0],t.data()+myTIFF.tImgInfo.nDataOffset,myTIFF.tImgInfo.nDataSize*sizeof(char));
    }
    else if(myTIFF.tImgInfo.nDepth == 12)
    {
        //TODO:
        myTIFF.vShortData.resize(myTIFF.tImgInfo.nWidth*myTIFF.tImgInfo.nHeight);
        if(myTIFF.vShortData.size()<1)
        {
            return false;
        }
        memcpy((char*)&myTIFF.vShortData[0],t.data()+myTIFF.tImgInfo.nDataOffset,myTIFF.tImgInfo.nDataSize*sizeof(char));
    }
    else if(myTIFF.tImgInfo.nDepth == 8)
    {
        //TODO:
        myTIFF.vUcharData.resize(myTIFF.tImgInfo.nWidth*myTIFF.tImgInfo.nHeight);
        if(myTIFF.vUcharData.size()<1)
        {
            return false;
        }
        memcpy((char*)&myTIFF.vUcharData[0],t.data()+myTIFF.tImgInfo.nDataOffset,myTIFF.tImgInfo.nDataSize*sizeof(char));
    }
    else
    {
        return false;
    }
    return true;
}
