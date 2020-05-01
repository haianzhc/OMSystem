/*******************************************************
* @projectName   OMSystem
* @brief         Excel导入线程类
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-16
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef EXCELIMPORTER_H
#define EXCELIMPORTER_H

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

class ExcelImporter : public QObject
{
    Q_OBJECT

    DataSource* myConnection;
    SearchDialog* searchDly;
    QString path;

    QThread importThread;

    QStringList headList;

    bool assemble(CompolentInfo& obj,const QVariantList& row);
    bool isValid(const QVariantList& vList);

    bool importExcelToDataBase(const QString& path);
public:

    ExcelImporter(SearchDialog* sDly = nullptr,QObject *parent = nullptr);
    void setPath(const QString& path);
    void importStart();

signals:
    void importBegin();
    void importSuccess();
    void importFaliure();

public slots:
    void importTmain();
};

#endif // EXCELIMPORTER_H
