/*******************************************************
* @projectName   OMSystem
* @brief         详细信息展示窗口，用于整合数据库的一行数据
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef DETAILINFODISPLAYDIALOG_H
#define DETAILINFODISPLAYDIALOG_H

#include <QDialog>
#include <QList>
#include <QFileDialog>
#include <QPoint>
#include <QImage>
#include <QRect>
#include <QStringList>
#include <QMenu>

#include "DetailDataTabWidget.h"
#include "DataSource.h"
#include "WordHandler.h"
#include "XVideoUI.h"

namespace Ui {
class DetailInfoDisplayDialog;
}

class DetailInfoDisplayDialog : public QDialog
{
    Q_OBJECT

    int currRow;
    DataSource* pConnect;
    bool* m_editable;
    WordHandler* wordThread;

    DetailDataTabWidget* tab1;
    DetailDataTabWidget* tab2;
    QList<DetailDataTabWidget*> tabList;

    QRect rec;
    CompolentInfo obj;

    QStringList imgList;
    int index;

    QString videoPath;

    QMenu menu;

    void initTabWidget();
    void initMenu();

    void display();
    void showImg(const QString& path);

    void initImageList();
    void initVideoPath();

    bool event(QEvent* e);
    bool eventFilter(QObject* obj, QEvent* evt);

public:

    DetailInfoDisplayDialog(bool* editable = nullptr,QWidget *parent = nullptr);
    ~DetailInfoDisplayDialog();

    QList<DetailDataTabWidget*>& getTabList();
    void setEditable(bool editable);
    void setCompolentInfo(CompolentInfo& obj);
    void setCurrRow(int row);

protected:

    void paintEvent(QPaintEvent *);

private slots:

    void on_editCheckBox_clicked();

    void on_cancelBtn_clicked();

    void on_preBtn_clicked();

    void on_nextBtn_clicked();

    void on_wordBtn_clicked();

    void on_picBtn_clicked();

    void on_saveBtn_clicked();

    void onWordSuccess();

    void onWordFaliure();

    void on_preImgBtn_clicked();

    void on_nextImgBtn_clicked();

    void onViewBigImage();

    void onViewVideo();

private:
    Ui::DetailInfoDisplayDialog *ui;
};

#endif // DETAILINFODISPLAYDIALOG_H
