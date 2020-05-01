/*******************************************************
* @projectName   OMSystem
* @brief         数据源类，用于与数据库建立连接，可直接操作数据库
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#include "DataSource.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>
#include <QVariantList>
#include <QVariant>
#include <QRandomGenerator>
#include <QSqlError>
#include <QDateTime>

DataSource::DataSource(QString usr,QString pwd,QObject *parent) : QObject(parent)
{
    username = usr;
    password = pwd;

    openDataBase();
}

/**
* @brief         打开数据库
* @param         None
* @return        数据库打开是否成功
*/
bool DataSource::openDataBase()
{
    bool ret = true;
    uint value = QRandomGenerator::global()->generate();

    if(QSqlDatabase::contains(QString::number(value)))
    {
       db = QSqlDatabase::database(QString::number(value));
    }
    else
    {
       db = QSqlDatabase::addDatabase("QMYSQL",QString::number(value));
       db.setDatabaseName("OMSystem");
       db.setHostName("localhost");
       db.setUserName(username);
       db.setPassword(password);
    }

    if(!db.open())
    {
        qDebug() << db.lastError().text();
        ret = false;
    }

    return ret;
}

/**
* @brief         向数据库中插入数据
* @param         obj:零件对象
* @return        插入是否成功
*/
bool DataSource::insert(CompolentInfo& obj)
{
    bool ret = true;

    QString fieldSql = "insert into compolent (";
    QString valueSql = ") values (";

    QStringList fieldList;
    QVariantList valueList;

    if(!obj.getName().isEmpty())
    {
        fieldList.append("name");
        valueList.append(QVariant(obj.getName()));
    }

    if(obj.getPara0() > -1000)
    {
        fieldList.append("para0");
        valueList.append(QVariant(obj.getPara0()));
    }

    if(obj.getPara1() > -1000)
    {
        fieldList.append("para1");
        valueList.append(QVariant(obj.getPara1()));
    }

    if(obj.getPara2() > -1000)
    {
        fieldList.append("para2");
        valueList.append(QVariant(obj.getPara2()));
    }

    if(obj.getPara3() > -1000)
    {
        fieldList.append("para3");
        valueList.append(QVariant(obj.getPara3()));
    }

    if(obj.getPara4() > -1000)
    {
        fieldList.append("para4");
        valueList.append(QVariant(obj.getPara4()));
    }

    if(obj.getPara5() > -1000)
    {
        fieldList.append("para5");
        valueList.append(QVariant(obj.getPara5()));
    }

    if(obj.getPara6() > -1000)
    {
        fieldList.append("para6");
        valueList.append(QVariant(obj.getPara6()));
    }

    if(obj.getPara7() > -1000)
    {
        fieldList.append("para7");
        valueList.append(QVariant(obj.getPara7()));
    }

    if(obj.getPara8() > -1000)
    {
        fieldList.append("para8");
        valueList.append(QVariant(obj.getPara8()));
    }

    if(obj.getPara9() > -1000)
    {
        fieldList.append("para9");
        valueList.append(QVariant(obj.getPara9()));
    }

    if(obj.getPara10() > -1000)
    {
        fieldList.append("para10");
        valueList.append(QVariant(obj.getPara10()));
    }

    if(obj.getPara11() > -1000)
    {
        fieldList.append("para11");
        valueList.append(QVariant(obj.getPara11()));
    }

    if(obj.getPara12() > -1000)
    {
        fieldList.append("para12");
        valueList.append(QVariant(obj.getPara12()));
    }

    if(obj.getPara13() > -1000)
    {
        fieldList.append("para13");
        valueList.append(QVariant(obj.getPara13()));
    }

    if(obj.getPara14() > -1000)
    {
        fieldList.append("para14");
        valueList.append(QVariant(obj.getPara14()));
    }

    if(!obj.getResourceUrl().isEmpty())
    {
        fieldList.append("resourceUrl");
        valueList.append(QVariant(obj.getResourceUrl()));
    }

    if(!obj.getInfo().isEmpty())
    {
        fieldList.append("info");
        valueList.append(QVariant(obj.getInfo()));
    }

    if(obj.getTime().isValid())
    {
        fieldList.append("time");
        valueList.append(QVariant(obj.getTime().toString("yyyy-MM-dd hh:mm:ss")));
    }

    int count = fieldList.count();

    if(count > 0)
    {
        for(int i = 0;i < count;i++)
        {
            fieldSql += (fieldList[i] + ",");
            valueSql += "?,";
        }

        fieldSql.remove(fieldSql.length() - 1,1);
        valueSql.replace(valueSql.length() - 1,1,")");

        QSqlQuery query(db);

        query.prepare(fieldSql + valueSql);

        for(int i = 0;i < count;i++)
        {
           query.addBindValue(valueList.at(i));
        }

        ret = query.exec();
    }

    return ret;
}

