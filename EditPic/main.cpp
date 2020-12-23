#include "mainwindow.h"
#include <QApplication>
//struct XDFPoint
//{
//    float   x;
//    float   y;
//};

////求逆矩阵
//void InverF(double *p1, double *p2, int n)
//{
//    int i, j, r;
//    int n2 = 2 * n;
//    for (i = 0; i < n; i++)
//    {
//        for (j = 0; j < n; j++)
//        {
//            p1[i * n2 + j + n] = 0;    //右边
//            p1[i * n2 + i + n] = 1;
//        }
//    }

//    //对于对角元素为0的进行换行操作
//    double temp;
//    for (i = 0; i < n; i++)
//    {
//        while (p1[i*n2 + i] == 0)
//        {
//            for (j = i + 1; j < n; j++)
//            {
//                if (p1[j*n2 + i] != 0)
//                {
//                    temp = 0;
//                    //for (r = i; r < 2 * n; r++)
//                    for (r = 0; r < 2 * n; r++)
//                    {
//                        temp = p1[j*n2 + r];
//                        p1[j*n2 + r] = p1[i*n2 + r];
//                        p1[i*n2 + r] = temp;
//                    }
//                }
//                break;
//            }
//        }
//    }

//    //行变换为上三角矩阵
//    double k = 0;
//    for (i = 0; i < n; i++)
//    {
//        for (j = i + 1; j < n; j++)
//        {
//            if( p1[i*n2 + i] == 0.0)
//            {
//                qDebug()<<" p1[i*n2 + i]==0!";
//            }
//            k = (-1)*p1[j*n2 + i] / p1[i*n2 + i];
//            for (r = i; r < 2 * n; r++)
//                p1[j*n2 + r] += k*p1[i*n2 + r];
//        }
//    }

//    if (p1[(n - 1)*n2 + n - 1] == 0)
//    {
//        return;
//    }
//    //行变换为下三角矩阵
//    for (i = n - 1; i >= 0; i--)
//    {
//        for (j = i - 1; j >= 0; j--)
//        {
//            k = (-1)*p1[j*n2 + i] / p1[i*n2 + i];
//            for (r = 0; r < 2 * n; r++)
//                p1[j*n2 + r] += k*p1[i*n2 + r];
//        }
//    }

//    //化为单位阵
//    for (i = n - 1; i >= 0; i--)
//    {
//        k = p1[i*n2 + i];
//        for (j = 0; j < 2 * n; j++)
//            p1[i*n2 + j] /= k;
//    }


//    //拆分出逆矩阵
//    for (i = 0; i < n; i++)
//    {
//        for (j = 0; j < n; j++)
//            p2[i*n + j] = p1[i*n2 + n + j];
//    }

//}

//void ProjectiveMatrixF(XDFPoint *movingPoints, XDFPoint *fixedPoints, double *iPMat) {
//    double iMatrix[8 * 16] = {0.0};
//    double iMatrixOut[8 * 8] = {0.0};
//    double iVec[8] = {0.0};
//    double fVec[18] = {0.0};
//    double fVecOut[9] = {0.0};
//    int n2 = 16;
//    iVec[0] = movingPoints[0].x;
//    iVec[1] = movingPoints[1].x;
//    iVec[2] = movingPoints[2].x;
//    iVec[3] = movingPoints[3].x;
//    iVec[4] = movingPoints[0].y;
//    iVec[5] = movingPoints[1].y;
//    iVec[6] = movingPoints[2].y;
//    iVec[7] = movingPoints[3].y;

