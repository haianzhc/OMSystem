/*******************************************************
* @projectName   OMSystem
* @brief         查看大图
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-26
*******************************************************/


#include "BigImageDialog.h"

#include <QPixmap>
#include <QImage>

BigImageDialog::BigImageDialog(QString path,QWidget *parent) :
    BasicDialog(parent),myPath(path),myLabel(this)
{
    initTitle();

    QImage image(path);
    myLabel.setPixmap(QPixmap::fromImage(image));
    myLabel.setScaledContents(true);
    vLayout->addWidget(&myLabel);

    setLayout(vLayout);
}

void BigImageDialog::initTitle()
{
    setTitleWidget(myPath);
    vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->addWidget(m_titleWidget);
}
