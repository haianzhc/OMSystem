/***********************************************
* @projectName   OMSystem
* @brief         播放器界面类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-20
************************************************/

#pragma execution_character_set("utf-8")

#ifndef XVIDEOUI_H
#define XVIDEOUI_H

#include <QDialog>
#include <QMouseEvent>
#include <QFont>

using namespace std;

namespace Ui {
class XVideoUI;
}

class XVideoUI : public QDialog
{
    Q_OBJECT

    enum Status
    {
        ON,
        OFF
    };

    QPoint m_dragPos;

    void timerEvent(QTimerEvent* e);
    void mouseMoveEvent(QMouseEvent*event);
    void mousePressEvent(QMouseEvent*event);

    bool eventFilter(QObject* obj, QEvent* event);

public:

    XVideoUI(const QString& path = "",QWidget *parent = nullptr);
    ~XVideoUI();

    void setControlButtonText(Status status);

private slots:
    void on_openButton_clicked();

    void on_playSlider_sliderMoved(int position);

    void on_controlButton_clicked();

private:
    Ui::XVideoUI *ui;
};

#endif // XVIDEOUI_H