//    iMatrix[0] = fixedPoints[0].x; iMatrix[1] = fixedPoints[0].y; iMatrix[0 * n2 + 2] = 1; iMatrix[0 * n2 + 3] = 0; iMatrix[0 * n2 + 4] = 0; iMatrix[0 * n2 + 5] = 0; iMatrix[0 * n2 + 6] = -movingPoints[0].x*fixedPoints[0].x; iMatrix[0 * n2 + 7] = -movingPoints[0].x*fixedPoints[0].y;
//    iMatrix[1 * n2] = fixedPoints[1].x; iMatrix[1 * n2 + 1] = fixedPoints[1].y; iMatrix[1 * n2 + 2] = 1; iMatrix[1 * n2 + 3] = 0; iMatrix[1 * n2 + 4] = 0; iMatrix[1 * n2 + 5] = 0; iMatrix[1 * n2 + 6] = -movingPoints[1].x*fixedPoints[1].x; iMatrix[1 * n2 + 7] = -movingPoints[1].x*fixedPoints[1].y;
//    iMatrix[2 * n2] = fixedPoints[2].x; iMatrix[2 * n2 + 1] = fixedPoints[2].y; iMatrix[2 * n2 + 2] = 1; iMatrix[2 * n2 + 3] = 0; iMatrix[2 * n2 + 4] = 0; iMatrix[2 * n2 + 5] = 0; iMatrix[2 * n2 + 6] = -movingPoints[2].x*fixedPoints[2].x; iMatrix[2 * n2 + 7] = -movingPoints[2].x*fixedPoints[2].y;
//    iMatrix[3 * n2] = fixedPoints[3].x; iMatrix[3 * n2 + 1] = fixedPoints[3].y; iMatrix[3 * n2 + 2] = 1; iMatrix[3 * n2 + 3] = 0; iMatrix[3 * n2 + 4] = 0; iMatrix[3 * n2 + 5] = 0; iMatrix[3 * n2 + 6] = -movingPoints[3].x*fixedPoints[3].x; iMatrix[3 * n2 + 7] = -movingPoints[3].x*fixedPoints[3].y;
//    iMatrix[4 * n2] = 0; iMatrix[4 * n2 + 1] = 0; iMatrix[4 * n2 + 2] = 0; iMatrix[4 * n2 + 3] = fixedPoints[0].x; iMatrix[4 * n2 + 4] = fixedPoints[0].y; iMatrix[4 * n2 + 5] = 1; iMatrix[4 * n2 + 6] = -movingPoints[0].y*fixedPoints[0].x; iMatrix[4 * n2 + 7] = -movingPoints[0].y*fixedPoints[0].y;
//    iMatrix[5 * n2] = 0; iMatrix[5 * n2 + 1] = 0; iMatrix[5 * n2 + 2] = 0; iMatrix[5 * n2 + 3] = fixedPoints[1].x; iMatrix[5 * n2 + 4] = fixedPoints[1].y; iMatrix[5 * n2 + 5] = 1; iMatrix[5 * n2 + 6] = -movingPoints[1].y*fixedPoints[1].x; iMatrix[5 * n2 + 7] = -movingPoints[1].y*fixedPoints[1].y;
//    iMatrix[6 * n2] = 0; iMatrix[6 * n2 + 1] = 0; iMatrix[6 * n2 + 2] = 0; iMatrix[6 * n2 + 3] = fixedPoints[2].x; iMatrix[6 * n2 + 4] = fixedPoints[2].y; iMatrix[6 * n2 + 5] = 1; iMatrix[6 * n2 + 6] = -movingPoints[2].y*fixedPoints[2].x; iMatrix[6 * n2 + 7] = -movingPoints[2].y*fixedPoints[2].y;
//    iMatrix[7 * n2] = 0; iMatrix[7 * n2 + 1] = 0; iMatrix[7 * n2 + 2] = 0; iMatrix[7 * n2 + 3] = fixedPoints[3].x; iMatrix[7 * n2 + 4] = fixedPoints[3].y; iMatrix[7 * n2 + 5] = 1; iMatrix[7 * n2 + 6] = -movingPoints[3].y*fixedPoints[3].x; iMatrix[7 * n2 + 7] = -movingPoints[3].y*fixedPoints[3].y;

//    InverF(&(iMatrix[0]), &(iMatrixOut[0]), 8);

