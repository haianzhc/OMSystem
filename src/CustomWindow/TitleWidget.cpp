/***********************************************
* @projectName   OMSystem
* @brief         自定义标题栏
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-14
************************************************/

#include "ui_TitleWidget.h"
#include "TitleWidget.h"
#include "FileTool.h"

#include <QPainter>
#include <QIcon>

#define TITLE_BACK_COLOR QColor(53, 53, 53)

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(ui->sysMin, SIGNAL(clicked()), this, SLOT(onMin()));
    connect(ui->sysMax, SIGNAL(clicked()), this, SLOT(onMax()));
    connect(ui->sysClose, SIGNAL(clicked()), this, SLOT(onClose()));

    FileTool::loadSyleSheet(this,"TitleWidget");
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

void TitleWidget::onMin()
{
    emit signalMin();
}

void TitleWidget::onClose()
{
    emit signalClose();
}

void TitleWidget::onMax()
{
    emit signalMax();
}

void TitleWidget::setTitleText(const QString& titleText)
{
    ui->TitleName->setText(titleText);
}

void TitleWidget::setTitleIcon(const QString& icon)
{
    ui->Titleicon->setPixmap(QPixmap(icon).scaled(ui->Titleicon->size(),
                                                  Qt::IgnoreAspectRatio, Qt::FastTransformation));
}

void TitleWidget::setMaxIcon(const QString& icon)
{
    ui->sysMax->setIcon(QIcon(QPixmap(icon).scaled(QSize(12,12),
                                                   Qt::IgnoreAspectRatio, Qt::FastTransformation)));
}

void TitleWidget::hideMin(bool isHide)
{
    ui->sysMin->setVisible(!isHide);
}

void TitleWidget::hideMax(bool isHide)
{
    ui->sysMax->setVisible(!isHide);
}

void TitleWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QColor colorBackGround = TITLE_BACK_COLOR;
    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(colorBackGround);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(0, 0, width() - 1, height() - 1, 2, 2);
}
