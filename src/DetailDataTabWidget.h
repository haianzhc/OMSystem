/*******************************************************
* @projectName   OMSystem
* @brief         分页页面类，内容可定制
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-12
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef DETAILDATATABWIDGET_H
#define DETAILDATATABWIDGET_H

#include <QWidget>

#include "CompolentInfo.h"

namespace Ui {
class DetailDataTabWidget;
}

class DetailDataTabWidget : public QWidget
{
    Q_OBJECT

    bool* m_editable;

public:

    DetailDataTabWidget(bool* editable = nullptr,QWidget *parent = nullptr);
    ~DetailDataTabWidget();

    void setEditable(bool editable);
    void setDataLabelName(QString name0,QString name1,QString name2,QString name3,QString name4,QString name5,
                          QString name6,QString name7,QString name8,QString name9,QString name10,QString name11,
                          QString name12,QString name13,QString name14,QString name15,QString name16,QString name17,
                          QString name18,QString name19);
    void setCompolentInfoOnTab1(CompolentInfo& obj);

    QString getValue0();
    QString getValue1();
    QString getValue2();
    QString getValue3();
    QString getValue4();
    QString getValue5();
    QString getValue6();
    QString getValue7();
    QString getValue8();
    QString getValue9();
    QString getValue10();
    QString getValue11();
    QString getValue12();
    QString getValue13();
    QString getValue14();
    QString getValue15();
    QString getValue16();
    QString getValue17();
    QString getValue18();
    QString getValue19();

private:
    Ui::DetailDataTabWidget *ui;
};

#endif // DETAILDATATABWIDGET_H
