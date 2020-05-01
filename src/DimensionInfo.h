#ifndef DIMENSIONINFO_H
#define DIMENSIONINFO_H

#include <QObject>
#include <QPoint>
#include <QList>

#include "PaintTool.h"

class DimensionInfo : public QObject
{
    Q_OBJECT

public:

    struct Circle
    {
        QPoint center;
        double radius;
        PaintTool::Direction direction;
    };

    struct Line
    {
        QList<QPoint> points;
        double distance;
        PaintTool::Direction direction;
    };

    explicit DimensionInfo(QObject *parent = nullptr);

    void appendCircle(Circle circle);
    void appendLine(Line line);
    QList<Circle> getCircleList();
    QList<Line> getLineList();
    void clearCircleList();
    void clearLineList();
    void clear();
    bool hasCircle();
    bool hasLine();
    bool isEmpty();

private:

    QList<Circle> circleList;
    QList<Line> lineList;
};

#endif // DIMENSIONINFO_H
