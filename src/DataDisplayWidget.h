/*******************************************************
* @projectName   OMSystem
* @brief         数据展示窗口，用于显示整体数据
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef DATADISPLAYWIDGET_H
#define DATADISPLAYWIDGET_H

#include "CompolentInfoModel.h"
#include "DataSource.h"
#include "DetailInfoDisplayDialog.h"
#include "SearchDialog.h"
#include "ExcelImporter.h"
#include "ExcelExporter.h"
#include "WaitDialog.h"
#include "CustomWindow/BasicWidget.h"

#include <QEvent>
#include <QWidget>
#include <QMenu>
#include <QFileDialog>

namespace Ui {
class DataDisplayWidget;
}

class DataDisplayWidget : public BasicWidget
{
    Q_OBJECT

    QMenu m_menu;
    CompolentInfoModel compolentModel;

    bool* isEditable;
    DataSource* pConnect;
    SearchDialog* searchDly;
    ExcelImporter* excelImporter = nullptr;
    ExcelExporter* excelExporter = nullptr;
    WaitDialog* waitExporter = nullptr;
    WaitDialog* waitImporter = nullptr;

    int pageCount;
    int currentPage;
    int totalCount;

    void inItTitle();
    void initMenu();

    bool event(QEvent* evt);
    bool eventFilter(QObject* obj, QEvent* evt);

public:

    DataDisplayWidget(bool* editable = nullptr,DataSource* pds = nullptr,QWidget *parent = nullptr);
    ~DataDisplayWidget();

    CompolentInfoModel* getCompolentInfoModel();
    DataSource* getConnection();

    void setTotalNum(int i);
    int getPageSize();
    void setPageSize(int i);

    void search();
    void currentPageChanged();

private slots:

    void on_refreshBtn_clicked();

    void on_deleteBtn_clicked();

    void onClear();

    void on_infoBtn_clicked();

    void onCompleteDelete();

    void on_findBtn_clicked();

    void on_importBtn_clicked();

    void on_exportBtn_clicked();

    void on_pageSizeComboBox_currentIndexChanged(const QString &);

    void on_firstPageBtn_clicked();

    void on_lastPageBtn_clicked();

    void on_prePageBtn_clicked();

    void on_nextPageBtn_clicked();

    void on_gotoBtn_clicked();

    void onExportBegin();

    void onExporterSuccess();

    void onExporterFaliure();

    void onImportBegin();

    void onImporterSuccess();

    void onImporterFaliure();

    void on_clearBtn_clicked();

private:
    Ui::DataDisplayWidget *ui;
};

#endif // DATADISPLAYWIDGET_H
