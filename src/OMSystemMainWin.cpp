/*******************************************************
* @projectName   OMSystem
* @brief         主窗口类，主要用于图像，视频操作，实时数据交互
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-03
*******************************************************/

#include "ui_OMSystemMainWin.h"
#include "OMSystemMainWin.h"
#include "DetailDataTabWidget.h"
#include "FileTool.h"
#include "OMSystem.h"
#include "CustomWindow/MessageBox.h"
#include "PaintTool.h"
#include "CoreArithmetic.h"

#include <QObjectList>
#include <QIcon>
#include <QStatusBar>
#include <QList>
#include <QDebug>
#include <QDir>
#include <QCursor>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QApplication>
#include <QFile>
#include <QtConcurrent>
#include <QTableWidgetItem>
#include <QToolButton>
#include <QFileInfo>

QImage Mat2QImage(Mat cvImg);

OMSystemMainWin::OMSystemMainWin(DataSource* pds) :
    pDataSource(pds),editable(false),sbVisible(true),isVideoOn(false),
    ui(new Ui::OMSystemMainWin)
{
    ui->setupUi(this);
    ui->dataTable->setRowCount(0);
    ui->dataTable->setColumnCount(2);
    ui->dataTable->setColumnWidth(0,60);
    ui->dataTable->setColumnWidth(1,160);
    setContextMenuPolicy(Qt::NoContextMenu);

    connect(ui->imgWidget,SIGNAL(signalRatioChanged(double)),this,SLOT(setStatusText(double)));
    connect(ui->imgWidget,SIGNAL(signalFileChanged(const QString&)),this,SLOT(setFilePath(const QString&)));
    connect(ui->imgWidget,SIGNAL(signalData(const QList<double>&)),this,SLOT(setData(const QList<double>&)));
}

OMSystemMainWin* OMSystemMainWin::NewInstance(DataSource* pds)
{
    OMSystemMainWin* ret = new OMSystemMainWin(pds);

    if( (ret == nullptr) || !ret->construct() )
    {
        delete ret;
        ret = nullptr;
    }

    FileTool::loadSyleSheet(ret,"OMSystemMainWin");

    return ret;
}

/**
* @brief         初始化主窗口
* @param         None
* @return        初始化是否成功
*/
bool OMSystemMainWin::construct()
{
    bool ret = true;

    ret = ret && initMenuBar();
    ret = ret && initToolBar();
    ret = ret && initStatusBar();

    pDataDisplayWidget = new DataDisplayWidget(&editable,pDataSource);

    ret = ret && (pDataDisplayWidget != nullptr);
    return ret;
}

bool OMSystemMainWin::isEditable()
{
    return editable;
}

bool OMSystemMainWin::isSbVisible()
{
    return sbVisible;
}

int OMSystemMainWin::getPageSize()
{
    return pDataDisplayWidget->getPageSize();
}

void OMSystemMainWin::setEditable(bool isEditable)
{
    editable = isEditable;
    findMenuBarAction("可编辑")->setChecked(isEditable);
    findToolBarAction("可编辑")->setChecked(isEditable);
}

void OMSystemMainWin::setSbVisible(bool sbVisible)
{
    this->sbVisible = sbVisible;
    statusBar()->setVisible(sbVisible);
    findMenuBarAction("状态栏")->setChecked(sbVisible);
    findToolBarAction("状态栏")->setChecked(sbVisible);
}

void OMSystemMainWin::setPageSize(int pageSize)
{
    pDataDisplayWidget->setPageSize(pageSize);
}

bool OMSystemMainWin::initMenuBar()
{
    bool ret = true;

    QMenuBar* mb = menuBar();

    ret = ret && initFileMenu(mb);
    ret = ret && initControlMenu(mb);
    ret = ret && initImageMenu(mb);
    ret = ret && initSetMenu(mb);
    ret = ret && initViewMenu(mb);
    ret = ret && initHelpMenu(mb);

    return ret;
}

