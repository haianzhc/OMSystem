/*******************************************************
* @projectName   OMSystem
* @brief         数据展示窗口，用于显示整体数据
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#include "ui_DataDisplayWidget.h"
#include "DataDisplayWidget.h"
#include "CompolentInfo.h"
#include "FileTool.h"
#include "CustomWindow/MessageBox.h"

#include <QDebug>
#include <QHeaderView>
#include <QDebug>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QStatusBar>

DataDisplayWidget::DataDisplayWidget(bool* editable,DataSource* pds,QWidget *parent) :
    BasicWidget(parent),m_menu(this),isEditable(editable),pConnect(pds),
    searchDly(new SearchDialog(this)),
    ui(new Ui::DataDisplayWidget)
{
    ui->setupUi(this);
    ui->tableView->installEventFilter(this);
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    inItTitle();
    initMenu();

    excelImporter = new ExcelImporter(searchDly);
    excelExporter = new ExcelExporter(searchDly);
    connect(excelExporter,SIGNAL(exportBegin()),this,SLOT(onExportBegin()));
    connect(excelExporter,SIGNAL(exportSuccess()),this,SLOT(onExporterSuccess()));
    connect(excelExporter,SIGNAL(exportFaliure()),this,SLOT(onExporterFaliure()));
    connect(excelImporter,SIGNAL(importBegin()),this,SLOT(onImportBegin()));
    connect(excelImporter,SIGNAL(importSuccess()),this,SLOT(onImporterSuccess()));
    connect(excelImporter,SIGNAL(importFaliure()),this,SLOT(onImporterFaliure()));

    on_refreshBtn_clicked();
}

/**
* @brief         初始化右键菜单
* @param         None
* @return        None
*/
void DataDisplayWidget::initMenu()
{
    m_menu.addAction("刷新");
    m_menu.addAction("删除");
    m_menu.addAction("彻底删除");
    m_menu.addSeparator();
    m_menu.addAction("详细信息");

    connect(m_menu.actions()[0],SIGNAL(triggered(bool)),this,SLOT(on_refreshBtn_clicked()));
    connect(m_menu.actions()[1],SIGNAL(triggered(bool)),this,SLOT(on_deleteBtn_clicked()));
    connect(m_menu.actions()[2],SIGNAL(triggered(bool)),this,SLOT(onCompleteDelete()));
    connect(m_menu.actions()[3],SIGNAL(triggered(bool)),this,SLOT(onClear()));
    connect(m_menu.actions()[4],SIGNAL(triggered(bool)),this,SLOT(on_infoBtn_clicked()));
}

void DataDisplayWidget::inItTitle()
{
    setTitleWidget("全部数据");
    ui->verticalLayout->insertWidget(0,m_titleWidget);
    ui->verticalLayout->insertWidget(3,new QStatusBar(this));
}

bool DataDisplayWidget::event(QEvent* evt)
{
    if( evt->type() == QEvent::Close )
    {
        hide();

        return true;
    }

    return QWidget::event(evt);
}

void DataDisplayWidget::setTotalNum(int i)
{
    ui->totalLabel->setText(QString::number(i));
}

CompolentInfoModel* DataDisplayWidget::getCompolentInfoModel()
{
    return &compolentModel;
}

DataSource* DataDisplayWidget::getConnection()
{
    return pConnect;
}

DataDisplayWidget::~DataDisplayWidget()
{
    delete ui;
    delete excelExporter;
    delete excelImporter;
}

bool DataDisplayWidget::eventFilter(QObject* obj, QEvent* evt)
{
    if( (obj == ui->tableView) && (evt->type() == QEvent::ContextMenu) )
    {
        m_menu.exec(cursor().pos());
    }

    return QWidget::eventFilter(obj, evt);
}

void DataDisplayWidget::on_refreshBtn_clicked()
{
    searchDly->clearCondition();

    search();
}

/**
* @brief         根据已有的查找条件查找对应数据
* @param         None
* @return        None
*/
void DataDisplayWidget::search()
{
    QString condition = searchDly->getCondition();

    totalCount = pConnect->count(condition);
    setTotalNum(totalCount);
    searchDly->setTotalCount(totalCount);

    int pageSize = ui->pageSizeComboBox->currentText().toInt();

    if(totalCount % pageSize == 0)
    {
        pageCount = totalCount / pageSize;
    }
    else
    {
        pageCount = totalCount / pageSize + 1;
    }

    ui->pageCountLbl->setText(QString::number(pageCount));
    ui->currentPageSpinBox->setMaximum(pageCount);

    currentPage = 1;
    currentPageChanged();
}

void DataDisplayWidget::on_deleteBtn_clicked()
{
    compolentModel.remove(ui->tableView->currentIndex().row());
    ui->totalLabel->setText(QString::number(compolentModel.count()));
}

void DataDisplayWidget::onClear()
{

}

void DataDisplayWidget::on_infoBtn_clicked()
{
    CompolentInfo obj;
    int currRow = ui->tableView->currentIndex().row();
    int currId = compolentModel.getItemId(currRow);

    DetailInfoDisplayDialog* detailInfoDly = new DetailInfoDisplayDialog(isEditable);

    detailInfoDly->setCurrRow(currRow);

    if(pConnect->selectData(obj,currId))
    { 
        detailInfoDly->setWindowTitle(obj.getName());
        detailInfoDly->setCompolentInfo(obj);
        detailInfoDly->getTabList()[0]->setCompolentInfoOnTab1(obj);
        detailInfoDly->exec();
    }
    else
    {
        showWarning(this,"提示","当前未选择有效数据！");
    }

    delete detailInfoDly;
}


