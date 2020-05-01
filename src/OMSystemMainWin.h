/*******************************************************
* @projectName   OMSystem
* @brief         主窗口类，主要用于图像，视频操作，实时数据交互
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-03
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef OMSYSTEMMAINWIN_H
#define OMSYSTEMMAINWIN_H

#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QImage>
#include <QPainter>
#include <QMainWindow>
#include <QGridLayout>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>

#include "DataSource.h"
#include "DataDisplayWidget.h"
#include "DetailInfoDisplayDialog.h"
#include "DimensionInfo.h"

using namespace cv;

namespace Ui {
class OMSystemMainWin;
}

class OMSystemMainWin : public QMainWindow
{
    Q_OBJECT

    DataSource* pDataSource;
    DataDisplayWidget* pDataDisplayWidget;

    QLabel statusLbl;
    bool editable;
    bool sbVisible;
    bool isVideoOn;
    int timerId;

    OMSystemMainWin(DataSource* pds = nullptr);
    OMSystemMainWin(const OMSystemMainWin&);
    OMSystemMainWin& operator= (const OMSystemMainWin&);
    ~OMSystemMainWin();

    bool construct();

    bool initMenuBar();
    bool initToolBar();
    bool initStatusBar();

    bool initFileMenu(QMenuBar* mb);
    bool initControlMenu(QMenuBar* mb);
    bool initImageMenu(QMenuBar* mb);
    bool initSetMenu(QMenuBar* mb);
    bool initViewMenu(QMenuBar* mb);
    bool initHelpMenu(QMenuBar* mb);

    bool initFileToolItem(QToolBar* tb);
    bool initControlToolItem(QToolBar* tb);
    bool initImageToolItem(QToolBar* tb);
    bool initSetToolItem(QToolBar* tb);
    bool initViewToolItem(QToolBar* tb);
    bool initHelpToolItem(QToolBar* tb);

    bool makeAction(QAction*& action, QWidget* parent, QString text, int key);
    bool makeAction(QAction*& action, QWidget* parent, QString tip, QString icon);
    QAction* findMenuBarAction(QString text);
    QAction* findToolBarAction(QString text);

    void reset();

    void timerEvent(QTimerEvent* e);

public:

    static OMSystemMainWin* NewInstance(DataSource* pds);

    QToolBar* toolBar();

    bool isEditable();
    bool isSbVisible();
    int getPageSize();

    void setEditable(bool isEditable);
    void setSbVisible(bool sbVisible);
    void setPageSize(int pageSize);

signals:

    void signalClose();

private slots:

    void onFileOpen();

    void onFileSave();

    void onFileClose();

    void onControlVideo();

    void onControlTakePhoto();

    void onControlWidth();

    void onControlHeight();

    void onControlMeasure();

    void onControlCorrect();

    void onControlStop();

    void onHelpMunal();

    void onHelpAbout();

    void onViewStatusBar();

    void on_startBtn_clicked();

    void onImageBig();

    void onImageSmall();

    void setStatusText(double ratio);

    void setFilePath(const QString& path);

    void setData(const QList<double>& list);

public slots:

    void onViewAllData();

    void onViewEditable();

private:
    Ui::OMSystemMainWin *ui;

    QString filePath;

    Mat myVideo;
    QImage myQVideo;
    VideoCapture myCap;
};

#endif // OMSYSTEMMAINWIN_H
