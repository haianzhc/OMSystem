/***********************************************
* @projectName   OMSystem
* @brief         自定义系统托盘类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#pragma execution_character_set("utf-8")

#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QWidget>
#include <QSystemTrayIcon>

class SysTray : public QSystemTrayIcon
{
    Q_OBJECT

    QWidget* m_parent;

    void initSysTemTray();
    void addSysTrayMenu();

public:

    explicit SysTray(QWidget *parent = nullptr);

public slots:

    void onIconActivated(QSystemTrayIcon::ActivationReason reason);

};

#endif // SYSTRAY_H
