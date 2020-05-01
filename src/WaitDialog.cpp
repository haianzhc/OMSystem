/*******************************************************
* @projectName   OMSystem
* @brief         线程等待对话框
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-16
*******************************************************/

#include "WaitDialog.h"
#include "ui_WaitDialog.h"

WaitDialog::WaitDialog(QWidget *parent) :
    BasicDialog(parent),
    ui(new Ui::WaitDialog)
{
    ui->setupUi(this);
}

WaitDialog::~WaitDialog()
{
    delete ui;
}

void WaitDialog::initTitle(const QString& title)
{
    setTitleWidget(title);
    ui->verticalLayout->insertWidget(0,m_titleWidget);
}

void WaitDialog::setLabelText(const QString& str)
{
    ui->label->setText(str);
}
