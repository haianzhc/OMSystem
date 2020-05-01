/***********************************************
* @projectName   OMSystem
* @brief         自定义对话框类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-16
************************************************/

#include "BasicDialog.h"

#include <QPainter>
#include <QPalette>
#include <QIcon>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

#define BACK_COLOR QColor(53, 53, 53)
#define ARC_WIDTH 2

static bool press = false;
static QPoint last;

BasicDialog::BasicDialog(QWidget* parent) : QDialog(parent)
{
    initTitleWidget();
    setWindowIcon(QIcon(TITLE_ICON));
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowMinMaxButtonsHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void BasicDialog::initTitleWidget()
{
    m_titleWidget = new TitleWidget(this);
    m_titleWidget->hideMin(true);
    m_titleWidget->hideMax(true);
}

void BasicDialog::setTitleWidget(const QString& qsTitleName, const QString& qsTitleIcon)
{
    connect(m_titleWidget, SIGNAL(signalClose()), this, SLOT(onShowClose()));
    m_titleWidget->setTitleIcon(qsTitleIcon);
    m_titleWidget->setTitleText(qsTitleName);
}

void BasicDialog::onShowClose()
{
    close();
}

void BasicDialog::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QColor colorBackGround = BACK_COLOR;
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(colorBackGround);
    p.drawRoundedRect(0, 0, width() - 1, height() - 1, ARC_WIDTH, ARC_WIDTH);
}

void BasicDialog::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        press = true;

        last = event->globalPos();
    }

    QDialog::mousePressEvent(event);
}

void BasicDialog::mouseMoveEvent(QMouseEvent* event)
{
    if(press)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        move(x() + dx, y() + dy);
    }

    QDialog::mouseMoveEvent(event);
}

void BasicDialog::mouseReleaseEvent(QMouseEvent*event)
{
    if(event->button() == Qt::LeftButton && press )
    {
        press = false;

        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        move(x() + dx, y() + dy);
    }

    QDialog::mousePressEvent(event);
}
