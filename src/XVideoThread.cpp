/***********************************************
* @projectName   OMSystem
* @brief         播放器线程类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-20
************************************************/

#include "XVideoThread.h"

static cv::VideoCapture cap1;
static bool isExit = false;
static bool isStart = true;

XVideoThread* XVideoThread::get()
{
    static XVideoThread vt;
    return &vt;
}

XVideoThread::XVideoThread()
{
    start();
}

void XVideoThread::run()
{
    cv::Mat mat1;

    for(;;)
    {
        mutex.lock();

        if(isExit)
        {
            mutex.unlock();
            break;
        }

        if(!cap1.isOpened())
        {
            mutex.unlock();
            msleep(5);
            continue;
        }

        if(!isStart)
        {
            mutex.unlock();
            msleep(5);
            continue;
        }

        if(!cap1.read(mat1) || mat1.empty())
        {
            mutex.unlock();
            msleep(5);
            continue;
        }

        emit viewImage1(mat1);

        mutex.unlock();

        int s = 1000 / fps;
        msleep(s);
    }
}

void XVideoThread::setStart(bool start)
{
    isStart = start;
}

bool XVideoThread::getStart()
{
    return isStart;
}

bool XVideoThread::open(const QString& file)
{

    isStart = true;

    mutex.lock();
    cap1.release();
    bool re = cap1.open(file.toStdString());
    mutex.unlock();

    if(!re)
    {
        return re;
    }

    fps = cap1.get(cv::CAP_PROP_FPS);

    if(fps <= 0)
    {
        fps = 25;
    }

    return true;
}

double XVideoThread::getPos()
{
    double pos = 0;

    mutex.lock();

    if(!cap1.isOpened())
    {
        mutex.unlock();
        return pos;
    }

    double count = cap1.get(cv::CAP_PROP_FRAME_COUNT);
    double cur = cap1.get(cv::CAP_PROP_POS_FRAMES);

    if(count > 0.001)
    {
        pos = cur / count;
    }

    mutex.unlock();

    return pos;
}

bool XVideoThread::seek(int frame)
{
    mutex.lock();

    if(!cap1.isOpened())
    {
        mutex.unlock();
        return false;
    }

    bool re = cap1.set(cv::CAP_PROP_POS_FRAMES,frame);

    if(re)
    {
        cv::Mat mat;
        if(cap1.read(mat))
        {
            emit viewImage1(mat);
            int s = 1000 / fps;
            msleep(s);
        }
    }

    mutex.unlock();

    return re;
}

bool XVideoThread::seek(double pos)
{
    double count = cap1.get(cv::CAP_PROP_FRAME_COUNT);
    int frame = count * pos;
    return seek(frame);
}

XVideoThread::~XVideoThread()
{
    mutex.lock();
    isExit = true;
    mutex.unlock();

    wait();
}
