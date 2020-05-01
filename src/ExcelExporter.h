/*******************************************************
* @projectName   OMSystem
* @brief         Excel导出线程类
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-16
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef EXCELEXPORTER_H
#define EXCELEXPORTER_H

#include "DataSource.h"
#include "CompolentInfo.h"
#include "SearchDialog.h"

#include <QObject>
#include <QAxObject>
#include <QList>
#include <QVariant>
#include <QVariantList>
#include <QStringList>
#include <QThread>

class ExcelExporter : public QObject
{
    Q_OBJECT

    DataSource* myConnection;
    SearchDialog* searchDly;
    QString path;

    QThread exportThread;

    QVariantList allRowData;
    QVariantList headerData;

    bool exportTableViewToExcel(const QString& path);
public:

    ExcelExporter(SearchDialog* sDly = nullptr,QObject *parent = nullptr);

    void setPath(const QString& path);
    void exportStart();

signals:
    void exportBegin();
    void exportSuccess();
    void exportFaliure();

public slots:
    void exportTmain();
};

#endif // EXCELEXPORTER_H
