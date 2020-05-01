/*******************************************************
* @projectName   OMSystem
* @brief         Excel导入线程类
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-16
*******************************************************/

#include "ExcelImporter.h"

#include <QDir>
#include <QDebug>

ExcelImporter::ExcelImporter(SearchDialog* sDly,QObject *parent) : QObject(parent)
{
    myConnection = new DataSource("root","xjtuzhc",this);
    searchDly = sDly;
    path = "";

    moveToThread(&importThread);
    connect(&importThread,SIGNAL(started()),this,SLOT(importTmain()));
}

void ExcelImporter::setPath(const QString& path)
{
    this->path = path;
}

/**
* @brief         将Excel表中数据导入至数据库
* @param         path:文件路径
* @return        导入是否成功
*/
bool ExcelImporter::importExcelToDataBase(const QString& path)
{
    bool ret = true;

    QAxObject* myExcel = new QAxObject("Excel.Application");
    QAxObject* myWorks = myExcel->querySubObject("WorkBooks");
    myWorks->dynamicCall("Open(const QString&)",QDir::toNativeSeparators(path));
    QAxObject* workBook = myExcel->querySubObject("ActiveWorkBook");
    QAxObject* mySheets = workBook->querySubObject("Sheets");
    QAxObject* mySheet = mySheets->querySubObject("Item(int)",1);

    QVariant var;
    QAxObject *usedRange = mySheet->querySubObject("UsedRange");
    var = usedRange->dynamicCall("Value");
    QVariantList varRows = var.toList();
    const int rowCount = varRows.size();
    QVariantList rowData = varRows[0].toList();

    if(isValid(rowData))
    {
        for(int i = 1;i < rowCount;i++)
        {
            rowData = varRows[i].toList();
            CompolentInfo obj;
            assemble(obj,rowData);
            myConnection->insert(obj);
        }
    }
    else
    {
        ret = false;
    }

    workBook->dynamicCall("Close()");
    myExcel->dynamicCall("Quit()");
    delete myExcel;

    return ret;
}

/**
* @brief         将链表装配为零件对象
* @param         row:数据链表
*                obj:待装配零件对象
* @return        装配是否成功
*/
bool ExcelImporter::assemble(CompolentInfo& obj,const QVariantList& row)
{
    bool ret = true;

    for(int i = 0;i < row.count();i++)
    {
        if(!obj.setAttributeByString(headList[i],row.at(i)))
        {
            ret = false;
        }
    }

    return ret;
}

/**
* @brief         判断Excel表头是否合法
* @param         vList:表头数据链表
* @return        是否合法
*/
bool ExcelImporter::isValid(const QVariantList& vList)
{
    bool ret = true;
    headList.clear();

    for(int i = 0;i < vList.count();i++)
    {
        QString attr = vList.at(i).toString().trimmed().toLower();

        if(CompolentInfo::ATTRIBUTE_LIST.contains(attr))
        {
            if(headList.contains(attr))
            {
                ret = false;
            }
            else
            {
                headList.append(attr);
            }
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

void ExcelImporter::importTmain()
{
    emit importBegin();

    if(importExcelToDataBase(path))
    {
        emit importSuccess();
    }
    else
    {
        emit importFaliure();
    }
    importThread.quit();
}

 void ExcelImporter::importStart()
 {
     importThread.start();
 }