bool OMSystemMainWin::initToolBar()
{
    bool ret = true;

    QToolBar* tb = toolBar();

    ret = ret && initFileToolItem(tb);
    ret = ret && initControlToolItem(tb);
    ret = ret && initImageToolItem(tb);
    ret = ret && initSetToolItem(tb);
    ret = ret && initViewToolItem(tb);
    ret = ret && initHelpToolItem(tb);

    return ret;
}

bool OMSystemMainWin::initStatusBar()
{
    bool ret = true;
    QStatusBar* sb = statusBar();
    QLabel* label = new QLabel("Xi'an Jiao Tong University");
    label->setStyleSheet("color:white;font:12pt '等线'");

    if( label != nullptr )
    {
        statusLbl.setMinimumWidth(700);
        statusLbl.setAlignment(Qt::AlignCenter);
        statusLbl.setText("当前放大倍数 ：100 %");
        statusLbl.setStyleSheet("color:white;font:12pt '等线'");

        label->setMinimumWidth(200);
        label->setAlignment(Qt::AlignCenter);

        sb->addPermanentWidget(new QLabel());
        sb->addPermanentWidget(&statusLbl);
        sb->addPermanentWidget(label);
     }
     else
     {
        ret = false;
     }

     return ret;
}

bool OMSystemMainWin::initFileMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("文件(&F)", mb);
    bool ret = (menu != nullptr);

    if( ret )
    {
        QAction* action = nullptr;

        ret = ret && makeAction(action, menu, "打开(&O)", Qt::CTRL + Qt::Key_O);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onFileOpen()));
        }

        ret = ret && makeAction(action, menu, "另存为(&S)", Qt::CTRL + Qt::Key_S);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onFileSave()));
        }

        menu->addSeparator();

        ret = ret && makeAction(action, menu, "退出(&X)",0);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onFileClose()));
        }
    }

    if( ret )
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

bool OMSystemMainWin::initControlMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("控制(&I)", mb);
    bool ret = (menu != nullptr);

    if( ret )
    {
        QAction* action = nullptr;

        ret = ret && makeAction(action, menu, "摄像头", 0);

        if( ret )
        {
            menu->addAction(action);
            action->setCheckable(true);
            action->setChecked(false);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlVideo()));
        }

        ret = ret && makeAction(action, menu, "拍照(&P)", Qt::CTRL + Qt::Key_P);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlTakePhoto()));
        }

        menu->addSeparator();

        ret = ret && makeAction(action, menu, "宽",0);

        if( ret )
        {
            action->setCheckable(true);
            action->setChecked(false);
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlWidth()));
        }

        ret = ret && makeAction(action, menu, "高",0);

        if( ret )
        {
            action->setCheckable(true);
            action->setChecked(false);
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlHeight()));
        }

        ret = ret && makeAction(action, menu, "测量(&B)", Qt::CTRL + Qt::Key_B);

        if( ret )
        {
            menu->addAction(action);
            action->setCheckable(true);
            action->setChecked(false);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlMeasure()));
        }

        ret = ret && makeAction(action, menu, "矫正",0);

        if( ret )
        {
            action->setCheckable(true);
            action->setChecked(ui->imgWidget->getCorrectMode());
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlCorrect()));
        }

        menu->addSeparator();

        ret = ret && makeAction(action, menu, "清空图像区(&Q)", Qt::CTRL + Qt::Key_Q);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlStop()));
        }
    }

    if( ret )
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

bool OMSystemMainWin::initImageMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("图像(&M)", mb);
    bool ret = (menu != nullptr);

    if( ret )
    {
        QAction* action = nullptr;

        ret = ret && makeAction(action, menu, "放大", Qt::Key_Plus);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onImageBig()));
        }

        ret = ret && makeAction(action, menu, "缩小", Qt::Key_Minus);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onImageSmall()));
        }
    }

    if( ret )
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

