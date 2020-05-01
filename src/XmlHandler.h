#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QObject>

#include "DimensionInfo.h"
#include "PaintTool.h"

class XmlHandler : public QObject
{
    Q_OBJECT

    static PaintTool::Direction string2Direction(const QString& str);

public:
    explicit XmlHandler(QObject *parent = nullptr);

    static void parseXML(const QString& path,DimensionInfo& dimension);
};

#endif // XMLHANDLER_H
