/*******************************************************
* @projectName   OMSystem
* @brief         数据源类，用于与数据库建立连接，可直接操作数据库
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QVariantList>

#include "CompolentInfo.h"

class DataSource : public QObject
{
    Q_OBJECT

    QSqlDatabase db;
    QString username;
    QString password;
    QList<CompolentInfo> dataList;

    bool parse(QSqlQuery& query, CompolentInfo& obj);
    bool parse(QSqlQuery& query,QVariantList &vList);

public:

    DataSource(QString usr = "",QString pwd = "",QObject* parent = nullptr);

    bool openDataBase();
    bool isOpened();

    bool selectAllData(int currentPage = 1,int pageSize = 20);
    bool selectAllData(const QString& condition,int currentPage = 1,int pageSize = 20);
    bool selectExportData(QVariantList& vList);
    bool selectExportData(const QString& condition,QVariantList& vList);
    bool selectData(CompolentInfo& obj,int id);

    bool deleteDataById(int id);

    int count();
    int count(const QString& condition);

    QVariant maxPara(const QString& para);
    QVariant maxPara(const QString& para,const QString& condition);
    QVariant minPara(const QString& para);
    QVariant minPara(const QString& para,const QString& condition);

    bool clear();
    bool clear(const QString& condition);

    bool insert(CompolentInfo& obj);
    bool insert(QList<CompolentInfo>& list);

    bool update(CompolentInfo& obj);

    int pageCount();
    QList<CompolentInfo> fetchData();
};

#endif // DATASOURCE_H
