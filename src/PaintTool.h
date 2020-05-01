#ifndef PAINTTOOL_H
#define PAINTTOOL_H

#include <QObject>
#include <QPainter>
#include <QPoint>

class PaintTool : public QObject
{
    Q_OBJECT

    explicit PaintTool(QObject *parent = nullptr);

    static void drawArrow(QPainter& p,QPoint startPoint,QPoint endPoint,double ratio = 1.0,bool isSingle = false);

public:

    enum Direction
    {
        Top,
        Bottom,
        Left,
        Right
    };

    static void drawLinearDimension(QPainter& painter,QPoint& startPoint,QPoint& endPoint,Direction direction,
                                    int num,double length,int height = 50,double ratio = 1.0);
};

#endif // PAINTTOOL_H
