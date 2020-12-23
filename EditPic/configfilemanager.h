#ifndef CONFIGFILEMANAGER_H
#define CONFIGFILEMANAGER_H
#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QtXml/QDomDocument>
#include <QDebug>
#include <QMap>
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
#include <QVector>
struct PARAM//参数节点
{
    int                 m_nIndex;//参数ID
    QString             m_sName;//参数名
    QString             m_sNickname;//参数中文名
    QString             m_sValueType;//参数类型
    int                 m_nValueRange[2];//int类型的参数范围
    float               m_fValueRange[2];//float类型的参数范围
    QVector<int>        m_vIntValue;//int类型的参数容器
    QVector<float>      m_vFloatValue;//float类型的参数容器
    QString             m_sStringValue;//string类型的参数、或者enum类型的参数、或bool类型的参数
    QStringList         m_slistEnumValues;//enum类型的参数值列表
    bool                m_bVisible;//参数是否显示
    PARAM():m_nIndex(0),
        m_sName(""),
        m_sNickname(""),
        m_sValueType(""),
        m_bVisible(true)
    {
        m_nValueRange[0] = 0;
        m_nValueRange[1] = 0;
        m_fValueRange[0] = 0;
        m_fValueRange[1] = 0;
        m_sStringValue = "";
        if(!m_slistEnumValues.empty())
        {
            m_slistEnumValues.clear();
        }
    }
};
struct BRANCH_LEVEL2//二级分支节点
{
    int                     m_nIndex;
    QString                 m_sName;
    QString                 m_sNickname;
    int                     m_nAlgoId;
    bool                    m_bVisible;
    QMap<int,PARAM>         m_mapParams;
};
struct BRANCH_LEVEL1//一级分支节点
{
    int                     m_nIndex;
    QString                 m_sName;
    QString                 m_sNickname;
    int                     m_nAlgoId;
    bool                    m_bVisible;
    QVector<int>            m_vInvokeOrder;
    QMap<int,BRANCH_LEVEL2>       m_mapBranchLevel2;
};
struct ROOT//根节点
{
    QString                 m_sVersion;
    QString                 m_sTime;
    QMap<int,BRANCH_LEVEL1>     m_mapBranchLevel1;
};
class ConfigFileManager : public QObject
{
        Q_OBJECT
public:
    ConfigFileManager();
    bool            ParseConfigFile();
    bool            SaveConfigFile();


private:
    void            ParseROOT(QDomNode* node);
    void            ParseBRANCH_LEVEL1(QDomNode* node, QMap<int, BRANCH_LEVEL1> &mapBranchLevel1);
    void            ParseBRANCH_LEVEL2(QDomNode *node, QMap<int, BRANCH_LEVEL2> &mapBranchLevel2);
    void            ParseParameters(QDomNode *node, QMap<int,PARAM> &mapParam);
    void            SaveROOT(QDomNode* node);
    void            SaveBranchLevel1(QDomElement* parentNode,QMap<int, BRANCH_LEVEL1> &mapBranchLevel1);
    void            SaveBranchLevel2(QDomElement* parentNode, QMap<int, BRANCH_LEVEL2> &mapBranchLevel2);
    void            SaveParams(QDomElement* parentNode, QMap<int, PARAM> &mapParam);
    QVector<int>    SplitXmlStringInt(QString xmlText);
    QVector<float>  SplitXmlStringFloat(QString xmlText);
private:
    ROOT                m_tRoot;
    QDomDocument     m_domDocSaveConfig;
};

#endif // CONFIGFILEMANAGER_H
