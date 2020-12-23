#include "configfilemanager.h"

ConfigFileManager::ConfigFileManager()
{

}
bool ConfigFileManager::ParseConfigFile()//读取test.config文件并获取根节点
{
    QString sConfigFilePath;
#if defined(Q_OS_LINUX)
    sConfigFilePath = qApp->applicationDirPath() + "/../EditPic/test.config" ;//in linux
#else
    sConfigFilePath = qApp->applicationDirPath() + "/../../EditPic/test.config" ;//in windows，我的工程名为EditPic
#endif
    QFile file(sConfigFilePath);
    if (!file.open(QFile::ReadOnly))
    {
        return false;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument qDomConfigFile;
    if (!qDomConfigFile.setContent(&file, false, &errorStr, &errorLine,&errorColumn))
    {
        return false;
    }
    QDomElement root = qDomConfigFile.documentElement();
    QDomNode child = root.firstChild();
    if (!child.isNull())
    {
        if(child.toElement().tagName() == "ROOT")
        {
            ParseROOT(&child);
        }
    }
    file.close();
    return true;
}

bool ConfigFileManager::SaveConfigFile()
{
    qSetGlobalQHashSeed(100);//为了使 通过QDomElement保存节点属性时， 每次保存的属性的顺序固定，与qSetGlobalQHashSeed(-1);搭配着用
    //projectDoc.createProcessingInstruction("xml","version = "1.0"encoding = " UTF-8"");
    QDomElement root = m_domDocSaveConfig.documentElement();
    if(root.isNull())
    {
        root = m_domDocSaveConfig.createElement("configuration");
    }
    SaveROOT(&root);
    m_domDocSaveConfig.appendChild(root);
//#if defined(Q_OS_LINUX)
//    m_wstrFilePath = qApp->applicationDirPath() + "/../Tx2Oled/XMLTest/"+strProName+".config";//in linux system
//#else
    QString sFilePath = qApp->applicationDirPath() + "/../../EditPic/test2.config";//in windows system XMLTest
//#endif
    QFile file(sFilePath);
    if (!file.open(QFile::WriteOnly|QFile::Truncate | QFile::Text))//1.QFile::WriteOnly如果文件不存在，则创建；2.QFile::Truncate打开的同时清空
    {
        return false;
    }
    QTextStream stream( &file );
    stream.setCodec("utf-8");
    m_domDocSaveConfig.save(stream,4,QDomNode::EncodingFromTextStream);
    file.close();
    qSetGlobalQHashSeed(-1);
    return true;
}

void ConfigFileManager::ParseROOT(QDomNode *node)//解析根节点
{
    m_tRoot.m_sVersion = node->toElement().attribute("version");
    m_tRoot.m_sTime = node->toElement().attribute("time");
    ParseBRANCH_LEVEL1(node,m_tRoot.m_mapBranchLevel1);
}

void ConfigFileManager::ParseBRANCH_LEVEL1(QDomNode *node, QMap<int, BRANCH_LEVEL1> &mapBranchLevel1)//解析一级分支
{
    QDomNode childnode = node->toElement().firstChild();
    while(!childnode.isNull())
    {
        if(childnode.toElement().tagName() == "BRANCH_LEVEL1")
        {
            BRANCH_LEVEL1 BranchLevel1;
            BranchLevel1.m_sName = childnode.toElement().attribute("name");
            BranchLevel1.m_nAlgoId = childnode.toElement().attribute("AlgorithmID").toInt();
            BranchLevel1.m_sNickname = childnode.toElement().attribute("nickname");
            BranchLevel1.m_nIndex = childnode.toElement().attribute("index").toInt();
            QString sVisible = childnode.toElement().attribute("visible");
            if(sVisible=="on")
            {
                BranchLevel1.m_bVisible = true;
            }
            else
            {
                BranchLevel1.m_bVisible = false;
            }
            QString sInvokerOrder = childnode.toElement().attribute("invokeOrder");
            BranchLevel1.m_vInvokeOrder = SplitXmlStringInt(sInvokerOrder);
            ParseBRANCH_LEVEL2(&childnode,BranchLevel1.m_mapBranchLevel2);
            mapBranchLevel1.insert(BranchLevel1.m_nIndex,BranchLevel1);
        }
        childnode = childnode.nextSibling();
    }
}

void ConfigFileManager::ParseBRANCH_LEVEL2(QDomNode *node, QMap<int, BRANCH_LEVEL2> &mapBranchLevel2)//解析二级分支
{
    QDomNode childnode = node->toElement().firstChild();
    while(!childnode.isNull())
    {
        if(childnode.toElement().tagName() == "BRANCH_LEVEL2")
        {
            BRANCH_LEVEL2 BranchLevel2;
            BranchLevel2.m_sName = childnode.toElement().attribute("name");
            BranchLevel2.m_nAlgoId = childnode.toElement().attribute("SubAlgoID").toInt();
            BranchLevel2.m_sNickname = childnode.toElement().attribute("nickname");
            BranchLevel2.m_nIndex = childnode.toElement().attribute("index").toInt();
            QString sVisible = childnode.toElement().attribute("visible");
            if(sVisible=="on")
            {
                BranchLevel2.m_bVisible = true;
            }
            else
            {
                BranchLevel2.m_bVisible = false;
            }
            ParseParameters(&childnode,BranchLevel2.m_mapParams);
            mapBranchLevel2.insert(BranchLevel2.m_nIndex,BranchLevel2);
        }
        childnode = childnode.nextSibling();
    }
}
void ConfigFileManager::ParseParameters(QDomNode *node, QMap<int,PARAM> &mapParam)//解析参数
{

    QDomNode childnode = node->toElement().firstChild();
    while(!childnode.isNull())
    {
        if(childnode.toElement().tagName() == "param")
        {
            PARAM Parameter;
            Parameter.m_nIndex = childnode.toElement().attribute("index").toInt();
            Parameter.m_sName = childnode.toElement().attribute("name");
            Parameter.m_sNickname = childnode.toElement().attribute("nickname");
            Parameter.m_sValueType = childnode.toElement().attribute("valuetype");
            QString Value,RangeValue;
            if(Parameter.m_sValueType == "int")
            {
                Value = childnode.toElement().attribute("value");
                Parameter.m_vIntValue = SplitXmlStringInt(Value);
                RangeValue = childnode.toElement().attribute("valueRange");
                QStringList list = RangeValue.split(',');
                if(2 == list.size())
                {
                    Parameter.m_nValueRange[0] = list.at(0).toInt();
                    Parameter.m_nValueRange[1] = list.at(1).toInt();
                }
            }
            else if(Parameter.m_sValueType == "float")
            {
                Value = childnode.toElement().attribute("value");
                Parameter.m_vFloatValue = SplitXmlStringFloat(Value);
                RangeValue = childnode.toElement().attribute("valueRange");
                QStringList list = RangeValue.split(',');
                if(2 == list.size())
                {
                    Parameter.m_fValueRange[0] = list.at(0).toFloat();
                    Parameter.m_fValueRange[1] = list.at(1).toFloat();
                }
            }
            else if(Parameter.m_sValueType == "string")
            {
                Parameter.m_sStringValue = childnode.toElement().attribute("value");
            }
            else if((Parameter.m_sValueType == "enum")||((Parameter.m_sValueType == "bool")))
            {
                Parameter.m_sStringValue = childnode.toElement().attribute("value");
                QString valuelist = childnode.toElement().attribute("valueList");
                Parameter.m_slistEnumValues = valuelist.split(",");
                RangeValue = childnode.toElement().attribute("valueRange");
                QStringList list = RangeValue.split(',');
                if(2 == list.size())
                {
                    Parameter.m_nValueRange[0] = list.at(0).toInt();
                    Parameter.m_nValueRange[1] = list.at(1).toInt();
                }
            }
            QString sVisible = childnode.toElement().attribute("visible");
            if(sVisible=="on")
            {
                Parameter.m_bVisible = true;
            }
            else
            {
                Parameter.m_bVisible = false;
            }
            mapParam.insert(Parameter.m_nIndex,Parameter);
        }
        childnode = childnode.nextSibling();
    }
}

void ConfigFileManager::SaveROOT(QDomNode *node)
{
    QDomElement eldRoot = m_domDocSaveConfig.createElement("ROOT");
    eldRoot.setAttribute("version",m_tRoot.m_sVersion);
    eldRoot.setAttribute("time",m_tRoot.m_sTime);
    SaveBranchLevel1(&eldRoot,m_tRoot.m_mapBranchLevel1);
    node->appendChild(eldRoot);
}

void ConfigFileManager::SaveBranchLevel1(QDomElement *parentNode, QMap<int, BRANCH_LEVEL1> &mapBranchLevel1)
{
    for (int i = 1;i<(mapBranchLevel1.size()+1);i++)
    {
        QDomElement eleBranchLV1 = m_domDocSaveConfig.createElement("BRANCH_LEVEL1");
        eleBranchLV1.setAttribute("name",mapBranchLevel1[i].m_sName);
        eleBranchLV1.setAttribute("AlgorithmID",mapBranchLevel1[i].m_nAlgoId);
        eleBranchLV1.setAttribute("nickname",mapBranchLevel1[i].m_sNickname);
        eleBranchLV1.setAttribute("index",mapBranchLevel1[i].m_nIndex);
        QString qstr = "";
        int nNum = mapBranchLevel1[i].m_vInvokeOrder.size();
        for(int j = 0;j<nNum;j++)
        {
            if(j == 0)
            {
                qstr = QString::number(mapBranchLevel1[i].m_vInvokeOrder[j],10);
            }
            else
            {
                qstr=qstr+","+QString::number(mapBranchLevel1[i].m_vInvokeOrder[j],10);
            }
        }
        eleBranchLV1.setAttribute("invokeOrder",qstr);
        if(mapBranchLevel1[i].m_bVisible == true)
        {
            eleBranchLV1.setAttribute("visible","on");
        }
        else
        {
            eleBranchLV1.setAttribute("visible","off");
        }
        SaveBranchLevel2(&eleBranchLV1,mapBranchLevel1[i].m_mapBranchLevel2);
        parentNode->appendChild(eleBranchLV1);
    }
}

void ConfigFileManager::SaveBranchLevel2(QDomElement *parentNode, QMap<int, BRANCH_LEVEL2> &mapBranchLevel2)
{
    for (int i = 1;i<(mapBranchLevel2.size()+1);i++)
    {
        QDomElement eleBranchLV2 = m_domDocSaveConfig.createElement("BRANCH_LEVEL2");
        eleBranchLV2.setAttribute("name",mapBranchLevel2[i].m_sName);
        eleBranchLV2.setAttribute("SubAlgoID",mapBranchLevel2[i].m_nAlgoId);
        eleBranchLV2.setAttribute("nickname",mapBranchLevel2[i].m_sNickname);
        eleBranchLV2.setAttribute("index",mapBranchLevel2[i].m_nIndex);

        if(mapBranchLevel2[i].m_bVisible == true)
        {
            eleBranchLV2.setAttribute("visible","on");
        }
        else
        {
            eleBranchLV2.setAttribute("visible","off");
        }
        SaveParams(&eleBranchLV2,mapBranchLevel2[i].m_mapParams);
        parentNode->appendChild(eleBranchLV2);
    }
}

void ConfigFileManager::SaveParams(QDomElement *parentNode, QMap<int, PARAM> &mapParam)
{
    for (int i=1;i<(mapParam.size()+1);i++)
    {
        QDomElement param = m_domDocSaveConfig.createElement("param");
        param.setAttribute("name",mapParam[i].m_sName);
        param.setAttribute("nickname",mapParam[i].m_sNickname);
        param.setAttribute("index",mapParam[i].m_nIndex);
        param.setAttribute("valuetype",mapParam[i].m_sValueType);
        if(mapParam[i].m_bVisible)
        {
            param.setAttribute("visible","on");
        }
        else
        {
            param.setAttribute("visible","off");
        }
        //
        if(mapParam[i].m_sValueType == "int")
        {
            QString qstr = "";
            qstr = QString::number(mapParam[i].m_nValueRange[0],10) +","+QString::number(mapParam[i].m_nValueRange[1],10);
            param.setAttribute("valueRange",qstr);
            qstr = "";
            for(int j = 0;j<mapParam[i].m_vIntValue.size();j++)
            {
                if(j == 0)
                {
                    qstr = QString::number(mapParam[i].m_vIntValue[j],10);
                }
                else
                {
                    qstr=qstr+","+QString::number(mapParam[i].m_vIntValue[j],10);
                }
            }
            param.setAttribute("value",qstr);
        }
        else if(mapParam[i].m_sValueType == "float")
        {
            QString qstr = "";
            qstr = QString("%1").arg(mapParam[i].m_fValueRange[0]) +","+QString("%1").arg(mapParam[i].m_fValueRange[1]);
            param.setAttribute("valueRange",qstr);
            qstr = "";
            for(int j = 0;j<mapParam[i].m_vFloatValue.size();j++)
            {
                if(j == 0)
                {
                    qstr = QString("%1").arg(mapParam[i].m_vFloatValue[j]);
                }
                else
                {
                    qstr=qstr+","+QString("%1").arg(mapParam[i].m_vFloatValue[j]);
                }
            }
            param.setAttribute("value",qstr);
        }
        else if(mapParam[i].m_sValueType == "string")
        {
            param.setAttribute("value",mapParam[i].m_sStringValue);
        }
        else if(mapParam[i].m_sValueType == "enum")
        {
            param.setAttribute("value",mapParam[i].m_sStringValue);
            int nNum = mapParam[i].m_slistEnumValues.size();
            QString qstr = "";
            qstr = "0,"+QString("%1").arg((nNum-1));
            param.setAttribute("valueRange",qstr);
            qstr = "";
            for(int j = 0;j<nNum;j++)
            {
                if(j == 0)
                {
                    qstr = mapParam[i].m_slistEnumValues.takeFirst();
                }
                else
                {
                    qstr=qstr+","+mapParam[i].m_slistEnumValues.takeFirst();
                }
            }
            param.setAttribute("valueList",qstr);
        }
        else if(mapParam[i].m_sValueType == "bool")
        {
            param.setAttribute("value",mapParam[i].m_sStringValue);
            param.setAttribute("valueRange","0,1");
        }
        parentNode->appendChild(param);
    }
}
QVector<int> ConfigFileManager::SplitXmlStringInt(QString xmlText)//将QString按逗号分割，并转为int类型，存放到QVector<int>
{
    QVector<int> vParam;
    QString value;
    QStringList list = xmlText.split(',');
    for (int i = 0; i < list.size(); ++i)
    {
        value = list.at(i);
        vParam.push_back(value.toInt());
    }
    return vParam;
}
QVector<float> ConfigFileManager::SplitXmlStringFloat(QString xmlText)//将QString按逗号分割，并转为float类型，存放到QVector<float>
{
    QVector<float> vParam;
    QString value;
    QStringList list = xmlText.split(',');
    for (int i = 0; i < list.size(); ++i)
    {
        value = list.at(i);
        vParam.push_back(value.toFloat());
    }
    return vParam;
}

