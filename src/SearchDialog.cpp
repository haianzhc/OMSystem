/*******************************************************
* @projectName   OMSystem
* @brief         查找对话框
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#include "SearchDialog.h"
#include "ui_SearchDialog.h"
#include "DataDisplayWidget.h"

#include <QDebug>
#include <QDate>
#include <QDateTime>

SearchDialog::SearchDialog(QWidget *parent) : BasicDialog(parent),
    ui(new Ui::SearchDialog)
{
    sqlCondition = "";
    map.insert(0,"");
    map.insert(1,"para0");
    map.insert(2,"para1");
    map.insert(3,"para2");
    map.insert(4,"para3");
    map.insert(5,"para4");
    map.insert(6,"para5");
    map.insert(7,"para6");
    map.insert(8,"para7");
    map.insert(9,"para8");
    map.insert(10,"para9");
    map.insert(11,"para10");
    map.insert(12,"para11");
    map.insert(13,"para12");
    map.insert(14,"para13");
    map.insert(15,"para14");
    ui->setupUi(this);

    ui->preDateEdit->setDateRange(QDate::currentDate().addYears(-20),QDate::currentDate());
    ui->nextDateEdit->setDateRange(QDate::currentDate().addYears(-20),QDate::currentDate());
    ui->preDateEdit->setDate(QDate::currentDate().addYears(-20));
    ui->nextDateEdit->setDate(QDate::currentDate());

    inItTitle();
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

bool SearchDialog::event(QEvent* evt)
{
    if( evt->type() == QEvent::Close )
    {
        hide();

        return true;
    }

    return QDialog::event(evt);
}

void SearchDialog::inItTitle()
{
    setTitleWidget("查找");
    ui->titleLayout->addWidget(m_titleWidget);
}

QString SearchDialog::getCondition()
{
    return sqlCondition;
}

/**
* @brief         将下拉列表条件拼接为sql语句
* @param         box:下拉列表
*                pre:数值输入框
*                last:数值输入框
* @return        None
*/
void SearchDialog::parseCondition(QComboBox*& box,QDoubleSpinBox*& pre,QDoubleSpinBox*& last)
{
    QString paraStr = map[box->currentIndex()];

    if(!paraStr.isEmpty())
    {
        QString preText = pre->text();
        QString lastText = last->text();

        sqlCondition.append("(");
        sqlCondition.append(paraStr);
        sqlCondition.append(" >= ");
        sqlCondition.append(preText);
        sqlCondition.append(" and ");
        sqlCondition.append(paraStr);
        sqlCondition.append(" <= ");
        sqlCondition.append(lastText);
        sqlCondition.append(")");
        sqlCondition.append(" and ");
    }
}

void SearchDialog::parseCondition(QDateEdit*& pre,QDateEdit*& last)
{
    QString preTime = pre->date().toString("yyyy-MM-dd");
    QString nextTime = last->date().toString("yyyy-MM-dd");

    sqlCondition.append("(");
    sqlCondition.append("time");
    sqlCondition.append(" between ");
    sqlCondition.append("'" + preTime + " 00:00:00" + "'");
    sqlCondition.append(" and ");
    sqlCondition.append("'" + nextTime + " 23:59:59" + "'");
    sqlCondition.append(")");
    sqlCondition.append(" and ");
}

void SearchDialog::clearCondition()
{
    sqlCondition.clear();
}

void SearchDialog::on_cancelBtn_clicked()
{
    close();
}

void SearchDialog::on_searchBtn_clicked()
{
    sqlCondition.clear();
    parseCondition(ui->paraGomboBox1,ui->preDSBX1,ui->lastDSBX1);
    parseCondition(ui->paraGomboBox2,ui->preDSBX2,ui->lastDSBX2);
    parseCondition(ui->paraGomboBox3,ui->preDSBX3,ui->lastDSBX3);
    parseCondition(ui->paraGomboBox4,ui->preDSBX4,ui->lastDSBX4);
    parseCondition(ui->paraGomboBox5,ui->preDSBX5,ui->lastDSBX5);
    parseCondition(ui->preDateEdit,ui->nextDateEdit);

    QString text = ui->lineEdit->text();

    if(!text.trimmed().isEmpty())
    {
        sqlCondition.append("(");
        sqlCondition.append(" name ");
        sqlCondition.append("like ");
        sqlCondition.append("\'");
        sqlCondition.append("%");
        sqlCondition.append(text);
        sqlCondition.append("%");
        sqlCondition.append("\' ");
        sqlCondition.append(")");
    }
    else
    {
        if(!sqlCondition.isEmpty())
        {
           sqlCondition = sqlCondition.mid(0,sqlCondition.length() - 4);
        }
    }

    DataDisplayWidget* w = dynamic_cast<DataDisplayWidget*>(parent());

    if(w != NULL)
    {
        w->search();
    }
}

void SearchDialog::setTotalCount(int i)
{
    totalCount = i;
}

int SearchDialog::getTotalCount()
{
    return totalCount;
}