void DataDisplayWidget::on_findBtn_clicked()
{
    searchDly->show();
}

void DataDisplayWidget::onCompleteDelete()
{
    if(showQuestion(this,"警告","此操作不可逆，你确定要将此数据彻底删除吗？") == QMessageBox::Yes)
    {
        if(pConnect->deleteDataById(compolentModel.getItemId(ui->tableView->currentIndex().row())))
        {
            on_deleteBtn_clicked();
        }
        else
        {
            showError(this,"错误","操作失败！");
        }
    }
}

void DataDisplayWidget::on_importBtn_clicked()
{
    QString path = FileTool::showFileDialog(this,QFileDialog::AcceptOpen,"请选择工作表",FileTool::Excel);

    if(!path.isEmpty())
    {
        if(path.endsWith(".xlsx") || path.endsWith(".xls"))
        {
            excelImporter->setPath(path);
            excelImporter->importStart();
        }
        else
        {
            showError(this,"失败","导入失败，仅支持Excel工作表！");
        }
    }
}

void DataDisplayWidget::on_exportBtn_clicked()
{
    if(compolentModel.count() > 0)
    {
        QString path = FileTool::showFileDialog(this,QFileDialog::AcceptSave,"另存为工作表",FileTool::Excel);

        if(!path.isEmpty())
        {
            excelExporter->setPath(path);
            excelExporter->exportStart();
        }
    }
}

void DataDisplayWidget::currentPageChanged()
{
    compolentModel.clear();

    if(1 <= currentPage && currentPage <= pageCount)
    {
        int pageSize = ui->pageSizeComboBox->currentText().toInt();

        if( pConnect->selectAllData(searchDly->getCondition(),currentPage,pageSize))
        {
            compolentModel.add(pConnect->fetchData());
            compolentModel.setView(ui->tableView);
            ui->currentPageSpinBox->setValue(currentPage);
        }
        else
        {
            ui->totalLabel->setText(QString::number(0));
            ui->pageCountLbl->setText(QString::number(0));
            showError(this, "错误", "数据库发生错误！");
        }
    }
}

int DataDisplayWidget::getPageSize()
{
    return ui->pageSizeComboBox->currentText().toInt();
}

void DataDisplayWidget::setPageSize(int i)
{
    ui->pageSizeComboBox->setCurrentText(QString::number(i));
}

void DataDisplayWidget::on_pageSizeComboBox_currentIndexChanged(const QString &)
{
    search();
}

void DataDisplayWidget::on_firstPageBtn_clicked()
{
    currentPage = 1;
    currentPageChanged();
}

void DataDisplayWidget::on_lastPageBtn_clicked()
{
    currentPage = pageCount;
    currentPageChanged();
}

void DataDisplayWidget::on_prePageBtn_clicked()
{
    if(1 < currentPage && currentPage <= pageCount)
    {
        currentPage--;
        currentPageChanged();
    }
}

void DataDisplayWidget::on_nextPageBtn_clicked()
{
    if(1 <= currentPage && currentPage < pageCount)
    {
        currentPage++;
        currentPageChanged();
    }
}

void DataDisplayWidget::on_gotoBtn_clicked()
{
    int gotoPage = ui->currentPageSpinBox->value();

    if(1 <= gotoPage && gotoPage <= pageCount)
    {
        currentPage = gotoPage;
        currentPageChanged();
    }
}

void DataDisplayWidget::onExportBegin()
{
    if(waitExporter == nullptr)
    {
        waitExporter = new WaitDialog();
        waitExporter->setLabelText("开始导出数据...");
        waitExporter->initTitle("导出");
        waitExporter->show();
    }
}

void DataDisplayWidget::onExporterSuccess()
{
    if(waitExporter != nullptr)
    {
        delete waitExporter;
        waitExporter = nullptr;

        showSuccess(this,"成功","导出成功！");
    }
}

void DataDisplayWidget::onExporterFaliure()
{
    if(waitExporter != nullptr)
    {
        delete waitExporter;
        waitExporter = nullptr;

        showError(this,"失败","导出失败！");
    }
}

void DataDisplayWidget::onImportBegin()
{
    if(waitImporter == nullptr)
    {
        waitImporter = new WaitDialog();
        waitImporter->setLabelText("开始导入数据...");
        waitImporter->initTitle("导入");
        waitImporter->show();
    }
}

void DataDisplayWidget::onImporterSuccess()
{
    if(waitImporter != nullptr)
    {
        delete waitImporter;
        waitImporter = nullptr;

        showSuccess(this,"成功","导入成功！");

        on_refreshBtn_clicked();
    }
}

void DataDisplayWidget::onImporterFaliure()
{
    if(waitImporter != nullptr)
    {
        delete waitImporter;
        waitImporter = nullptr;

        showError(this,"失败","导入失败！");
    }
}

void DataDisplayWidget::on_clearBtn_clicked()
{
    if(showQuestion(this,"警告","此操作不可逆，你确定要将数据表清空吗？") == QMessageBox::Yes)
    {
        if(pConnect->clear(searchDly->getCondition()))
        {
            showSuccess(this,"成功","数据表已清空！");
            on_refreshBtn_clicked();
        }
        else
        {
            showError(this,"失败","数据库错误！");
        }
    }
}