/**
* @brief         向数据库中插入数据集
* @param         list:零件对象集
* @return        插入是否成功
*/
bool DataSource::insert(QList<CompolentInfo>& list)
{
    bool ret = true;

    for(int i = 0;i < list.count();i++)
    {
        if(!insert(list[i]))
        {
            ret = false;
        }
    }

    return ret;
}

bool DataSource::update(CompolentInfo& obj)
{
    bool ret = true;

    QString preSql = "update compolent set info = '%1',para0 = '%2',para1 = '%3',para2 = '%4',para3 = '%5',\
                  para4 = '%6',para5 = '%7',para6 = '%8',para7 = '%9',para8 = '%10',para9 = '%11',\
                  para10 = '%12',para11 = '%13',para12 = '%14',para13 = '%15',para14 = '%16',name = '%17' \
                  where id = '%18'";

    QString sql = preSql.arg(obj.getInfo()).arg(obj.getPara0()).arg(obj.getPara1()).
            arg(obj.getPara2()).arg(obj.getPara3()).arg(obj.getPara4()).arg(obj.getPara5()).
            arg(obj.getPara6()).arg(obj.getPara7()).arg(obj.getPara8()).arg(obj.getPara9()).
            arg(obj.getPara10()).arg(obj.getPara11()).arg(obj.getPara12()).arg(obj.getPara13()).
            arg(obj.getPara14()).arg(obj.getName()).arg(obj.getId().toInt());

    QSqlQuery query(db);

    ret = query.exec(sql);

    return ret;
}

