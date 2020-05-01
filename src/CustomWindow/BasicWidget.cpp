/***********************************************
* @projectName   OMSystem
* @brief         自定义标题容器类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#include "BasicWidget.h"

#include <QPainter>
#include <QPalette>
#include <QIcon>
#include <QApplication>
#include <QMouseEvent>

#define BACK_COLOR QColor(53, 53, 53)
#define ARC_WIDTH 2

static bool press = false;
static QPoint last;

BasicWidget::BasicWidget(QWidget *parent) : QWidget(parent)
{
    initTitleWidget();
    setWindowIcon(QIcon(TITLE_ICON));
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowMinMaxButtonsHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void BasicWidget::initTitleWidget()
{
    m_titleWidget = new TitleWidget(this);
}

void BasicWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        press = true;

        last = event->globalPos();
    }

    QWidget::mousePressEvent(event);
}

void BasicWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(press)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        move(x() + dx, y() + dy);
    }

    QWidget::mouseMoveEvent(event);
}

void BasicWidget::mouseReleaseEvent(QMouseEvent*event)
{
    if(event->button() == Qt::LeftButton && press )
    {
        press = false;

        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        move(x() + dx, y() + dy);
    }

    QWidget::mousePressEvent(event);
}

void BasicWidget::setTitleWidget(const QString& qsTitleName, const QString& qsTitleIcon)
{
    connect(m_titleWidget, SIGNAL(signalClose()), this, SLOT(onShowClose()));
    connect(m_titleWidget, SIGNAL(signalMin()), this, SLOT(onShowMin()));
    connect(m_titleWidget, SIGNAL(signalMax()), this, SLOT(onShowMax()));
    m_titleWidget->setTitleIcon(qsTitleIcon);
    m_titleWidget->setTitleText(qsTitleName);
    m_titleWidget->setMaxIcon(":/res/pic/title/normal.png");
}

void BasicWidget::onShowClose()
{
    close();
}

void BasicWidget::onShowMin()
{
    showMinimized();
}

void BasicWidget::onShowMax()
{
    if(isMaximized())
    {
        showNormal();
        m_titleWidget->setMaxIcon(":/res/pic/title/normal.png");
    }
    else
    {
        showMaximized();
        m_titleWidget->setMaxIcon(":/res/pic/title/max.png");
    }
}

void BasicWidget::onShowNormal()
{
    show();
    activateWindow();
}

void BasicWidget::onShowQuit()
{
    QApplication::quit();
}

void BasicWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QColor colorBackGround = BACK_COLOR;
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(colorBackGround);
    p.drawRoundedRect(0, 0, width() - 1, height() - 1, ARC_WIDTH, ARC_WIDTH);
}
