/***********************************************
* @projectName   OMSystem
* @brief         主窗口
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#pragma execution_character_set("utf-8")

#ifndef OMSYSTEM_H
#define OMSYSTEM_H

#include <QWidget>

#include "CustomWindow/BasicWidget.h"
#include "CustomWindow/SysTray.h"
#include "OMSystemMainWin.h"
#include "DataSource.h"

typedef enum EG_STATUS
{

    EG_NORMAL = 0,

    EG_TOP,

    EG_LEFT,

    EG_RIGHT,

}EG_STATUS;

namespace Ui {
class OMSystem;
}

class OMSystem : public BasicWidget
{
    Q_OBJECT

    EG_STATUS m_eEdgeStatus;
    QPoint m_dragPos;
    SysTray* m_systemTray;
    OMSystemMainWin* m_OMSystemMainWin;

    void inItTitle();
    void initSysTray();

    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void mousePressEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);

public:

    OMSystem(DataSource* ds = nullptr,QWidget *parent = nullptr);
    ~OMSystem();

private slots:

    void onShowData();

private:
    Ui::OMSystem *ui;
};

#endif // OMSYSTEM_H
