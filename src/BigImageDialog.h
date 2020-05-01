/*******************************************************
* @projectName   OMSystem
* @brief         查看大图
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-26
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef BIGIMAGEDIALOG_H
#define BIGIMAGEDIALOG_H

#include <QLabel>
#include <QVBoxLayout>

#include "CustomWindow/BasicDialog.h"

class BigImageDialog : public BasicDialog
{
    Q_OBJECT

    QString myPath;
    QLabel myLabel;

    QVBoxLayout* vLayout;

    void initTitle();

public:
    BigImageDialog(QString path = "",QWidget *parent = nullptr);
};

#endif // BIGIMAGEDIALOG_H