bool OMSystemMainWin::initSetMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("设置(&P)", mb);
    bool ret = (menu != nullptr);

    if( ret )
    {
        QAction* action = nullptr;

        ret = ret && makeAction(action, menu, "可编辑(&E)", Qt::CTRL + Qt::Key_E);

        if( ret )
        {
            action->setCheckable(true);
            action->setChecked(false);
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onViewEditable()));
        }

        mb->addSeparator();

        ret = ret && makeAction(action, menu, "状态栏", 0);

        if( ret )
        {
            action->setCheckable(true);
            action->setChecked(true);
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onViewStatusBar()));
        }
    }

    if( ret )
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

bool OMSystemMainWin::initViewMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("查看(&V)", mb);
    bool ret = (menu != nullptr);

    if( ret )
    {
        QAction* action = nullptr;

        ret = ret && makeAction(action, menu, "数据对比(&C)", Qt::CTRL + Qt::Key_L);

        if( ret )
        {
            menu->addAction(action);
        }

        ret = ret && makeAction(action, menu, "详细信息(&F)", Qt::CTRL + Qt::Key_F);

        if( ret )
        {
            menu->addAction(action);
        }

        ret = ret && makeAction(action, menu, "全部数据(&W)", Qt::CTRL + Qt::Key_W);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onViewAllData()));
        }

    }

    if( ret )
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

bool OMSystemMainWin::initHelpMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("帮助(&H)", mb);
    bool ret = (menu != nullptr);

    if( ret )
    {
        QAction* action = nullptr;

        ret = ret && makeAction(action, menu, "用户手册", 0);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onHelpMunal()));
        }

        ret = ret && makeAction(action, menu, "关于OMSystem...", 0);

        if( ret )
        {
            menu->addAction(action);
            connect(action,SIGNAL(triggered(bool)),this,SLOT(onHelpAbout()));
        }
    }

    if( ret )
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

bool OMSystemMainWin::initFileToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = nullptr;

    ret = ret && makeAction(action, tb, "打开", ":/res/pic/openfile.png");

    if( ret )
    {
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onFileOpen()));
    }

    ret = ret && makeAction(action, tb, "另存为", ":/res/pic/save.png");

    if( ret )
    {
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onFileSave()));
    }

    return ret;
}

bool OMSystemMainWin::initControlToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = nullptr;

    ret = ret && makeAction(action, tb, "摄像头", ":/res/pic/open.png");

    if( ret )
    {
        action->setCheckable(true);
        action->setChecked(false);
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlVideo()));
    }

    ret = ret && makeAction(action, tb, "拍照", ":/res/pic/photo.png");

    if( ret )
    {
        tb->addAction(action);
         connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlTakePhoto()));
    }

    tb->addSeparator();

    ret = ret && makeAction(action, tb, "宽", ":/res/pic/width.png");

    if( ret )
    {
        tb->addAction(action);
        action->setCheckable(true);
        action->setChecked(false);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlWidth()));
    }

    ret = ret && makeAction(action, tb, "高", ":/res/pic/height.png");

    if( ret )
    {
        tb->addAction(action);
        action->setCheckable(true);
        action->setChecked(false);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlHeight()));
    }

    ret = ret && makeAction(action, tb, "测量", ":/res/pic/start.png");

    if( ret )
    {
        tb->addAction(action);
        action->setCheckable(true);
        action->setChecked(false);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlMeasure()));
    }

    ret = ret && makeAction(action, tb, "矫正", ":/res/pic/correct.png");

    if( ret )
    {
        action->setCheckable(true);
        action->setChecked(ui->imgWidget->getCorrectMode());
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlCorrect()));
    }

    ret = ret && makeAction(action, tb, "清空图像区", ":/res/pic/stop.png");

    if( ret )
    {
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onControlStop()));
    }

    return ret;
}

bool OMSystemMainWin::initImageToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = nullptr;

    tb->addSeparator();

    ret = ret && makeAction(action, tb, "放大", ":/res/pic/big.png");

    if( ret )
    {
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onImageBig()));
    }

    ret = ret && makeAction(action, tb, "缩小", ":/res/pic/small.png");

    if( ret )
    {
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onImageSmall()));
    }

    return ret;
}

