#ifndef MYTIFLIB_H
#define MYTIFLIB_H
//************************************************************
//by Bruce Xu
//注：该类只解析特定的tiff文件！
//1.解析的tiff文件中只存在一幅图，如果文件中存在多幅图，本类不支持解析！
//2.图像数据为8位或12位或16位深度的灰度图，如果是其他类型的图片，本类不支持解析！
//3.图片没有被压缩过！
//************************************************************
#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
struct MY_IFH//Image File Head
{
    qint16          nByteOrder;//TIF标记，其值为0x4D4D或0x4949
    qint16          nVersion;//版本号，其值恒为0x2A
    qint32          nOffset2FirstIFD;//第一个IFD的偏移量
};
struct MY_DE//Directory Entry
{
    qint16          nTagID;//本属性的标签编号
    qint16          nType;//本属性值的数据类型
    qint32          nLength;//该种类型的数据的个数，而不是某个数据的长度
    qint32          nValueOffset;//tagID代表的变量值相对文件开始处的偏移量，但如果变量值占用的空间不多于4个字节（例如只有1个Integer类型的值），那么该值就直接存放在valueOffset中，没必要再另外指向一个地方了。
};
struct MY_IFD//image file directory
{
    qint16          nIDNum;//本IFD中DE的数量
    QVector<MY_DE>  vMyDE;//本IFD中的DE
};

struct MY_ImgInfo//图片属性信息
{
    qint32          nHeight;//图像的宽度
    qint32          nWidth;//图像的高度
    qint16          nDepth;//图像的深度
    bool            bCompressed;//图像是否被压缩
    qint32          nDataOffset;//图像第一个像素数据距离的偏移多少字节
    qint32          nDataSize;//图像数据字节总数
};

struct MY_TIFF//Image File Struct
{
    MY_IFH                  tMyIFH;//Image File Head
    MY_IFD                  tMyIFD;//放image file directory的容器
    QVector<unsigned char>  vUcharData;//如果是8位深的灰度图用unsigned char 放数据
    QVector<unsigned short> vShortData;//如果是16位深的灰度图用short* 放数据
    MY_ImgInfo              tImgInfo;//图片属性信息
};

class MyTifLib
{
public:
    MyTifLib();
    ~MyTifLib();
    bool            ParseTIFF(QString sFilePath, MY_TIFF &myTIFF);
};

#endif // MYTIFLIB_H
