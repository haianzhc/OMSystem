/*******************************************************
* @projectName   OMSystem
* @brief         模型类，用于整合封装好的数据与用户交互
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#include "CompolentInfoModel.h"
#include "FileTool.h"

#include <QStandardItem>
#include <QVariant>
#include <QHeaderView>

CompolentInfoModel::CompolentInfoModel(QObject* parent) : QObject(parent)
{
}

/**
* @brief         向模型中添加数据
* @param         obj:零件对象
* @return        添加是否成功
*/
bool CompolentInfoModel::add(CompolentInfo obj)
{
    QString dirpath = obj.getResourceUrl() + "/image/";
    QStringList nameFilters,imgNames;
    nameFilters << "*.jpg" << "*.png";
    FileTool::findFilesInDir(dirpath,nameFilters,imgNames);

    QString path = "";

    if(!imgNames.isEmpty())
    {
        path = imgNames[0];
    }

    QStandardItem* root = m_model.invisibleRootItem();
    QStandardItem* item0 = new QStandardItem();
    QStandardItem* item1 = new QStandardItem();
    QStandardItem* item2 = new QStandardItem();
    QStandardItem* item3 = new QStandardItem();
    QStandardItem* item4 = new QStandardItem();
    QStandardItem* item5 = new QStandardItem();
    QStandardItem* item6 = new QStandardItem();
    QStandardItem* item7 = new QStandardItem();
    QStandardItem* item8 = new QStandardItem();
    QStandardItem* item9 = new QStandardItem();
    QStandardItem* item10 = new QStandardItem();
    QStandardItem* item11 = new QStandardItem();
    QStandardItem* item12 = new QStandardItem();
    QStandardItem* item13 = new QStandardItem();
    QStandardItem* item14 = new QStandardItem();
    QStandardItem* item15 = new QStandardItem();
    QStandardItem* item16 = new QStandardItem();
    QStandardItem* item17 = new QStandardItem();
    QStandardItem* item18 = new QStandardItem();
    bool ret = true;

    if( m_model.rowCount() == 0 )
    {
        QStringList list;

        list.append("ID");
        list.append("图片");
        list.append("名称");
        list.append("参数0");
        list.append("参数1");
        list.append("参数2");
        list.append("参数3");
        list.append("参数4");
        list.append("参数5");
        list.append("参数6");
        list.append("参数7");
        list.append("参数8");
        list.append("参数9");
        list.append("参数10");
        list.append("参数11");
        list.append("参数12");
        list.append("参数13");
        list.append("参数14");
        list.append("时间");

        m_model.setHorizontalHeaderLabels(list);
    }

    if( (root != nullptr) && (item0 != nullptr) && (item1 != nullptr) && (item2 != nullptr)
            && (item3 != nullptr)&& (item4 != nullptr) && (item5 != nullptr)&& (item6 != nullptr)
            && (item7 != nullptr) && (item8 != nullptr) &&(item9 != nullptr) && (item10 != nullptr)
            && (item11 != nullptr) && (item12 != nullptr) && (item13 != nullptr) && (item14 != nullptr)
            && (item15 != nullptr) && (item16 != nullptr) && (item17 != nullptr) && (item18 != nullptr))
    {
        item0->setData(obj.getId(), Qt::DisplayRole);
        item1->setData(path, Qt::DisplayRole);
        item2->setData(obj.getName(), Qt::DisplayRole);
        item3->setData(obj.getPara0(), Qt::DisplayRole);
        item4->setData(obj.getPara1(), Qt::DisplayRole);
        item5->setData(obj.getPara2(), Qt::DisplayRole);
        item6->setData(obj.getPara3(), Qt::DisplayRole);
        item7->setData(obj.getPara4(), Qt::DisplayRole);
        item8->setData(obj.getPara5(), Qt::DisplayRole);
        item9->setData(obj.getPara6(), Qt::DisplayRole);
        item10->setData(obj.getPara7(), Qt::DisplayRole);
        item11->setData(obj.getPara8(), Qt::DisplayRole);
        item12->setData(obj.getPara9(), Qt::DisplayRole);
        item13->setData(obj.getPara10(), Qt::DisplayRole);
        item14->setData(obj.getPara11(), Qt::DisplayRole);
        item15->setData(obj.getPara12(), Qt::DisplayRole);
        item16->setData(obj.getPara13(), Qt::DisplayRole);
        item17->setData(obj.getPara14(), Qt::DisplayRole);
        item18->setData(obj.getTime().toString("yyyy-MM-dd hh:mm:ss"), Qt::DisplayRole);

        item0->setEditable(false);
        item1->setEditable(false);
        item2->setEditable(false);
        item3->setEditable(false);
        item4->setEditable(false);
        item5->setEditable(false);
        item6->setEditable(false);
        item7->setEditable(false);
        item8->setEditable(false);
        item9->setEditable(false);
        item10->setEditable(false);
        item11->setEditable(false);
        item12->setEditable(false);
        item13->setEditable(false);
        item14->setEditable(false);
        item15->setEditable(false);
        item16->setEditable(false);
        item17->setEditable(false);
        item18->setEditable(false);

        item0->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item2->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item3->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item5->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item6->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item7->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item8->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item9->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item10->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item11->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item12->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item13->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item14->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item15->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item16->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item17->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item18->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        int newRow = count();

        root->setChild(newRow, 0, item0);
        root->setChild(newRow, 1, item1);
        root->setChild(newRow, 2, item2);
        root->setChild(newRow, 3, item3);
        root->setChild(newRow, 4, item4);
        root->setChild(newRow, 5, item5);
        root->setChild(newRow, 6, item6);
        root->setChild(newRow, 7, item7);
        root->setChild(newRow, 8, item8);
        root->setChild(newRow, 9, item9);
        root->setChild(newRow, 10, item10);
        root->setChild(newRow, 11, item11);
        root->setChild(newRow, 12, item12);
        root->setChild(newRow, 13, item13);
        root->setChild(newRow, 14, item14);
        root->setChild(newRow, 15, item15);
        root->setChild(newRow, 16, item16);
        root->setChild(newRow, 17, item17);
        root->setChild(newRow, 18, item18);
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         向模型中添加数据链表
* @param         list:零件对象链表
* @return        添加是否成功
*/
bool CompolentInfoModel::add(QList<CompolentInfo> list)
{
    bool ret = true;

    for(int i=0; i<list.count(); i++)
    {
        ret = ret && add(list[i]);
    }

    return ret;
}

/**
* @brief         根据行号删除模型中数据
* @param         i:行号
* @return        删除是否成功
*/
bool CompolentInfoModel::remove(int i)
{
    bool ret = true;

    if( (0 <= i) && (i < count()) )
    {
        m_model.removeRow(i);
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         清空模型中数据
* @param         None
*/
void CompolentInfoModel::clear()
{
    m_model.clear();
}

/**
* @brief         根据行号获取对应id
* @param         i:行号
* @return        i:id值
*/
int CompolentInfoModel::getItemId(int i)
{
    int ret = -1;

    if( (0 <= i) && (i < count()) )
    {
        QModelIndex index = m_model.index(i, 0, QModelIndex());
        QVariant vid = index.data(Qt::DisplayRole);
        ret = vid.toInt();
    }

    return ret;
}

/**
* @brief         获取模型中的数据数量
* @param         None
* @return        数据量
*/
int CompolentInfoModel::count()
{
    return m_model.rowCount();
}

void CompolentInfoModel::setView(QTableView*& view)
{
    view->setModel(&m_model);
    view->setItemDelegate(&m_delegate);

    view->hideColumn(0);
    view->setColumnWidth(1,200);
    view->setColumnWidth(18,200);
}
