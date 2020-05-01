/*******************************************************
* @projectName   OMSystem
* @brief         零件类，用于整合数据库的一行数据
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/


#include "CompolentInfo.h"

const QStringList CompolentInfo::ATTRIBUTE_LIST = {"name","para0","para1","para2","para3","para4",
                                                   "para5","para6","para7","para8","para9","para10",
                                                   "para11","para12","para13","para14","time"};

CompolentInfo::CompolentInfo(QObject* parent) : QObject(parent)
{
    id = "";
    name = "";
    info = "";
    resourceUrl = "";
    para0 = -1000;
    para1 = -1000;
    para2 = -1000;
    para3 = -1000;
    para4 = -1000;
    para5 = -1000;
    para6 = -1000;
    para7 = -1000;
    para8 = -1000;
    para9 = -1000;
    para10 = -1000;
    para11 = -1000;
    para12 = -1000;
    para13 = -1000;
    para14 = -1000;
}

CompolentInfo::CompolentInfo(QString id, QString name,double para0, double para1,double para2,double para3,
                             double para4,double para5,double para6,double para7,double para8,double para9,
                             double para10,double para11,double para12,double para13, double para14,
                             QString info,QString resourceUrl,QDateTime time,QObject* parent): QObject(parent)
{
    this->id = id;
    this->info = info;
    this->name = name;
    this->resourceUrl = resourceUrl;
    this->time = time;
    this->para0 = para0;
    this->para1 = para1;
    this->para2 = para2;
    this->para3 = para3;
    this->para4 = para4;
    this->para5 = para5;
    this->para6 = para6;
    this->para7 = para7;
    this->para8 = para8;
    this->para9 = para9;
    this->para10 = para10;
    this->para11 = para11;
    this->para12 = para12;
    this->para13 = para13;
    this->para14 = para14;
}

CompolentInfo::CompolentInfo(const CompolentInfo& obj,QObject* parent) : QObject(parent)
{
    this->id = obj.id;
    this->info = obj.info;
    this->name = obj.name;
    this->resourceUrl = obj.resourceUrl;
    this->time = obj.time;
    this->para0 = obj.para0;
    this->para1 = obj.para1;
    this->para2 = obj.para2;
    this->para3 = obj.para3;
    this->para4 = obj.para4;
    this->para5 = obj.para5;
    this->para6 = obj.para6;
    this->para7 = obj.para7;
    this->para8 = obj.para8;
    this->para9 = obj.para9;
    this->para10 = obj.para10;
    this->para11 = obj.para11;
    this->para12 = obj.para12;
    this->para13 = obj.para13;
    this->para14 = obj.para14;
}

CompolentInfo& CompolentInfo::operator= (const CompolentInfo& obj)
{
    if( this != &obj )
    {
        this->id = obj.id;
        this->info = obj.info;
        this->resourceUrl = obj.resourceUrl;
        this->name = obj.name;
        this->time = obj.time;
        this->para0 = obj.para0;
        this->para1 = obj.para1;
        this->para2 = obj.para2;
        this->para3 = obj.para3;
        this->para4 = obj.para4;
        this->para5 = obj.para5;
        this->para6 = obj.para6;
        this->para7 = obj.para7;
        this->para8 = obj.para8;
        this->para9 = obj.para9;
        this->para10 = obj.para10;
        this->para11 = obj.para11;
        this->para12 = obj.para12;
        this->para13 = obj.para13;
        this->para14 = obj.para14;
    }

    return *this;
}

/**
* @brief         根据属性名称设置对应属性
* @param         attr:属性名
*                value:属性值
* @return        设置是否成功
*/
bool CompolentInfo::setAttributeByString(const QString& attr,const QVariant& value)
{
    bool ret = true;

    if(ATTRIBUTE_LIST.contains(attr))
    {
        if("name" == attr && !value.isNull())
            name = value.toString();

        if("info" == attr && !value.isNull())
            info = value.toString();

        if("para0" == attr && !value.isNull())
            para0 = value.toDouble(&ret);

        if("para1" == attr && !value.isNull())
            para1 = value.toDouble(&ret);

        if("para2" == attr && !value.isNull())
            para2 = value.toDouble(&ret);

        if("para3" == attr && !value.isNull())
            para3 = value.toDouble(&ret);

        if("para4" == attr && !value.isNull())
            para4 = value.toDouble(&ret);

        if("para5" == attr && !value.isNull())
            para5 = value.toDouble(&ret);

        if("para6" == attr && !value.isNull())
            para6 = value.toDouble(&ret);

        if("para7" == attr && !value.isNull())
            para7 = value.toDouble(&ret);

        if("para8" == attr && !value.isNull())
            para8 = value.toDouble(&ret);

        if("para9" == attr && !value.isNull())
            para9 = value.toDouble(&ret);

        if("para10" == attr && !value.isNull())
            para10 = value.toDouble(&ret);

        if("para11" == attr && !value.isNull())
            para11 = value.toDouble(&ret);

        if("para12" == attr && !value.isNull())
            para12 = value.toDouble(&ret);

        if("para13" == attr && !value.isNull())
            para13 = value.toDouble(&ret);

        if("para14" == attr && !value.isNull())
            para14 = value.toDouble(&ret);

        if("time" == attr && !value.isNull())
            time = value.toDateTime();
    }
    else
    {
        ret = false;
    }

    return ret;
}

