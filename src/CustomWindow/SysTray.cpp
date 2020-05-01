/***********************************************
* @projectName   OMSystem
* @brief         自定义系统托盘类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#include "SysTray.h"
#include "CustomMenu.h"
#include "FileTool.h"

#define TRAY_DATA	      ":/res/pic/whole.png"
#define TRAY_ICON	      ":/res/pic/logo/All_logo32.ico"
#define CLOSE_MENU		  ":/res/pic/menu/fatalerror.png"

SysTray::SysTray(QWidget *parent) : QSystemTrayIcon(parent),m_parent(parent)
{
    initSysTemTray();
    show();
}

void SysTray::initSysTemTray()
{
    setToolTip("西安交通大学光学测量系统");
    setIcon(QIcon(TRAY_ICON));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onIconActivated(QSystemTrayIcon::ActivationReason)));
}

void SysTray::onIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        m_parent->show();
        m_parent->activateWindow();
    }
    else if (reason == QSystemTrayIcon::Context)
    {
        addSysTrayMenu();
    }
}

void SysTray::addSysTrayMenu()
{
    CustomMenu* customMenu = new CustomMenu(m_parent);

    customMenu->addCustomMenu("主界面",    TRAY_ICON,         "主界面");
    customMenu->addCustomMenu("数据",    TRAY_DATA,         "数据");
    customMenu->addSeparator();
    customMenu->addCustomMenu("退出",      CLOSE_MENU,        "退出");

    FileTool::loadSyleSheet(customMenu,"SysTray");

    connect(customMenu->getAction("主界面"), SIGNAL(triggered(bool)), m_parent, SLOT(onShowNormal()));
    connect(customMenu->getAction("数据"), SIGNAL(triggered(bool)), m_parent, SLOT(onShowData()));
    connect(customMenu->getAction("退出"), SIGNAL(triggered(bool)), m_parent, SLOT(onShowQuit()));
    customMenu->exec(QCursor::pos());

    delete customMenu;
}
