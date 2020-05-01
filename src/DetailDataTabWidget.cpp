/*******************************************************
* @projectName   OMSystem
* @brief         分页页面类，内容可定制
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-12
*******************************************************/

#include "DetailDataTabWidget.h"
#include "ui_DetailDataTabWidget.h"

DetailDataTabWidget::DetailDataTabWidget(bool* editable,QWidget *parent) :
    QWidget(parent),m_editable(editable),
    ui(new Ui::DetailDataTabWidget)
{
    ui->setupUi(this);
    setEditable(*m_editable);
}

DetailDataTabWidget::~DetailDataTabWidget()
{
    delete ui;
}

/**
* @brief         设置标签名称
* @param         nameN:标签名
* @return        None
*/
void DetailDataTabWidget::setDataLabelName(QString name0,QString name1,QString name2,QString name3,QString name4,
                      QString name5,QString name6,QString name7,QString name8,QString name9,QString name10,
                      QString name11,QString name12,QString name13,QString name14,QString name15,QString name16,
                      QString name17,QString name18,QString name19)
{
    ui->para0->setText(name0);
    ui->para1->setText(name1);
    ui->para2->setText(name2);
    ui->para3->setText(name3);
    ui->para4->setText(name4);
    ui->para5->setText(name5);
    ui->para6->setText(name6);
    ui->para7->setText(name7);
    ui->para8->setText(name8);
    ui->para9->setText(name9);
    ui->para10->setText(name10);
    ui->para11->setText(name11);
    ui->para12->setText(name12);
    ui->para13->setText(name13);
    ui->para14->setText(name14);
    ui->para15->setText(name15);
    ui->para16->setText(name16);
    ui->para17->setText(name17);
    ui->para18->setText(name18);
    ui->para19->setText(name19);
}

void DetailDataTabWidget::setEditable(bool editable)
{
    ui->data0Edit->setReadOnly(!editable);
    ui->data1Edit->setReadOnly(!editable);
    ui->data2Edit->setReadOnly(!editable);
    ui->data3Edit->setReadOnly(!editable);
    ui->data4Edit->setReadOnly(!editable);
    ui->data5Edit->setReadOnly(!editable);
    ui->data6Edit->setReadOnly(!editable);
    ui->data7Edit->setReadOnly(!editable);
    ui->data8Edit->setReadOnly(!editable);
    ui->data9Edit->setReadOnly(!editable);
    ui->data10Edit->setReadOnly(!editable);
    ui->data11Edit->setReadOnly(!editable);
    ui->data12Edit->setReadOnly(!editable);
    ui->data13Edit->setReadOnly(!editable);
    ui->data14Edit->setReadOnly(!editable);
    ui->data15Edit->setReadOnly(!editable);
    ui->data16Edit->setReadOnly(!editable);
    ui->data17Edit->setReadOnly(!editable);
    ui->data18Edit->setReadOnly(!editable);
    ui->data19Edit->setReadOnly(!editable);
}

void DetailDataTabWidget::setCompolentInfoOnTab1(CompolentInfo& obj)
{
    ui->data0Edit->setText(obj.getName());
    ui->data1Edit->setText(QString::number(obj.getPara0()));
    ui->data2Edit->setText(QString::number(obj.getPara1()));
    ui->data3Edit->setText(QString::number(obj.getPara2()));
    ui->data4Edit->setText(QString::number(obj.getPara3()));
    ui->data5Edit->setText(QString::number(obj.getPara4()));
    ui->data6Edit->setText(QString::number(obj.getPara5()));
    ui->data7Edit->setText(QString::number(obj.getPara6()));
    ui->data8Edit->setText(QString::number(obj.getPara7()));
    ui->data9Edit->setText(QString::number(obj.getPara8()));
    ui->data10Edit->setText(QString::number(obj.getPara9()));
    ui->data11Edit->setText(QString::number(obj.getPara10()));
    ui->data12Edit->setText(QString::number(obj.getPara11()));
    ui->data13Edit->setText(QString::number(obj.getPara12()));
    ui->data14Edit->setText(QString::number(obj.getPara13()));
    ui->data15Edit->setText(QString::number(obj.getPara14()));
}

QString DetailDataTabWidget::getValue0()
{
    return ui->data0Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue1()
{
    return ui->data1Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue2()
{
    return ui->data2Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue3()
{
    return ui->data3Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue4()
{
    return ui->data4Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue5()
{
    return ui->data5Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue6()
{
    return ui->data6Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue7()
{
    return ui->data7Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue8()
{
    return ui->data8Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue9()
{
    return ui->data9Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue10()
{
    return ui->data10Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue11()
{
    return ui->data11Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue12()
{
    return ui->data12Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue13()
{
    return ui->data13Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue14()
{
    return ui->data14Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue15()
{
    return ui->data15Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue16()
{
    return ui->data16Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue17()
{
    return ui->data17Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue18()
{
    return ui->data18Edit->text().trimmed();
}

QString DetailDataTabWidget::getValue19()
{
    return ui->data19Edit->text().trimmed();
}
