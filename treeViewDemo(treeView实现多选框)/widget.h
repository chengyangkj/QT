#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMap>
#include <QIcon>
#include <QStandardItemModel>
//以下是图标的宏设定
#ifndef TREE_ITEM_ICON_Project
#define TREE_ITEM_ICON_Project QStringLiteral("treeItem_Project")
#endif
#ifndef TREE_ITEM_ICON_folder
#define TREE_ITEM_ICON_folder QStringLiteral("treeItem_folder")
#endif
#ifndef TREE_ITEM_ICON_folderOriginal
#define TREE_ITEM_ICON_folderOriginal QStringLiteral("treeItem_folder-ansys")
#endif
#ifndef TREE_ITEM_ICON_folderAnsys
#define TREE_ITEM_ICON_folderAnsys QStringLiteral("treeItem_folder-ansys")
#endif
#ifndef TREE_ITEM_ICON_TdmsGroup
#define TREE_ITEM_ICON_TdmsGroup QStringLiteral("treeItem_group")
#endif
#ifndef TREE_ITEM_ICON_TdmsChannel
#define TREE_ITEM_ICON_TdmsChannel QStringLiteral("treeItem_channel")
#endif
#ifndef TREE_ITEM_ICON_DataItem
#define TREE_ITEM_ICON_DataItem QStringLiteral("treeItem_dataItem")
#endif


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void initTree();
private slots:
    void on_pushButton_clicked();
    //QStandardItem* getCurrentSelItem();
    void on_pushButton_2_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    QStandardItem* getTopParent(QStandardItem* item);
    QModelIndex getTopParent(QModelIndex itemIndex);
    void on_pushButton_3_clicked();

    void on_treeWidget_clicked(const QModelIndex &index);
    void treeItemChanged(QStandardItem * item);
    void treeItem_checkAllChild(QStandardItem * item,bool check = true);
    void treeItem_checkAllChild_recursion(QStandardItem * item,bool check = true);
    Qt::CheckState checkSibling(QStandardItem * item);
    void treeItem_CheckChildChanged(QStandardItem * item);

//    bool isChildAllCheck(QStandardItem * item);
//    bool isChildAllCheck_recursion(QStandardItem * item);
//    bool isChildAllunCheck(QStandardItem * item);
//    bool isChildAllunCheck_recursion(QStandardItem * item);


private:
    Ui::Widget *ui;
    QMap<QString,QIcon> m_publicIconMap;///< 存放公共图标
};

#endif // WIDGET_H
