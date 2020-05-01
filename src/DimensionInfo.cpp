#include "DimensionInfo.h"

DimensionInfo::DimensionInfo(QObject *parent) : QObject(parent)
{

}

void DimensionInfo::appendCircle(Circle circle)
{
    circleList.append(circle);
}

void DimensionInfo::appendLine(Line line)
{
    lineList.append(line);
}

QList<DimensionInfo::Circle> DimensionInfo::getCircleList()
{
    return circleList;
}

QList<DimensionInfo::Line> DimensionInfo::getLineList()
{
    return lineList;
}

void DimensionInfo::clearCircleList()
{
    circleList.clear();
}

void DimensionInfo::clearLineList()
{
    lineList.clear();
}

void DimensionInfo::clear()
{
    clearCircleList();
    clearLineList();
}

bool DimensionInfo::hasCircle()
{
    return !circleList.isEmpty();
}

bool DimensionInfo::hasLine()
{
    return !lineList.isEmpty();
}

bool DimensionInfo::isEmpty()
{
    return !(hasCircle() || hasLine());
}
