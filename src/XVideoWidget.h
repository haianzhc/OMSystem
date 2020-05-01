/***********************************************
* @projectName   OMSystem
* @brief         播放器容器类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-20
************************************************/

#pragma execution_character_set("utf-8")

#ifndef XVIDEOWIDGET_H
#define XVIDEOWIDGET_H

#include <QOpenGLWidget>
#include <QImage>
#include <opencv2/opencv.hpp>

class XVideoWidget : public QOpenGLWidget
{
    Q_OBJECT

    QImage img;

    void paintGL();

public:

    explicit XVideoWidget(QWidget* parent = nullptr);

    void setIsChanged(bool isChanged);

public slots:

    void setImage(cv::Mat mat);
};

#endif // XVIDEOWIDGET_H
