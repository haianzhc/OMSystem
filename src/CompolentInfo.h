/*******************************************************
* @projectName   OMSystem
* @brief         零件类，用于整合数据库的一行数据
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef COMPOLENTINFO_H
#define COMPOLENTINFO_H

#include <QObject>
#include <QVariant>
#include <QStringList>
#include <QDateTime>

class CompolentInfo : public QObject
{
    Q_OBJECT

    QString id;
    QString name;
    QString info;
    QString resourceUrl;
    QDateTime time;
    double para0;
    double para1;
    double para2;
    double para3;
    double para4;
    double para5;
    double para6;
    double para7;
    double para8;
    double para9;
    double para10;
    double para11;
    double para12;
    double para13;
    double para14;

public:

    const static QStringList ATTRIBUTE_LIST;

    explicit CompolentInfo(QObject* parent = nullptr);
    CompolentInfo(QString id, QString name,double para0, double para1,double para2,double para3,
                  double para4,double para5,double para6,double para7,double para8,double para9,
                  double para10,double para11,double para12,double para13, double para14,
                  QString info,QString resourceUrl,QDateTime time,QObject* parent = nullptr);
    CompolentInfo(const CompolentInfo& obj,QObject* parent = nullptr);
    CompolentInfo& operator= (const CompolentInfo& obj);

    bool setAttributeByString(const QString& attr,const QVariant& value);

    void setId(QString id);
    void setInfo(QString info);
    void setResourceUrl(QString resourceUrl);
    void setName(QString name);
    void setTime(QDateTime time);
    void setPara0(double para0);
    void setPara1(double para1);
    void setPara2(double para2);
    void setPara3(double para3);
    void setPara4(double para4);
    void setPara5(double para5);
    void setPara6(double para6);
    void setPara7(double para7);
    void setPara8(double para8);
    void setPara9(double para9);
    void setPara10(double para10);
    void setPara11(double para11);
    void setPara12(double para12);
    void setPara13(double para13);
    void setPara14(double para14);

    QString getId();
    QString getInfo();
    QString getResourceUrl();
    QString getName();
    QDateTime getTime();
    double getPara0();
    double getPara1();
    double getPara2();
    double getPara3();
    double getPara4();
    double getPara5();
    double getPara6();
    double getPara7();
    double getPara8();
    double getPara9();
    double getPara10();
    double getPara11();
    double getPara12();
    double getPara13();
    double getPara14();
};

#endif // COMPOLENTINFO_H
