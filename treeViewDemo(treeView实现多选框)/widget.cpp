#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_publicIconMap[TREE_ITEM_ICON_Project] = QIcon(QStringLiteral(":/treeIcon/res_treeItemIcon/Project.png"));
    m_publicIconMap[TREE_ITEM_ICON_folder] = QIcon(QStringLiteral(":/treeIcon/res_treeItemIcon/folder.png"));
    m_publicIconMap[TREE_ITEM_ICON_folderAnsys] = QIcon(QStringLiteral(":/treeIcon/res_treeItemIcon/folder-ansys.png"));
    m_publicIconMap[TREE_ITEM_ICON_TdmsGroup] = QIcon(QStringLiteral(":/treeIcon/res_treeItemIcon/group.png"));
    m_publicIconMap[TREE_ITEM_ICON_TdmsChannel] = QIcon(QStringLiteral(":/treeIcon/res_treeItemIcon/channel.png"));
    m_publicIconMap[TREE_ITEM_ICON_folderOriginal] = QIcon(QStringLiteral(":/treeIcon/res_treeItemIcon/folder_original.png"));
    m_publicIconMap[TREE_ITEM_ICON_DataItem] = QIcon(QStringLiteral(":/treeIcon/res_treeItemIcon/dataItem.png"));
    initTree();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initTree()
{


    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("项目名")<<QStringLiteral("信息"));
    //第一行 1
    QStandardItem* itemProject = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Project")],QStringLiteral("项目"));
    model->appendRow(itemProject);
    model->setItem(model->indexFromItem(itemProject).row(),1,new QStandardItem(QStringLiteral("项目信息说明")));
    //1.1
    QStandardItem* itemFolder = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_folder")],QStringLiteral("文件夹1"));
    itemProject->appendRow(itemFolder);
    itemProject->setChild(itemFolder->index().row(),1,new QStandardItem(QStringLiteral("信息说明")));
    //1.2
    itemFolder = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_folder")],QStringLiteral("文件夹2"));
    itemProject->appendRow(itemFolder);
    for(int i=0;i<5;++i){
        QStandardItem* itemgroup = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_group")],QStringLiteral("组%1").arg(i+1));
        itemFolder->appendRow(itemgroup);
        for(int j=0;j<(i+1);++j){
            QStandardItem* itemchannel = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_channel")],QStringLiteral("频道%1").arg(j+1));
            itemgroup->appendRow(itemchannel);
            itemgroup->setChild(itemchannel->index().row(),1,new QStandardItem(QStringLiteral("频道%1信息说明").arg(j+1)));
        }
    }
    itemProject->setChild(itemFolder->index().row(),1,new QStandardItem(QStringLiteral("文件夹2信息说明")));
   //2
    itemProject = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_Project")],QStringLiteral("项目2"));
    model->appendRow(itemProject);
   //2.n
    for(int i =0;i<3;++i)
    {
        itemFolder = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_folder")],QStringLiteral("项目2文件夹%1").arg(i+1));
        itemFolder->setCheckable(true);
        itemFolder->setTristate(true);
        QStandardItem* itemFolderDes = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_group")],QStringLiteral("文件夹%1组").arg(i+1));
        itemProject->appendRow(itemFolder);
        itemProject->setChild(itemFolder->index().row(),1,itemFolderDes);
        for(int j=0;j<i+1;++j)
        {
             QStandardItem* item = new QStandardItem(m_publicIconMap[QStringLiteral("treeItem_dataItem")],QStringLiteral("项目%1").arg(j+1));
             item->setCheckable(true);
             itemFolder->appendRow(item);

        }
    }
    //关联项目属性改变的信号和槽
    connect(model,&QStandardItemModel::itemChanged,this,&Widget::treeItemChanged);
    //connect(model,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(treeItemChanged(QStandardItem*)));
    ui->treeView->setModel(model);



}

//QStandardItem* getCurrentSelItem();

