/*******************************************************
* @projectName   OMSystem
* @brief         用户配置文件类
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-05
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QPoint>

class AppConfig : public QObject
{
    Q_OBJECT

    QPoint m_mainWindowPoint;
    int m_pageSize;
    bool m_isEditable;
    bool m_isStatusBarVisible;
    bool m_isValid;

    bool restore();

public:

    explicit AppConfig(QObject *parent = nullptr);
    AppConfig(QPoint point,int m_pageSize,bool editable,bool sbVisable,QObject *parent = nullptr);

    bool store();
    QPoint mainWindowPoint();
    int pageSize();
    bool isEditable();
    bool isStatusBarVisible();
    bool isValid();
};

#endif // APPCONFIG_H