/**
* @brief         查找全部分页数据
* @param         currentPage:当前页
*                pageSize:每页显示数据量
* @return        查找是否成功
*/
bool DataSource::selectAllData(int currentPage,int pageSize)
{
    bool ret =  true;

    QSqlQuery query(db);
    QString sql = "select * from compolent limit " + QString::number((currentPage - 1) * pageSize) + "," +
                  QString::number(pageSize);

    if(query.exec(sql))
    {
        while(query.next())
        {
            CompolentInfo obj;

            if(parse(query,obj))
            {
                dataList.append(obj);
            }
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         根据id查找对应零件对象
* @param         obj:空零件对象
*                id:待查找id
* @return        查找是否成功
*/
bool DataSource::selectData(CompolentInfo& obj,int id)
{
    bool ret = true;

    QString sql = "select * from compolent where id = ";
    QSqlQuery query(db);

    if(query.exec(sql + QString::number(id)))
    {
        if(query.next())
        {
            ret = parse(query,obj);
        }
        else
        {
            ret = false;
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         根据给定条件查找对应分页的全部零件对象
* @param         condition:待查找条件
*                currentPage:当前页
*                pageSize:每页显示数据量
* @return        查找是否成功
*/
bool DataSource::selectAllData(const QString& condition,int currentPage,int pageSize)
{
    bool ret =  true;

    if(condition.isEmpty())
    {
        ret = selectAllData(currentPage,pageSize);
    }
    else
    {
        QSqlQuery query(db);
        QString sql = "select * from compolent where " + condition + " limit " +
                      QString::number((currentPage - 1) * pageSize) + "," + QString::number(pageSize);

        if(query.exec(sql))
        {
            while(query.next())
            {
                CompolentInfo obj;

                if(parse(query,obj))
                {
                    dataList.append(obj);
                }
            }
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

/**
* @brief         查找全部待导出数据
* @param         vList:待插入空链表
* @return        插入是否成功
*/
bool DataSource::selectExportData(QVariantList &vList)
{
    bool ret =  true;

    QSqlQuery query(db);
    QString sql = "select * from compolent";

    if(query.exec(sql))
    {
        while(query.next())
        {
            parse(query,vList);
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         根据条件查找全部待导出数据
* @param         condition:查找条件
*                vList:待插入空链表
* @return        插入是否成功
*/
bool DataSource::selectExportData(const QString& condition, QVariantList &vList)
{
    bool ret =  true;

    if(condition.isEmpty())
    {
        ret = selectExportData(vList);
    }
    else
    {
        QSqlQuery query(db);
        QString sql = "select * from compolent where " + condition;

        if(query.exec(sql))
        {
            while(query.next())
            {
                parse(query,vList);
            }
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

/**
* @brief         根据id删除对应数据
* @param         id:id值
* @return        是否删除成功
*/
bool DataSource::deleteDataById(int id)
{
    bool ret = true;

    QSqlQuery query(db);

    if(query.exec("delete from compolent where id = " + QString::number(id)))
    {
        dataList.clear();
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         清空数据表（此方法一旦调用，数据表将被清空。慎用！！！）
* @param         None
* @return        清空是否成功
*/
bool DataSource::clear()
{
    bool ret = true;

    QSqlQuery query(db);

    if(query.exec("delete from compolent"))
    {
        dataList.clear();
    }
    else
    {
        ret = false;
    }

    return ret;
}

bool DataSource::clear(const QString& condition)
{
    bool ret = true;

    if(condition.isEmpty())
    {
        ret = clear();
    }
    else
    {
        QSqlQuery query(db);

        if(query.exec("delete from compolent where " + condition))
        {
            dataList.clear();
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

/**
* @brief         查询数据量
* @param         None
* @return        数据总量
*/
int DataSource::count()
{
    QSqlQuery query(db);
    int count = 0;

    if(query.exec("select count(id) from compolent"))
    {
        if(query.next())
        {
            count = query.value(0).toInt();
        }
    }

    return count;
}

/**
* @brief         根据条件查询数据量
* @param         condition:查询条件
* @return        数据总量
*/
int DataSource::count(const QString& condition)
{
    int count = 0;

    if(condition.isEmpty())
    {
        count = this->count();
    }
    else
    {
        QSqlQuery query(db);
        QString sql = "select count(id) from compolent where " + condition;

        if(query.exec(sql))
        {
            if(query.next())
            {
                count = query.value(0).toInt();
            }
        }
    }

    return count;
}

QVariant DataSource::maxPara(const QString& para)
{
    QString sql = "select max(" + para + ") from compolent";
    QSqlQuery query(db);
    QVariant ret;

    if(query.exec(sql))
    {
        if(query.next())
        {
            ret = query.value(0);
        }
    }

    return ret;
}

QVariant DataSource::maxPara(const QString& para,const QString& condition)
{
    QVariant ret;

    if(condition.isEmpty())
    {
        ret = maxPara(para);
    }
    else
    {
        QString sql = "select max(" + para + ") from compolent where " + condition;
        QSqlQuery query(db);

        if(query.exec(sql))
        {
            if(query.next())
            {
                ret = query.value(0);
            }
        }
    }

    return ret;
}

QVariant DataSource::minPara(const QString& para)
{
    QString sql = "select min(" + para + ") from compolent";
    QSqlQuery query(db);
    QVariant ret;

    if(query.exec(sql))
    {
        if(query.next())
        {
            ret = query.value(0);
        }
    }

    return ret;
}

QVariant DataSource::minPara(const QString& para,const QString& condition)
{
    QVariant ret;

    if(condition.isEmpty())
    {
        ret = maxPara(para);
    }
    else
    {
        QString sql = "select min(" + para + ") from compolent where " + condition;
        QSqlQuery query(db);

        if(query.exec(sql))
        {
            if(query.next())
            {
                ret = query.value(0);
            }
        }
    }

    return ret;
}

/**
* @brief         将查询结果集封装为零件对象
* @param         query:查询结果集
*                obj:待封装零件对象
* @return        封装是否成功
*/
bool DataSource::parse(QSqlQuery& query, CompolentInfo& obj)
{
    bool ret = true;

    QString id = query.value("id").toString();
    QString name = query.value("name").toString();
    QString info = query.value("info").toString();
    QString resourceUrl = query.value("resourceUrl").toString();
    QDateTime time = query.value("time").toDateTime();
    double para0 = query.value("para0").toDouble(&ret);
    double para1 = query.value("para1").toDouble(&ret);
    double para2 = query.value("para2").toDouble(&ret);
    double para3 = query.value("para3").toDouble(&ret);
    double para4 = query.value("para4").toDouble(&ret);
    double para5 = query.value("para5").toDouble(&ret);
    double para6 = query.value("para6").toDouble(&ret);
    double para7 = query.value("para7").toDouble(&ret);
    double para8 = query.value("para8").toDouble(&ret);
    double para9 = query.value("para9").toDouble(&ret);
    double para10 = query.value("para10").toDouble(&ret);
    double para11 = query.value("para11").toDouble(&ret);
    double para12 = query.value("para12").toDouble(&ret);
    double para13 = query.value("para13").toDouble(&ret);
    double para14 = query.value("para14").toDouble(&ret);

    if( ret )
    {
        obj = CompolentInfo(id, name, para0, para1, para2, para3, para4, para5, para6,
                            para7, para8, para9, para10, para11, para12, para13, para14, info,resourceUrl,time);
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         将查询结果集封装为链表
* @param         query:查询结果集
*                obj:待封装链表
* @return        封装是否成功
*/
bool DataSource::parse(QSqlQuery& query,QVariantList &vList)
{
    bool ret = true;
    QVariantList aRowData;

    QString name = query.value("name").toString();
    double para0 = query.value("para0").toDouble(&ret);
    double para1 = query.value("para1").toDouble(&ret);
    double para2 = query.value("para2").toDouble(&ret);
    double para3 = query.value("para3").toDouble(&ret);
    double para4 = query.value("para4").toDouble(&ret);
    double para5 = query.value("para5").toDouble(&ret);
    double para6 = query.value("para6").toDouble(&ret);
    double para7 = query.value("para7").toDouble(&ret);
    double para8 = query.value("para8").toDouble(&ret);
    double para9 = query.value("para9").toDouble(&ret);
    double para10 = query.value("para10").toDouble(&ret);
    double para11 = query.value("para11").toDouble(&ret);
    double para12 = query.value("para12").toDouble(&ret);
    double para13 = query.value("para13").toDouble(&ret);
    double para14 = query.value("para14").toDouble(&ret);
    QString time = query.value("time").toDateTime().toString("yyyy-MM-dd hh:mm:ss");

    if(ret)
    {
        aRowData.append(QVariant(name));
        aRowData.append(QVariant(para0));
        aRowData.append(QVariant(para1));
        aRowData.append(QVariant(para2));
        aRowData.append(QVariant(para3));
        aRowData.append(QVariant(para4));
        aRowData.append(QVariant(para5));
        aRowData.append(QVariant(para6));
        aRowData.append(QVariant(para7));
        aRowData.append(QVariant(para8));
        aRowData.append(QVariant(para9));
        aRowData.append(QVariant(para10));
        aRowData.append(QVariant(para11));
        aRowData.append(QVariant(para12));
        aRowData.append(QVariant(para13));
        aRowData.append(QVariant(para14));
        aRowData.append(QVariant(time));

        vList.append(QVariant(aRowData));
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         取走数据集，并删除内置链表数据
* @param         None
* @return        零件对象链表
*/
QList<CompolentInfo> DataSource::fetchData()
{
    QList<CompolentInfo> ret = dataList;

    dataList.clear();

    return ret;
}

int DataSource::pageCount()
{
    return dataList.count();
}

bool DataSource::isOpened()
{
    return db.isOpen();
}
