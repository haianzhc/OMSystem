/*******************************************************
* @projectName   OMSystem
* @brief         Excel导出线程类
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-16
*******************************************************/

#include "ExcelExporter.h"

#include <QDir>
#include <QDebug>

ExcelExporter::ExcelExporter(SearchDialog* sDly,QObject *parent) : QObject(parent)
{
    myConnection = new DataSource("root","xjtuzhc",this);
    searchDly = sDly;
    path = "";

    headerData.append(QVariant("Name"));
    headerData.append(QVariant("Para0"));
    headerData.append(QVariant("Para1"));
    headerData.append(QVariant("Para2"));
    headerData.append(QVariant("Para3"));
    headerData.append(QVariant("Para4"));
    headerData.append(QVariant("Para5"));
    headerData.append(QVariant("Para6"));
    headerData.append(QVariant("Para7"));
    headerData.append(QVariant("Para8"));
    headerData.append(QVariant("Para9"));
    headerData.append(QVariant("Para10"));
    headerData.append(QVariant("Para11"));
    headerData.append(QVariant("Para12"));
    headerData.append(QVariant("Para13"));
    headerData.append(QVariant("Para14"));
    headerData.append(QVariant("Time"));

    moveToThread(&exportThread);

    connect(&exportThread,SIGNAL(started()),this,SLOT(exportTmain()));
}

void ExcelExporter::setPath(const QString& path)
{
    this->path = path;
}

/**
* @brief         将所需数据导出至Excel
* @param         path:路径
* @return        是否导出成功
*/
bool ExcelExporter::exportTableViewToExcel(const QString& path)
{
    bool ret = true;

    allRowData.clear();
    allRowData.append(QVariant(headerData));

    QString condition = searchDly->getCondition();
    int totalCount = searchDly->getTotalCount();

    if(myConnection->selectExportData(condition,allRowData))
    {
        QAxObject* myExcel = new QAxObject("Excel.Application");
        QAxObject* myWorks = myExcel->querySubObject("WorkBooks");
        myWorks->dynamicCall("add");
        QAxObject* workBook = myExcel->querySubObject("ActiveWorkBook");
        QAxObject* mySheets = workBook->querySubObject("Sheets");
        QAxObject* mySheet = mySheets->querySubObject("Item(int)",1);
        QAxObject* myRange = mySheet->querySubObject("Range(const QString)","A1:Q" + QString::number(totalCount + 1));
        myRange->dynamicCall("SetValue(const QVariant&)", QVariant(allRowData));
        workBook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(path));

        workBook->dynamicCall("Close()");
        myExcel->dynamicCall("Quit()");

        delete myExcel;
    }
    else
    {
        ret = false;
    }

    return ret;
}

void ExcelExporter::exportTmain()
{

    emit exportBegin();

    if(exportTableViewToExcel(path))
    {
        emit exportSuccess();
    }
    else
    {
        emit exportFaliure();
    }
    exportThread.quit();
}

 void ExcelExporter::exportStart()
 {
     exportThread.start();
 }
