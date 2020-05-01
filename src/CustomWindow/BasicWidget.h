/***********************************************
* @projectName   OMSystem
* @brief         自定义标题栏容器类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#pragma execution_character_set("utf-8")

#ifndef BASICWIDGET_H
#define BASICWIDGET_H

#include <QWidget>

#include "TitleWidget.h"

#define TITLE_ICON	":/res/pic/logo/All_logo32.ico"

class BasicWidget : public QWidget
{
    Q_OBJECT

    void initTitleWidget();
    void paintEvent(QPaintEvent *event);

public:

    BasicWidget(QWidget *parent = nullptr);

protected:

    TitleWidget* m_titleWidget = nullptr;

    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);

    void setTitleWidget(const QString& qsTitleName, const QString& qsTitleIcon = TITLE_ICON);

protected slots:

    void onShowClose();

    void onShowMin();

    void onShowMax();

    void onShowNormal();

    void onShowQuit();

};

#endif // BASICWIDGET_H
