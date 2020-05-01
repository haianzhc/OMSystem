/***********************************************
* @projectName   OMSystem
* @brief         自定义对话框类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-16
************************************************/

#pragma execution_character_set("utf-8")

#ifndef BASICDIALOG_H
#define BASICDIALOG_H

#include <QDialog>
#include <QMouseEvent>

#include "TitleWidget.h"

#define TITLE_ICON	":/res/pic/logo/All_logo32.ico"

class BasicDialog : public QDialog
{
    Q_OBJECT

    void initTitleWidget();
    void paintEvent(QPaintEvent *event);

public:

    BasicDialog(QWidget *parent = nullptr);

protected:

    TitleWidget* m_titleWidget = nullptr;

    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);
    void mouseReleaseEvent(QMouseEvent*event);

    void setTitleWidget(const QString& qsTitleName, const QString& qsTitleIcon = TITLE_ICON);

protected slots:

    void onShowClose();

};

#endif // BASICDIALOG_H
