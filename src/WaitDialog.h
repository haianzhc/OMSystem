/*******************************************************
* @projectName   OMSystem
* @brief         线程等待对话框
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-16
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include "CustomWindow/BasicDialog.h"

namespace Ui {
class WaitDialog;
}

class WaitDialog : public BasicDialog
{
    Q_OBJECT

public:

    explicit WaitDialog(QWidget *parent = nullptr);
    ~WaitDialog();

    void initTitle(const QString& title);
    void setLabelText(const QString& str);

private:
    Ui::WaitDialog *ui;
};

#endif // WAITDIALOG_H
