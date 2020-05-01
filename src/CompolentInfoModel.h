/*******************************************************
* @projectName   OMSystem
* @brief         模型类，用于整合封装好的数据与用户交互
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef COMPOLENTINFOMODEL_H
#define COMPOLENTINFOMODEL_H

#include <QObject>
#include <QStandardItem>
#include <QTableView>
#include <QList>

#include "CompolentInfo.h"
#include "CompolentInfoDelegate.h"

class CompolentInfoModel : public QObject
{
    Q_OBJECT

    QStandardItemModel m_model;
    CompolentInfoDelegate m_delegate;

public:

    explicit CompolentInfoModel(QObject *parent = nullptr);
    bool add(CompolentInfo obj);
    bool add(QList<CompolentInfo> list);
    bool remove(int i);
    int getItemId(int i);
    int count();
    void clear();
    void setView(QTableView*& view);

};

#endif // COMPOLENTINFOMODEL_H