void Widget::on_pushButton_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->treeView->model());
    QModelIndex index = ui->treeView->currentIndex();
    QStandardItem* item = model->itemFromIndex(index);

    ui->label->setText(QStringLiteral("当前选中：%1\nrow:%2,column:%3\n最左边节点：%4").arg(item->text())
                       .arg(index.row()).arg(index.column())
                       .arg(index.sibling(index.row(),0).data().toString()));
}

///
/// \brief 获取根部节点，即从属关系的可显示最上级，与invisibleRootItem不同
/// \param item
/// \return
///
QStandardItem* Widget::getTopParent(QStandardItem* item)
{
    QStandardItem* secondItem = item;
    while(item->parent()!= 0)
    {
        secondItem = item->parent();
        item = secondItem;
    }
    if(secondItem->index().column() != 0)
    {
         QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->treeView->model());
         secondItem = model->itemFromIndex(secondItem->index().sibling(secondItem->index().row(),0));
    }
    return secondItem;
}
QModelIndex Widget::getTopParent(QModelIndex itemIndex)
{
    QModelIndex secondItem = itemIndex;
    while(itemIndex.parent().isValid())
    {
        secondItem = itemIndex.parent();
        itemIndex = secondItem;
    }
    if(secondItem.column() != 0)
    {
         secondItem = secondItem.sibling(secondItem.row(),0);
    }
    return secondItem;
}
void Widget::on_pushButton_2_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->treeView->model());
    QModelIndex currentIndex = ui->treeView->currentIndex();
    QStandardItem* currentItem = model->itemFromIndex(currentIndex);
    ui->label_2->setText(getTopParent(currentItem)->text());
}

void Widget::on_treeView_clicked(const QModelIndex &index)
{
    QString str;
    str += QStringLiteral("当前选中：%1\nrow:%2,column:%3\n").arg(index.data().toString())
            .arg(index.row()).arg(index.column());
    str += QStringLiteral("父级：%1\n").arg(index.parent().data().toString());
    //兄弟节点测试
    QString name,info;
    if(index.column() == 0)
    {
        name = index.data().toString();
        info = index.sibling(index.row(),1).data().toString();
    }
    else
    {
        name = index.sibling(index.row(),0).data().toString();
        info = index.data().toString();
    }
    str += QStringLiteral("名称：%1\n信息：%2\n").arg(name).arg(info);
    //寻找顶层
    QString top = getTopParent(index).data().toString();
    str += QStringLiteral("顶层节点名：%1\n").arg(top);
    ui->label_realTime->setText(str);
}

void Widget::on_pushButton_3_clicked()
{
    QStandardItemModel* model = static_cast<QStandardItemModel*>(ui->treeView->model());
    ui->label_3->setText(QStringLiteral("invisibleRootItem的rowCount:%1").arg(model->invisibleRootItem()->rowCount()));
}

void Widget::on_treeWidget_clicked(const QModelIndex &index)
{

}

void Widget::treeItemChanged(QStandardItem * item)
{
    if(item == nullptr)
        return;
    if(item->isCheckable())
    {
        //如果条目是存在复选框的，那么就进行下面的操作
        Qt::CheckState state = item->checkState();//获取当前的选择状态
        if(item->isTristate())
        {
            //如果条目是三态的，说明可以对子目录进行全选和全不选的设置
            if(state != Qt::PartiallyChecked)
            {
                //当前是选中状态，需要对其子项目进行全选
                treeItem_checkAllChild(item,state == Qt::Checked ? true : false);
            }
        }
        else
        {
            //说明是两态的，两态会对父级的三态有影响
            //判断兄弟节点的情况
            treeItem_CheckChildChanged(item);
        }
    }
}
///
/// \brief 递归设置所有的子项目为全选或全不选状态
/// \param item 当前项目
/// \param check true时为全选，false时全不选
///
void Widget::treeItem_checkAllChild(QStandardItem * item, bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}
void Widget::treeItem_checkAllChild_recursion(QStandardItem * item,bool check)
{
    if(item == nullptr)
        return;
    int rowCount = item->rowCount();
    for(int i=0;i<rowCount;++i)
    {
        QStandardItem* childItems = item->child(i);
        treeItem_checkAllChild_recursion(childItems,check);
    }
    if(item->isCheckable())
        item->setCheckState(check ? Qt::Checked : Qt::Unchecked);
}