//    fVecOut[0] = iMatrixOut[0] * iVec[0] + iMatrixOut[1] * iVec[1] + iMatrixOut[2] * iVec[2] + iMatrixOut[3] * iVec[3] + iMatrixOut[4] * iVec[4] + iMatrixOut[5] * iVec[5] + iMatrixOut[6] * iVec[6] + iMatrixOut[7] * iVec[7];
//    fVecOut[1] = iMatrixOut[8] * iVec[0] + iMatrixOut[9] * iVec[1] + iMatrixOut[10] * iVec[2] + iMatrixOut[11] * iVec[3] + iMatrixOut[12] * iVec[4] + iMatrixOut[13] * iVec[5] + iMatrixOut[14] * iVec[6] + iMatrixOut[15] * iVec[7];
//    fVecOut[2] = iMatrixOut[16] * iVec[0] + iMatrixOut[17] * iVec[1] + iMatrixOut[18] * iVec[2] + iMatrixOut[19] * iVec[3] + iMatrixOut[20] * iVec[4] + iMatrixOut[21] * iVec[5] + iMatrixOut[22] * iVec[6] + iMatrixOut[23] * iVec[7];
//    fVecOut[3] = iMatrixOut[24] * iVec[0] + iMatrixOut[25] * iVec[1] + iMatrixOut[26] * iVec[2] + iMatrixOut[27] * iVec[3] + iMatrixOut[28] * iVec[4] + iMatrixOut[29] * iVec[5] + iMatrixOut[30] * iVec[6] + iMatrixOut[31] * iVec[7];
//    fVecOut[4] = iMatrixOut[32] * iVec[0] + iMatrixOut[33] * iVec[1] + iMatrixOut[34] * iVec[2] + iMatrixOut[35] * iVec[3] + iMatrixOut[36] * iVec[4] + iMatrixOut[37] * iVec[5] + iMatrixOut[38] * iVec[6] + iMatrixOut[39] * iVec[7];
//    fVecOut[5] = iMatrixOut[40] * iVec[0] + iMatrixOut[41] * iVec[1] + iMatrixOut[42] * iVec[2] + iMatrixOut[43] * iVec[3] + iMatrixOut[44] * iVec[4] + iMatrixOut[45] * iVec[5] + iMatrixOut[46] * iVec[6] + iMatrixOut[47] * iVec[7];
//    fVecOut[6] = iMatrixOut[48] * iVec[0] + iMatrixOut[49] * iVec[1] + iMatrixOut[50] * iVec[2] + iMatrixOut[51] * iVec[3] + iMatrixOut[52] * iVec[4] + iMatrixOut[53] * iVec[5] + iMatrixOut[54] * iVec[6] + iMatrixOut[55] * iVec[7];
//    fVecOut[7] = iMatrixOut[56] * iVec[0] + iMatrixOut[57] * iVec[1] + iMatrixOut[58] * iVec[2] + iMatrixOut[59] * iVec[3] + iMatrixOut[60] * iVec[4] + iMatrixOut[61] * iVec[5] + iMatrixOut[62] * iVec[6] + iMatrixOut[63] * iVec[7];
//    fVecOut[8] = 1;

//    iPMat[0] = fVecOut[0];
//    iPMat[1] = fVecOut[3];
//    iPMat[2] = fVecOut[6];
//    iPMat[3] = fVecOut[1];
//    iPMat[4] = fVecOut[4];
//    iPMat[5] = fVecOut[7];
//    iPMat[6] = fVecOut[2];
//    iPMat[7] = fVecOut[5];
//    iPMat[8] = fVecOut[8];
//}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    //test
//    XDFPoint SrcInput[4], DstInput[4];
//    double iPMat[9];

//    FILE *fp;
//    fp = fopen("SrcInput.bin", "rb");
//    fread((float *)&SrcInput[0], sizeof(float), 8, fp);
//    fclose(fp);

//    fp = fopen("DstInput.bin", "rb");
//    fread((float *)&DstInput[0], sizeof(float), 8, fp);
//    fclose(fp);

//    ProjectiveMatrixF(&DstInput[0], &SrcInput[0], &iPMat[0]);

//    for (int i = 0; i < 9; i++) {
//       // printf("%d:%lf\n",i, iPMat[0]);
//        qDebug()<<i<<" "<<iPMat[i];
//    }
//    //test
    return a.exec();
}
