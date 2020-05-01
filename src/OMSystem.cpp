/***********************************************
* @projectName   OMSystem
* @brief         主窗口
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#include <QIcon>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QDebug>

#include "ui_OMSystem.h"
#include "OMSystem.h"
#include "AppConfig.h"

#define SHOW_EDGE_WIDTH 10

OMSystem::OMSystem(DataSource* ds,QWidget *parent) :BasicWidget(parent),m_eEdgeStatus(EG_NORMAL),
    ui(new Ui::OMSystem)
{
    ui->setupUi(this);

    m_OMSystemMainWin = OMSystemMainWin::NewInstance(ds);

    AppConfig ac;

    if(ac.isValid() && m_OMSystemMainWin != nullptr)
    {
        move(ac.mainWindowPoint());
        m_OMSystemMainWin->setPageSize(ac.pageSize());
        m_OMSystemMainWin->setEditable(ac.isEditable());
        m_OMSystemMainWin->setSbVisible(ac.isStatusBarVisible());
    }

    connect(m_OMSystemMainWin,SIGNAL(signalClose()),this,SLOT(onShowQuit()));

    inItTitle();
    initSysTray();

}

OMSystem::~OMSystem()
{
    AppConfig config(pos(),m_OMSystemMainWin->getPageSize(),m_OMSystemMainWin->isEditable(),
                     m_OMSystemMainWin->isSbVisible());

    config.store();

    delete ui;
}

void OMSystem::inItTitle()
{
    m_titleWidget->hideMax(true);
    setTitleWidget("西安交通大学光学测量系统   Optical Measurement System of Xi 'an JiaoTong University    Version:1.0.0");
    ui->titleLayout->addWidget(m_titleWidget);
    ui->verticalLayout->addWidget(m_OMSystemMainWin);
}

void OMSystem::initSysTray()
{
    m_systemTray = new SysTray(this);
}

void OMSystem::onShowData()
{
    m_OMSystemMainWin->onViewAllData();
}

void OMSystem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && !m_OMSystemMainWin->geometry().contains(event->pos()))
    {
        BasicWidget::mousePressEvent(event);
    }
}

void OMSystem::mouseReleaseEvent(QMouseEvent* event)
{
    if (y() <= 0)
    {
        m_eEdgeStatus = EG_TOP;
    }
    else if (QApplication::desktop()->width() <= (x() + width()))
    {
        m_eEdgeStatus = EG_RIGHT;
    }
    else if (x() <= 0)
    {
        m_eEdgeStatus = EG_LEFT;
    }
    else
    {
        m_eEdgeStatus = EG_NORMAL;
    }

    BasicWidget::mouseReleaseEvent(event);
}

void OMSystem::leaveEvent(QEvent *event)
{
    switch (m_eEdgeStatus)
    {
    case EG_TOP:
        setGeometry(pos().x(), -height() + SHOW_EDGE_WIDTH, width(), height());
        break;
    case EG_LEFT:
        setGeometry(-width() + SHOW_EDGE_WIDTH, pos().y(), width(), height());
        break;
    case EG_RIGHT:
        setGeometry(QApplication::desktop()->width() - SHOW_EDGE_WIDTH, pos().y(), width(), height());
        break;
    }

    return QWidget::leaveEvent(event);
}

void OMSystem::enterEvent(QEvent *event)
{
    switch (m_eEdgeStatus)
    {
    case EG_TOP:
        setGeometry(pos().x(), -SHOW_EDGE_WIDTH, width(), height());
        break;
    case EG_LEFT:
        setGeometry(-SHOW_EDGE_WIDTH, y(), width(), height());
        break;
    case EG_RIGHT:
        setGeometry(QApplication::desktop()->width() - width() + SHOW_EDGE_WIDTH, y(), width(), height());
        break;
    }
    return QWidget::enterEvent(event);
}