///
/// \brief 测量兄弟节点的情况，如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
/// \param item
/// \return 如果都选中返回Qt::Checked，都不选中Qt::Unchecked,不完全选中返回Qt::PartiallyChecked
///
Qt::CheckState Widget::checkSibling(QStandardItem * item)
{
    //先通过父节点获取兄弟节点
    QStandardItem * parent = item->parent();
    if(nullptr == parent)
        return item->checkState();
    int brotherCount = parent->rowCount();
    int checkedCount(0),unCheckedCount(0);
    Qt::CheckState state;
    for(int i=0;i<brotherCount;++i)
    {
        QStandardItem* siblingItem = parent->child(i);
        state = siblingItem->checkState();
        if(Qt::PartiallyChecked == state)
            return Qt::PartiallyChecked;
        else if(Qt::Unchecked == state)
            ++unCheckedCount;
        else
            ++checkedCount;
        if(checkedCount>0 && unCheckedCount>0)
            return Qt::PartiallyChecked;
    }
    if(unCheckedCount>0)
        return Qt::Unchecked;
    return Qt::Checked;
}
///
/// \brief 根据子节点的改变，更改父节点的选择情况
/// \param item
///
void Widget::treeItem_CheckChildChanged(QStandardItem * item)
{
    if(nullptr == item)
        return;
    Qt::CheckState siblingState = checkSibling(item);
    QStandardItem * parentItem = item->parent();
    if(nullptr == parentItem)
        return;
    if(Qt::PartiallyChecked == siblingState)
    {
        if(parentItem->isCheckable() && parentItem->isTristate())
            parentItem->setCheckState(Qt::PartiallyChecked);
    }
    else if(Qt::Checked == siblingState)
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Checked);
    }
    else
    {
        if(parentItem->isCheckable())
            parentItem->setCheckState(Qt::Unchecked);
    }
    treeItem_CheckChildChanged(parentItem);
}






/////
///// \brief 判断当前项目其子项目是否全选
///// \param item 当前项目
///// \return
/////
//bool Widget::isChildAllCheck(QStandardItem * item)
//{
//    if(item == nullptr)
//        return false;
//    int rowCount = item->rowCount();
//    for(int i=0;i<rowCount;++i)
//    {
//        QStandardItem* childItems = item->child(i);
//        bool ischeck = isChildAllCheck_recursion(childItems);
//        if(!ischeck)
//            return false;
//    }
//    return true;
//}
//bool Widget::isChildAllCheck_recursion(QStandardItem * item)
//{
//    if(item == nullptr)
//        return false;
//    int rowCount = item->rowCount();
//    for(int i=0;i<rowCount;++i)
//    {
//        QStandardItem* childItems = item->child(i);
//        bool ischeck = isChildAllCheck_recursion(childItems);
//        if(!ischeck)
//            return false;
//    }
//    Qt::CheckState state = item->checkState();//获取当前的选择状态
//    return ((state == Qt::Checked) ? true : false);
//}

//bool Widget::isChildAllunCheck(QStandardItem * item)
//{
//    if(item == nullptr)
//        return false;
//    int rowCount = item->rowCount();
//    for(int i=0;i<rowCount;++i)
//    {
//        QStandardItem* childItems = item->child(i);
//        bool isuncheck = isChildAllunCheck_recursion(childItems);
//        if(!isuncheck)
//            return false;
//    }
//    return true;
//}

//bool Widget::isChildAllunCheck_recursion(QStandardItem * item)
//{
//    if(item == nullptr)
//        return false;
//    int rowCount = item->rowCount();
//    for(int i=0;i<rowCount;++i)
//    {
//        QStandardItem* childItems = item->child(i);
//        bool isuncheck = isChildAllunCheck_recursion(childItems);
//        if(!isuncheck)
//            return false;
//    }
//    Qt::CheckState state = item->checkState();//获取当前的选择状态
//    return ((state == Qt::Unchecked) ? true : false);
//}
