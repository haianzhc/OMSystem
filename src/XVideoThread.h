/***********************************************
* @projectName   OMSystem
* @brief         播放器线程类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-20
************************************************/

#pragma execution_character_set("utf-8")

#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H

#include <QThread>
#include <QMutex>
#include <QString>
#include <opencv2/opencv.hpp>

class XVideoThread : public QThread
{
    Q_OBJECT

    int fps = 0;
    QMutex mutex;

    XVideoThread();
    ~XVideoThread();

    void run();

public:

    bool open(const QString& file);

    double getPos();

    bool seek(int frame);
    bool seek(double pos);

    void setStart(bool start);
    bool getStart();

    static XVideoThread* get();

signals:

    void viewImage1(cv::Mat mat);
};

#endif // XVIDEOTHREAD_H
