/***********************************************
* @projectName   OMSystem
* @brief         自定义标题栏
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#pragma execution_character_set("utf-8")

#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>

namespace Ui {
class TitleWidget;
}

class TitleWidget : public QWidget
{
    Q_OBJECT

    void paintEvent(QPaintEvent *e);

public:

    explicit TitleWidget(QWidget *parent = nullptr);
    ~TitleWidget();

    void setTitleText(const QString& titleText);
    void setTitleIcon(const QString& icon);

    void setMaxIcon(const QString& icon);

    void hideMin(bool isHide);
    void hideMax(bool isHide);

signals:

    void signalMin();

    void signalMax();

    void signalClose();

private slots:

    void onMin();

    void onMax();

    void onClose();

private:
    Ui::TitleWidget *ui;
};

#endif // TITLEWIDGET_H
