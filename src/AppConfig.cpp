/*******************************************************
* @projectName   OMSystem
* @brief         用户配置文件类
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-05
*******************************************************/

#include "AppConfig.h"

#include <QFile>
#include <QDataStream>
#include <QApplication>

AppConfig::AppConfig(QObject *parent) : QObject(parent)
{
    m_isValid = restore();
}

AppConfig::AppConfig(QPoint point,int pageSize,bool editable,bool sbVisable,QObject *parent) : QObject(parent)
{
    m_mainWindowPoint = point;
    m_pageSize = pageSize;
    m_isEditable = editable;
    m_isStatusBarVisible = sbVisable;
    m_isValid = true;
}

/**
* @brief         加载app.config文件
* @param         None
* @return        加载是否成功
*/
bool AppConfig::restore()
{
    bool ret = true;
    QFile file(QApplication::applicationDirPath() + "/app.config");

    if( file.open(QIODevice::ReadOnly) )
    {
        QDataStream in(&file);

        in.setVersion(QDataStream::Qt_5_12);

        in >> m_mainWindowPoint;
        in >> m_pageSize;
        in >> m_isEditable;
        in >> m_isStatusBarVisible;

        file.close();
     }
     else
     {
        ret = false;
     }

     return ret;
}

/**
* @brief         将用户退出前的配置保存至app.config
* @param         None
* @return        保存是否成功
*/
bool AppConfig::store()
{
    bool ret = true;

    QFile file(QApplication::applicationDirPath() + "/app.config");

    if( file.open(QIODevice::WriteOnly) )
    {
        QDataStream out(&file);

        out.setVersion(QDataStream::Qt_5_12);

        out << m_mainWindowPoint;
        out << m_pageSize;
        out << m_isEditable;
        out << m_isStatusBarVisible;

        file.close();
        }
     else
     {
         ret = false;
     }

     return ret;
}

QPoint AppConfig::mainWindowPoint()
{
    return m_mainWindowPoint;
}

int AppConfig::pageSize()
{
    return m_pageSize;
}

bool AppConfig::isEditable()
{
    return m_isEditable;
}

bool AppConfig::isStatusBarVisible()
{
    return m_isStatusBarVisible;
}

bool AppConfig::isValid()
{
    return m_isValid;
}
