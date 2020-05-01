/*******************************************************
* @projectName   OMSystem
* @brief         查找对话框
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QEvent>
#include <QMap>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QMouseEvent>

#include "CustomWindow/BasicDialog.h"

namespace Ui {
class SearchDialog;
}

class SearchDialog : public BasicDialog
{
    Q_OBJECT

    QString sqlCondition;
    QMap<int,QString> map;
    int totalCount;

    void inItTitle();

    bool event(QEvent* evt);

    void parseCondition(QComboBox*& box,QDoubleSpinBox*& pre,QDoubleSpinBox*& last);
    void parseCondition(QDateEdit*& pre,QDateEdit*& last);

public:

    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

    QString getCondition();
    void clearCondition();
    void setTotalCount(int i);
    int getTotalCount();

private slots:

    void on_cancelBtn_clicked();

    void on_searchBtn_clicked();

private:
    Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_H
