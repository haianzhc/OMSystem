#pragma execution_character_set("utf-8")

#include "PaintTool.h"

#include <QFont>
#include <QPainter>

#define PAINT_LINE_WIDTH 2
#define PAINT_FONT "等线"
#define PAINT_FONT_SIZE 15
#define LENGTH_OF_SIDE 10.0         //箭头部分三角形的腰长
#define INTERVAL_OF_DIMENSION 0
#define RISE_OF_DIMENSION 5
#define INTERVAL_OF_TEXT 20
#define LENGTH_OF_TEXT 1

PaintTool::PaintTool(QObject *parent) : QObject(parent)
{

}

void PaintTool::drawArrow(QPainter& p,QPoint startPoint,QPoint endPoint,double ratio,bool isSingle)
{
    p.setRenderHint(QPainter::Antialiasing, true);  //消锯齿
    QPen drawTrianglePen;   //创建画笔
    drawTrianglePen.setColor(Qt::red);
    drawTrianglePen.setWidth(1);
    p.setPen(drawTrianglePen);
    p.setBrush(Qt::red);

    double length = LENGTH_OF_SIDE * ratio;

    //绘制箭头部分
    double slopy = atan2((endPoint.y() - startPoint.y()), (endPoint.x() - startPoint.x()));
    double cosy = cos(slopy);
    double siny = sin(slopy);

    QPoint point1 = QPoint(endPoint.x() + int(-length * cosy - (length / 2.0 * siny)),
                           endPoint.y() + int(-length * siny + (length / 2.0 * cosy)));
    QPoint point2 = QPoint(endPoint.x() + int(-length * cosy + (length / 2.0 * siny)),
                           endPoint.y() - int(length / 2.0 * cosy + length * siny));
    QPoint points[3] = { endPoint, point1, point2 };
    p.drawPolygon(points, 3);

    if(!isSingle)
    {
        QPoint point1_0 = QPoint(startPoint.x() - int(-length * cosy - (length / 2.0 * siny)),
                               startPoint.y() - int(-length * siny + (length / 2.0 * cosy)));
        QPoint point2_0 = QPoint(startPoint.x() - int(-length * cosy + (length / 2.0 * siny)),
                               startPoint.y() + int(length / 2.0 * cosy + length * siny));
        QPoint points_0[3] = { startPoint, point1_0, point2_0 };
        p.drawPolygon(points_0, 3);
    }

    drawTrianglePen.setWidth(3);
    drawTrianglePen.setStyle(Qt::DotLine);
    p.setPen(drawTrianglePen);
    p.drawLine(startPoint,endPoint);

    drawTrianglePen.setStyle(Qt::SolidLine);
    p.setPen(drawTrianglePen);
}

void PaintTool::drawLinearDimension(QPainter& painter,QPoint& startPoint,QPoint& endPoint,Direction direction,
                                    int num,double length,int height,double ratio)
{
    int interval = int(INTERVAL_OF_DIMENSION * ratio);
    height = int(height * ratio);
    int rise = int(RISE_OF_DIMENSION * ratio);
    QRect leftRect(int(-LENGTH_OF_TEXT * 600 * ratio),int(-INTERVAL_OF_TEXT * ratio),
                   int(LENGTH_OF_TEXT * 580 * ratio),int(INTERVAL_OF_TEXT * 2 * ratio));
    QRect rightRect(int(-LENGTH_OF_TEXT * 20 * ratio),int(-INTERVAL_OF_TEXT * ratio),
                    int(LENGTH_OF_TEXT * 620 * ratio),int(INTERVAL_OF_TEXT * 2 * ratio));

    QPen pen;
    pen.setColor(Qt::yellow);
    pen.setWidth(PAINT_LINE_WIDTH);
    painter.setFont(QFont(PAINT_FONT,int(PAINT_FONT_SIZE * ratio)));

    QString preText = "[" + QString::number(num + 1) + "]";
    QString text =  " " + QString::number(length) + "px";

    if(direction == Top)
    {
        drawArrow(painter,startPoint - QPoint(0,height + interval),endPoint - QPoint(0,height + interval),ratio);

        painter.setPen(pen);
        painter.drawLine(startPoint - QPoint(0,interval),startPoint - QPoint(0,rise + height + interval));
        painter.drawLine(endPoint - QPoint(0,interval),endPoint - QPoint(0,rise + height + interval));

        painter.translate((startPoint + endPoint) / 2 -
                          QPoint(0,height + interval + int(INTERVAL_OF_TEXT * ratio)));
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(leftRect,Qt::AlignRight | Qt::AlignVCenter,preText);
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawText(rightRect,Qt::AlignLeft | Qt::AlignVCenter,text);
        painter.resetTransform();
    }
    else if (direction == Bottom)
    {
        drawArrow(painter,startPoint + QPoint(0,height + interval),endPoint + QPoint(0,height + interval),ratio);

        painter.setPen(pen);
        painter.drawLine(startPoint + QPoint(0,interval),startPoint + QPoint(0,rise + height + interval));
        painter.drawLine(endPoint + QPoint(0,interval),endPoint + QPoint(0,rise + height + interval));

        painter.translate((startPoint + endPoint) / 2 +
                          QPoint(0,height + interval - int(INTERVAL_OF_TEXT * ratio)));
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(leftRect,Qt::AlignRight | Qt::AlignVCenter,preText);
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawText(rightRect,Qt::AlignLeft | Qt::AlignVCenter,text);
        painter.resetTransform();
    }
    else if (direction == Left)
    {
        drawArrow(painter,startPoint - QPoint(height + interval,0),endPoint - QPoint(height + interval,0),ratio);

        painter.setPen(pen);
        painter.drawLine(startPoint - QPoint(interval,0),startPoint - QPoint(rise + height + interval,0));
        painter.drawLine(endPoint - QPoint(interval,0),endPoint - QPoint(rise + height + interval,0));

        painter.translate((startPoint + endPoint) / 2 -
                          QPoint(height + interval + int(INTERVAL_OF_TEXT * ratio),0));
        painter.rotate(-90);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(leftRect,Qt::AlignRight | Qt::AlignVCenter,preText);
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawText(rightRect,Qt::AlignLeft | Qt::AlignVCenter,text);
        painter.resetTransform();
    }
    else if (direction == Right)
    {
        drawArrow(painter,startPoint + QPoint(height,0),endPoint + QPoint(height,0),ratio);

        painter.setPen(pen);
        painter.drawLine(startPoint + QPoint(interval,0),startPoint + QPoint(rise + height  + interval,0));
        painter.drawLine(endPoint + QPoint(interval,0),endPoint + QPoint(rise + height + interval,0));

        painter.translate((startPoint + endPoint) / 2 +
                          QPoint(height + interval - int(INTERVAL_OF_TEXT * ratio),0));
        painter.rotate(-90);
        pen.setColor(Qt::white);
        painter.setPen(pen);
        painter.drawText(leftRect,Qt::AlignRight | Qt::AlignVCenter,preText);
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawText(rightRect,Qt::AlignLeft | Qt::AlignVCenter,text);
        painter.resetTransform();
    }
}
