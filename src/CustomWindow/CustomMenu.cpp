/***********************************************
* @projectName   OMSystem
* @brief         自定义菜单类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#include "CustomMenu.h"

CustomMenu::CustomMenu(QWidget *parent) : QMenu(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
}

void CustomMenu::addCustomMenu(const QString& qsName, const QString& icon, const QString& zhName)
{
    QAction *pAction = addAction(QIcon(icon), zhName);
    m_menuActionMap.insert(qsName, pAction);
}

QAction* CustomMenu::getAction(const QString& qsName)
{
    return m_menuActionMap[qsName];
}