bool OMSystemMainWin::initSetToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = nullptr;

    ret = ret && makeAction(action, tb, "可编辑", ":/res/pic/edit.png");

    if( ret )
    {
        action->setCheckable(true);
        action->setChecked(false);
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onViewEditable()));
    }

    ret = ret && makeAction(action, tb, "状态栏", ":/res/pic/status.png");

    if( ret )
    {
        action->setCheckable(true);
        action->setChecked(true);
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onViewStatusBar()));
    }

    return ret;
}

bool OMSystemMainWin::initViewToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = nullptr;


    ret = ret && makeAction(action, tb, "数据对比", ":/res/pic/compare.png");

    if( ret )
    {
        tb->addAction(action);
    }

    ret = ret && makeAction(action, tb, "详细信息", ":/res/pic/info.png");

    if( ret )
    {
        tb->addAction(action);
    }


    ret = ret && makeAction(action, tb, "全部数据", ":/res/pic/whole.png");

    if( ret )
    {
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onViewAllData()));
    }

    return ret;
}

bool OMSystemMainWin::initHelpToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = nullptr;

    ret = ret && makeAction(action, tb, "用户手册", ":/res/pic/munal.png");

    if( ret )
    {
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onHelpMunal()));
    }

    ret = ret && makeAction(action, tb, "关于OMSystem...", ":/res/pic/about.png");

    if( ret )
    {
        tb->addAction(action);
        connect(action,SIGNAL(triggered(bool)),this,SLOT(onHelpAbout()));
    }

    return ret;
}

