/***********************************************
* @projectName   OMSystem
* @brief         播放器容器类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-20
************************************************/

#include "XVideoWidget.h"

#include <QPainter>

XVideoWidget::XVideoWidget(QWidget* parent) : QOpenGLWidget(parent)
{

}

void XVideoWidget::paintGL()
{
    QPainter p;
    p.begin(this);
    p.drawImage(QPoint(0,0),img);
    p.end();
}

void XVideoWidget::setImage(cv::Mat mat)
{
    int w = width();
    int h = height();

    if(img.isNull())
    {
        uchar* buf = new uchar[w * h * 3];
        img = QImage(buf,w,h,QImage::Format_RGB888);
    }

    cv::Mat des;
    cv::resize(mat,des,cv::Size(w,h));
    cv::cvtColor(des,des,cv::COLOR_BGR2RGB);

    memcpy(img.bits(),des.data,des.cols * des.rows * des.elemSize());

    update();
}
