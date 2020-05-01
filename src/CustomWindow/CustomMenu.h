/***********************************************
* @projectName   OMSystem
* @brief         自定义菜单类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#pragma execution_character_set("utf-8")

#ifndef CUSTOMMENU_H
#define CUSTOMMENU_H

#include <QMenu>
#include <QMap>

class CustomMenu : public QMenu
{
    Q_OBJECT

    QMap<QString, QAction*> m_menuActionMap;

public:

    CustomMenu(QWidget *parent = nullptr);

    void addCustomMenu(const QString& text, const QString& icon, const QString& zhName);
    QAction* getAction(const QString& qsName);

};

#endif // CUSTOMMENU_H
