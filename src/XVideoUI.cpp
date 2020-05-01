/***********************************************
* @projectName   OMSystem
* @brief         播放器界面类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-20
************************************************/

#include "ui_XVideoUI.h"
#include "XVideoUI.h"
#include "XVideoThread.h"
#include "FileTool.h"
#include "CustomWindow/MessageBox.h"

#include <QDesktopWidget>

XVideoUI::XVideoUI(const QString& path,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::XVideoUI)
{
    ui->setupUi(this);
    ui->controlButton->setFont(QFont("等线",30));
    setWindowFlag(Qt::FramelessWindowHint);

    qRegisterMetaType<cv::Mat>("cv::Mat");

    connect(XVideoThread::get(),SIGNAL(viewImage1(cv::Mat)),ui->src1Video,SLOT(setImage(cv::Mat)));

    ui->playSlider->installEventFilter(this);

    startTimer(40);

    if(!path.isEmpty())
    {

        if(XVideoThread::get()->open(path))
        {
            setControlButtonText(ON);
        }
        else
        {
            setControlButtonText(OFF);
            showError(this,"错误",path + " 打开失败!");
        }
    }
}

XVideoUI::~XVideoUI()
{
    delete ui;
}

void XVideoUI::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && !ui->playSlider->geometry().contains(event->pos()))
    {
        m_dragPos = QCursor::pos() - frameGeometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void XVideoUI::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton && !ui->playSlider->geometry().contains(event->pos()))
    {
        QRect desktopRc = QApplication::desktop()->availableGeometry();
        QPoint curPoint = event->globalPos() - m_dragPos;

        if (event->globalY() > desktopRc.height())
        {
            curPoint.setY(desktopRc.height() - m_dragPos.y());
        }
        move(curPoint);
    }
    QWidget::mouseMoveEvent(event);
}

void XVideoUI::timerEvent(QTimerEvent*)
{
    double pos = XVideoThread::get()->getPos();
    ui->playSlider->setValue(pos * 1000);
}

bool XVideoUI::eventFilter(QObject* obj, QEvent* event)
{
    if(obj == ui->playSlider)
    {
        if (event->type() == QEvent::MouseButtonPress)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

            if (mouseEvent->button() == Qt::LeftButton) //判断左键
            {
                int dur = ui->playSlider->maximum() - ui->playSlider->minimum();
                int pos = ui->playSlider->minimum() + dur * ((double)mouseEvent->x() / ui->playSlider->width());

                if(pos < (ui->playSlider->sliderPosition()) || pos > (ui->playSlider->sliderPosition()))
                {
                    ui->playSlider->setValue(pos);
                    XVideoThread::get()->seek((double)pos / 1000.);
                }
            }
        }
    }

    return QObject::eventFilter(obj,event);
}

void XVideoUI::on_openButton_clicked()
{
    QString name = FileTool::showFileDialog(this,QFileDialog::AcceptOpen,"请选择视频文件",FileTool::Video);

    if(!name.isEmpty())
    {

        if(XVideoThread::get()->open(name))
        {
            setControlButtonText(ON);
        }
        else
        {
            setControlButtonText(OFF);
            showError(this,"",name + " 打开失败!");
        }
    }
}

void XVideoUI::setControlButtonText(Status status)
{
    switch (status)
    {
        case ON:
            ui->controlButton->setIcon(QIcon(":/res/pic/playing.png"));
            break;

        case OFF:
            ui->controlButton->setIcon(QIcon(":/res/pic/play.png"));
            break;
    }
}

void XVideoUI::on_playSlider_sliderMoved(int position)
{
    XVideoThread::get()->seek((double)position / 1000.);
}

void XVideoUI::on_controlButton_clicked()
{
    XVideoThread* video = XVideoThread::get();
    bool isStart = video->getStart();
    video->setStart(!isStart);

    if(!isStart)
    {
        setControlButtonText(ON);
    }
    else
    {
        setControlButtonText(OFF);
    }
}