void CompolentInfo::setId(QString id)
{
    this->id = id;
}

void CompolentInfo::setInfo(QString info)
{
    this->info = info;
}

void CompolentInfo::setResourceUrl(QString resourceUrl)
{
    this->resourceUrl = resourceUrl;
}

void CompolentInfo::setName(QString name)
{
    this->name = name;
}

void CompolentInfo::setTime(QDateTime time)
{
    this->time = time;
}

void CompolentInfo::setPara0(double para0)
{
    this->para0 = para0;
}

void CompolentInfo::setPara1(double para1)
{
    this->para1 = para1;
}

void CompolentInfo::setPara2(double para2)
{
    this->para2 = para2;
}

void CompolentInfo::setPara3(double para3)
{
    this->para3 = para3;
}

void CompolentInfo::setPara4(double para4)
{
    this->para4 = para4;
}

void CompolentInfo::setPara5(double para5)
{
    this->para5 = para5;
}

void CompolentInfo::setPara6(double para6)
{
    this->para6 = para6;
}

void CompolentInfo::setPara7(double para7)
{
    this->para7 = para7;
}

void CompolentInfo::setPara8(double para8)
{
    this->para8 = para8;
}

void CompolentInfo::setPara9(double para9)
{
    this->para9 = para9;
}

void CompolentInfo::setPara10(double para10)
{
    this->para10 = para10;
}

void CompolentInfo::setPara11(double para11)
{
    this->para11 = para11;
}

void CompolentInfo::setPara12(double para12)
{
    this->para12 = para12;
}

void CompolentInfo::setPara13(double para13)
{
    this->para13 = para13;
}

void CompolentInfo::setPara14(double para14)
{
    this->para14 = para14;
}

QString CompolentInfo::getId()
{
    return id;
}

QString CompolentInfo::getName()
{
    return name;
}

QString CompolentInfo::getInfo()
{
    return info;
}

QString CompolentInfo::getResourceUrl()
{
    return resourceUrl;
}

QDateTime CompolentInfo::getTime()
{
    return time;
}

double CompolentInfo::getPara0()
{
    return para0;
}

double CompolentInfo::getPara1()
{
    return para1;
}

double CompolentInfo::getPara2()
{
    return para2;
}

double CompolentInfo::getPara3()
{
    return para3;
}

double CompolentInfo::getPara4()
{
    return para4;
}

double CompolentInfo::getPara5()
{
    return para5;
}

double CompolentInfo::getPara6()
{
    return para6;
}

double CompolentInfo::getPara7()
{
    return para7;
}

double CompolentInfo::getPara8()
{
    return para8;
}

double CompolentInfo::getPara9()
{
    return para9;
}

double CompolentInfo::getPara10()
{
    return para10;
}

double CompolentInfo::getPara11()
{
    return para11;
}

double CompolentInfo::getPara12()
{
    return para12;
}

double CompolentInfo::getPara13()
{
    return para13;
}

double CompolentInfo::getPara14()
{
    return para14;
}