/**
* @brief         初始化菜单项
* @param         action:空菜单项
*                parent:父组件
*                text:名称
*                key:快捷键
* @return        是否初始化成功
*/
bool OMSystemMainWin::makeAction(QAction*& action, QWidget* parent, QString text, int key)
{
    bool ret = true;

    action = new QAction(text, parent);

    if( action != nullptr )
    {
        action->setShortcut(QKeySequence(key));
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         初始化工具栏选项
* @param         action:空工具栏选项
*                parent:父组件
*                text:名称
*                key:快捷键
* @return        是否初始化成功
*/
bool OMSystemMainWin::makeAction(QAction*& action, QWidget* parent, QString tip, QString icon)
{
    bool ret = true;

    action = new QAction("", parent);

    if( action != nullptr )
    {
        action->setToolTip(tip);
        action->setIcon(QIcon(icon));
    }
    else
    {
        ret = false;
    }

    return ret;
}

/**
* @brief         找到特定菜单项
* @param         text:菜单项名称
* @return        菜单项指针
*/
QAction* OMSystemMainWin::findMenuBarAction(QString text)
{
    QAction* ret = nullptr;
    const QObjectList& list = menuBar()->children();

    for(int i=0; i<list.count(); i++)
    {
        QMenu* menu = dynamic_cast<QMenu*>(list[i]);

        if( menu != nullptr )
        {
            QList<QAction*> actions = menu->actions();

            for(int j=0; j<actions.count(); j++)
            {
                if( actions[j]->text().startsWith(text) )
                {
                    ret = actions[j];
                    break;
                }
            }
        }
    }

    return ret;
}

/**
* @brief         找到特定工具栏选项
* @param         text:工具栏选项名称
* @return        工具栏选项
*/
QAction* OMSystemMainWin::findToolBarAction(QString text)
{
    QAction* ret = nullptr;
    QList<QAction*> actions = toolBar()->actions();

    for(int j=0; j<actions.count(); j++)
    {
        if( actions[j]->toolTip().startsWith(text) )
        {
            ret = actions[j];
            break;
        }
    }

    return ret;
}

QToolBar* OMSystemMainWin::toolBar()
{
    QToolBar* ret = nullptr;
    const QObjectList& list = children();

    for(int i=0; i<list.count(); i++)
    {
        QToolBar* tb = dynamic_cast<QToolBar*>(list[i]);

        if( tb != nullptr )
        {
            ret = tb;
            break;
        }
    }

    return ret;
}

void OMSystemMainWin::reset()
{
    QFile::remove(QApplication::applicationDirPath() + "/temp/dimension.xml");
    ui->dataTable->setRowCount(0);
    findMenuBarAction("宽")->setChecked(false);
    findToolBarAction("宽")->setChecked(false);
    findMenuBarAction("高")->setChecked(false);
    findToolBarAction("高")->setChecked(false);
    ui->imgWidget->changeSelectMode(MeasureType::Global);
    findMenuBarAction("测量")->setChecked(false);
    findToolBarAction("测量")->setChecked(false);
    findToolBarAction("测量")->setIcon(QIcon(QPixmap(":/res/pic/start.png")));
    ui->imgWidget->changeMeasureMode(false);
    findMenuBarAction("矫正")->setChecked(false);
    findToolBarAction("矫正")->setChecked(false);
    ui->imgWidget->changeCorrectMode(false);
    ui->startBtn->setText("开始测量");
    ui->imgWidget->initImgPara();
}

void OMSystemMainWin::timerEvent(QTimerEvent*)
{
    myCap >> myVideo;
    myQVideo = Mat2QImage(myVideo);
    ui->video->setPixmap(QPixmap::fromImage(myQVideo));
}

OMSystemMainWin::~OMSystemMainWin()
{
    delete ui;
    FileTool::removeFolderContent(QApplication::applicationDirPath() + "/temp");
}

void OMSystemMainWin::onControlVideo()
{
    isVideoOn = !isVideoOn;

    findMenuBarAction("摄像头")->setChecked(isVideoOn);
    findToolBarAction("摄像头")->setChecked(isVideoOn);

    if(isVideoOn)
    {
        int camid = 0;

        if(!myCap.open(camid))
        {
            ui->video->setPixmap(QPixmap(":/res/pic/nosignal.png"));
            timerId = -1;

            showError(this,"错误","无法获取摄像头或视频通道已被占用！");
        }
        else
        {
            if(myCap.read(myVideo))
            {
                timerId = startTimer(20);
            }
            else
            {
                ui->video->setPixmap(QPixmap(":/res/pic/nosignal.png"));
                timerId = -1;

                showError(this,"错误","无法获取摄像头或视频通道已被占用！");
            }
        }
    }
    else
    {
        myCap.release();
        myVideo.release();

        if(timerId >= 0)
        {
            killTimer(timerId);
        }

        ui->video->clear();
    }
}

void OMSystemMainWin::onControlTakePhoto()
{
    if(!myVideo.empty())
    {
        ui->imgWidget->takePtoto(myVideo);
    }
}

void OMSystemMainWin::onControlWidth()
{
    if(ui->imgWidget->getMeasureMode())
    {
        onControlMeasure();
    }

    if(ui->imgWidget->getSelectMode() != MeasureType::Width)
    {
        ui->imgWidget->changeSelectMode(MeasureType::Width);
        ui->imgWidget->clearPoints();
        findMenuBarAction("宽")->setChecked(true);
        findToolBarAction("宽")->setChecked(true);
        findMenuBarAction("高")->setChecked(false);
        findToolBarAction("高")->setChecked(false);
    }
    else
    {
        ui->imgWidget->changeSelectMode(MeasureType::Global);
        findMenuBarAction("宽")->setChecked(false);
        findToolBarAction("宽")->setChecked(false);
    }

    ui->imgWidget->updateImage();
}

void OMSystemMainWin::onControlHeight()
{
    if(ui->imgWidget->getMeasureMode())
    {
        onControlMeasure();
    }

    if(ui->imgWidget->getSelectMode() != MeasureType::Height)
    {
        ui->imgWidget->changeSelectMode(MeasureType::Height);
        ui->imgWidget->clearPoints();
        findMenuBarAction("高")->setChecked(true);
        findToolBarAction("高")->setChecked(true);
        findMenuBarAction("宽")->setChecked(false);
        findToolBarAction("宽")->setChecked(false);
    }
    else
    {
        ui->imgWidget->changeSelectMode(MeasureType::Global);
        findMenuBarAction("高")->setChecked(false);
        findToolBarAction("高")->setChecked(false);
    }

    ui->imgWidget->updateImage();
}

void OMSystemMainWin::onControlMeasure()
{    
    QFile::remove(QApplication::applicationDirPath() + "/temp/dimension.xml");

    if(ui->imgWidget->hasImage())
    {
        ui->imgWidget->changeMeasureMode();
        findMenuBarAction("测量")->setChecked(ui->imgWidget->getMeasureMode());
        findToolBarAction("测量")->setChecked(ui->imgWidget->getMeasureMode());

        if(ui->imgWidget->getMeasureMode())
        {
            findToolBarAction("测量")->setIcon(QIcon(QPixmap(":/res/pic/starting.png")));
            ui->startBtn->setText("结束测量");

            if(!filePath.isEmpty())
            {
                if(ui->imgWidget->getSelectMode() == MeasureType::Global)
                {
                    CoreArithmetic::mathc_img(filePath,
                                              QApplication::applicationDirPath() + "/template/3-26template2.jpg");
                    QString measureFile = QApplication::applicationDirPath() + "/temp/measure.jpg";
                    QFileInfo fileInfo(measureFile);

                    if(fileInfo.exists())
                    {
                        filePath = measureFile;
                        ui->imgWidget->fileOpen(filePath);

                        QPoint w1(15,4);
                        QPoint w2(145,22);
                        CoreArithmetic::findLine(w1,w2,"top");

                        QPoint w3(177,4);
                        QPoint w4(305,20);
                        CoreArithmetic::findLine(w3,w4,"top");

                        QPoint w5(13,87);
                        QPoint w6(145,101);
                        CoreArithmetic::findLine(w5,w6,"bottom");

                        QPoint w7(178,85);
                        QPoint w8(304,100);
                        CoreArithmetic::findLine(w7,w8,"bottom");

                        QPoint h1(72,6);
                        QPoint h2(76,107);
                        CoreArithmetic::distanceCalculate(h1,h2,"left");

                        QPoint h3(241,7);
                        QPoint h4(243,104);
                        CoreArithmetic::distanceCalculate(h3,h4,"right");
                    }

                    QtConcurrent::run(ui->imgWidget,&ImageHandlerWidget::globalMeasure,filePath);
                }
            }
        }
        else
        {
            if(ui->imgWidget->getCorrectMode())
            {
                onControlCorrect();
            }

            findToolBarAction("测量")->setIcon(QIcon(QPixmap(":/res/pic/start.png")));
            ui->startBtn->setText("开始测量");
        }

        ui->imgWidget->updateImage();
    }
    else
    {
        findMenuBarAction("测量")->setChecked(false);
        findToolBarAction("测量")->setChecked(false);
        findToolBarAction("测量")->setIcon(QIcon(QPixmap(":/res/pic/start.png")));
        ui->imgWidget->changeMeasureMode(false);
        ui->startBtn->setText("开始测量");

        showWarning(this,"警告","图像区没有任何待测图片！");
    }
}

void OMSystemMainWin::onControlCorrect()
{
    if(ui->imgWidget->getMeasureMode())
    {
        ui->imgWidget->changeCorrectMode();

        findMenuBarAction("矫正")->setChecked(ui->imgWidget->getCorrectMode());
        findToolBarAction("矫正")->setChecked(ui->imgWidget->getCorrectMode());
    }
    else
    {
        ui->imgWidget->changeCorrectMode(false);

        findMenuBarAction("矫正")->setChecked(false);
        findToolBarAction("矫正")->setChecked(false);

        showInformation(this,"提示","请在测量模式下使用！");
    }
}

void OMSystemMainWin::onControlStop()
{
    reset();
    ui->imgWidget->updateImage();
}

void OMSystemMainWin::onFileOpen()
{
    QString path = FileTool::showFileDialog(this,QFileDialog::AcceptOpen,"请选择图片",FileTool::Image);

    if(!path.isEmpty())
    {
        QFile::remove(QApplication::applicationDirPath() + "/temp/measure.jpg");
        filePath = path;
        reset();
        ui->imgWidget->fileOpen(path);
    }
}

void OMSystemMainWin::onFileSave()
{
    if(!ui->imgWidget->hasImage())
    {
        return;
    }

    QString path = FileTool::showFileDialog(this,QFileDialog::AcceptSave,"另存为",FileTool::Image);

    if(path.isEmpty())
    {
        return;
    }

    ui->imgWidget->fileSave(path);
}

void OMSystemMainWin::onFileClose()
{
    emit signalClose();
}

void OMSystemMainWin::onViewAllData()
{
    pDataDisplayWidget->show();
    pDataDisplayWidget->activateWindow();
}

void OMSystemMainWin::onHelpMunal()
{
    QString path = "file:///" + QApplication::applicationDirPath() + "/西安交通大学光学测量系统使用手册.doc";
    //qDebug() << path;
    QDesktopServices::openUrl(QUrl(path));
}

void OMSystemMainWin::onHelpAbout()
{

}

void OMSystemMainWin::onViewEditable()
{
    editable = !editable;

    findMenuBarAction("可编辑")->setChecked(editable);
    findToolBarAction("可编辑")->setChecked(editable);

    foreach (QWidget* w, QApplication::allWidgets())
    {
        DetailInfoDisplayDialog* detailDly = dynamic_cast<DetailInfoDisplayDialog*>(w);

        if(detailDly != nullptr)
        {
            detailDly->setEditable(editable);

            QList<DetailDataTabWidget*> tbList = detailDly->getTabList();

            for(int i = 0;i < tbList.count();i++)
            {
                tbList[i]->setEditable(editable);
            }
        }
    }
}

void OMSystemMainWin::onViewStatusBar()
{
    sbVisible = !sbVisible;

    QStatusBar* sb = statusBar();
    sb->setVisible(sbVisible);
    findMenuBarAction("状态栏")->setChecked(sbVisible);
    findToolBarAction("状态栏")->setChecked(sbVisible);
}

void OMSystemMainWin::on_startBtn_clicked()
{
    onControlMeasure();
}

void OMSystemMainWin::onImageBig()
{
    ui->imgWidget->imageBig();
}

void OMSystemMainWin::onImageSmall()
{
    ui->imgWidget->imageSmall();
}

void OMSystemMainWin::setStatusText(double ratio)
{
    statusLbl.setText("当前放大倍数 ：" + QString::number(ratio) + " %");
}

void OMSystemMainWin::setFilePath(const QString& path)
{
    reset();
    filePath = path;
}

void OMSystemMainWin::setData(const QList<double>& list)
{
    ui->dataTable->setRowCount(list.count());

    for (int i = 0;i < list.count();i++)
    {
        QTableWidgetItem* num = new QTableWidgetItem("[" + QString::number(i + 1) + "]");
        num->setTextColor(Qt::white);
        num->setFont(QFont("黑体",15));
        num->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(list[i]) + "px");
        item->setTextColor(Qt::green);
        item->setFont(QFont("黑体",15));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        ui->dataTable->setItem(i,0,num);
        ui->dataTable->setItem(i,1,item);
    }
}

/**
* @brief         将Mat转换为QImage(仅用于读取视频，图像不可用)
* @param         cvImg:Mat数据
* @return        QImage数据
*/
QImage Mat2QImage(Mat cvImg)
{
    QImage qImg;

    cvtColor(cvImg, cvImg, CV_BGR2RGB);
    qImg = QImage(reinterpret_cast<const unsigned char*>(cvImg.data),cvImg.cols, cvImg.rows,
                  cvImg.cols * cvImg.channels(),QImage::Format_RGB888);

    return qImg;
}
