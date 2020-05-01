#include "XmlHandler.h"

#include <QtXml>
#include <QFile>
#include <QDebug>

XmlHandler::XmlHandler(QObject *parent) : QObject(parent)
{

}

PaintTool::Direction XmlHandler::string2Direction(const QString& str)
{
    if(str == "top")
    {
        return PaintTool::Top;
    }
    else if (str == "bottom")
    {
        return PaintTool::Bottom;
    }
    else if (str == "left")
    {
        return PaintTool::Left;
    }
    else
    {
        return PaintTool::Right;
    }
}

void XmlHandler::parseXML(const QString& path,DimensionInfo& dimension)
{
    dimension.clear();
    QDomDocument doc;
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly))
        return;

    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }

    file.close();

    QDomElement docElem = doc.documentElement();

    QDomNode n = docElem.firstChild();

    while(!n.isNull())
    {
        if(n.isElement())
        {
            QDomElement e = n.toElement();

            if("line" == e.tagName())
            {
                DimensionInfo::Line line;
                double distance = e.attribute("length").toDouble();
                PaintTool::Direction direction = string2Direction(e.attribute("direction"));

                QDomNodeList list = e.childNodes();

                for (int i = 0;i < list.count();i++)
                {
                    QDomNode node = list.at(i);

                    if(node.isElement())
                    {
                        QDomElement element = node.toElement();

                        int x = int(element.attribute("x").toDouble());
                        int y = int(element.attribute("y").toDouble());
                        QPoint point(x,y);
                        line.points.append(point);
                    }
                }

                if(distance > 0.001)
                {
                    line.distance = distance;
                    line.direction = direction;
                    dimension.appendLine(line);
                }
            }

            if("circle" == e.tagName())
            {
                DimensionInfo::Circle circle;
                double radius = e.attribute("radius").toDouble();

                QDomNodeList list = e.childNodes();

                for (int i = 0;i < list.count();i++)
                {
                    QDomNode node = list.at(i);

                    if(node.isElement())
                    {
                        QDomElement element = node.toElement();

                        int x = int(element.attribute("x").toDouble());
                        int y = int(element.attribute("y").toDouble());
                        QPoint point(x,y);
                        circle.center = point;
                    }
                }

                if(radius > 0.001)
                {
                    circle.radius = radius;
                    dimension.appendCircle(circle);
                }
            }
        }

        n = n.nextSibling();
    }
}
