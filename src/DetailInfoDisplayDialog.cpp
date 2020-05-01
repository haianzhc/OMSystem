/*******************************************************
* @projectName   OMSystem
* @brief         详细信息展示窗口，用于整合数据库的一行数据
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-10
*******************************************************/

#include "ui_DetailInfoDisplayDialog.h"
#include "DetailInfoDisplayDialog.h"
#include "OMSystemMainWin.h"
#include "CompolentInfo.h"
#include "DataDisplayWidget.h"
#include "CompolentInfoModel.h"
#include "BigImageDialog.h"
#include "FileTool.h"
#include "CustomWindow/MessageBox.h"
#include "XVideoUI.h"

#include <QDebug>
#include <QPixmap>
#include <QScreen>
#include <QBitmap>
#include <QPainter>
#include <QDir>
#include <QApplication>
#include <QStringList>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPlainTextEdit>

static bool press = false;
static QPoint last;

DetailInfoDisplayDialog::DetailInfoDisplayDialog(bool* editable,QWidget *parent) :
    QDialog(parent,Qt::WindowCloseButtonHint),currRow(-1),m_editable(editable),
    tab1(new DetailDataTabWidget(editable)),tab2(new DetailDataTabWidget(editable)),
    rec(80,310,171,171),menu(this),
    ui(new Ui::DetailInfoDisplayDialog)
{
    pConnect = new DataSource("root","xjtuzhc",this);

    ui->setupUi(this);
    ui->imgLabel->installEventFilter(this);

    setEditable(*m_editable);
    initTabWidget();
    initMenu();

    QPixmap pix;
    pix.load(":/res/pic/1.png",nullptr,Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
    resize(pix.size());
    setMask(QBitmap(pix.mask()));

    wordThread = new WordHandler();

    connect(wordThread,SIGNAL(wordSuccess()),this,SLOT(onWordSuccess()));
    connect(wordThread,SIGNAL(wordFaliure()),this,SLOT(onWordFaliure()));
}

DetailInfoDisplayDialog::~DetailInfoDisplayDialog()
{
    delete wordThread;
    delete ui;
}

/**
* @brief         初始化标签页
* @param         None
* @return        None
*/
void DetailInfoDisplayDialog::initTabWidget()
{
    ui->tabWidget->addTab(tab1,"第一页");
    ui->tabWidget->addTab(tab2,"第二页");

    int w = ui->tabWidget->width();

    QString str = QString("QTabBar::tab{width: %1px;height:46px;font:20px;color:black}").arg(w/3-20);
    str.append("QTabWidget::pane{border-width: 1px;border-color:black;border-style:outset;\
               background-color: white;border-radius: 25px;}");
    str.append("QTabWidget::tab-bar{left:20px;}");    
    str.append("QTabBar::tab:selected{margin-left: 1;margin-right: 0;\
               color: black;background-color:rbg(100,200,255);}");
    str.append("QTabBar::tab:!selected{margin-left: 1;margin-right: 0;\
               color: red;background-color:rbg(50,100,255);}");
    str.append("QTabBar::tab:hover:!selected{color: white;margin-left: 1;\
               margin-right: 0;background-color:rbg(100,200,100);}");
    str.append("QTabBar::tab:!selected{margin-top: 10px;margin-bottom: -10px;}");

    ui->tabWidget->setStyleSheet(str);

    tabList.append(tab1);
    tabList.append(tab2);

    tab1->setDataLabelName("名称：","参数0：","参数1：","参数2：","参数3：","参数4：","参数5：","参数6：","参数7：","参数8：",
                           "参数9：","参数10：","参数11：","参数12：","参数13：","参数14：","参数15：","参数16：","参数17：",
                           "参数18：");
    tab2->setDataLabelName("参数19：","参数20：","参数21：","参数22：","参数23：","参数24：","参数25：","参数26：","参数27：",
                           "参数28：","参数29：","参数30：","参数31：","参数32：","参数33：","参数34：","参数35：","参数36：",
                           "参数37：","参数38：");
}

void DetailInfoDisplayDialog::setEditable(bool editable)
{
    ui->infoTextEdit->setReadOnly(!editable);
    ui->editCheckBox->setChecked(editable);

    if(!imgList.isEmpty())
    {
        ui->closeBtn->setVisible(editable);
    }
    else
    {
        ui->closeBtn->setVisible(false);
    }

    ui->addBtn->setVisible(editable);
}

 void DetailInfoDisplayDialog::initImageList()
 {
     QString dirpath = obj.getResourceUrl() + "/image/";
     QStringList nameFilters;
     nameFilters << "*.jpg" << "*.png";

     FileTool::findFilesInDir(dirpath,nameFilters,imgList);
 }

 void DetailInfoDisplayDialog::initVideoPath()
 {
     QString dirpath = obj.getResourceUrl() + "/video/";
     QStringList nameFilters,videoNames;
     nameFilters << "*.avi" << "*.mp4";

     FileTool::findFilesInDir(dirpath,nameFilters,videoNames);

     if(!videoNames.isEmpty())
     {
         videoPath = videoNames[0];
     }
 }

void DetailInfoDisplayDialog::setCompolentInfo(CompolentInfo& obj)
{
    imgList.clear();
    index = 0;

    this->obj = obj;
    wordThread->setCompolentInfo(obj);

    initImageList();
    initVideoPath();

    display();
    setEditable(*m_editable);
}

void DetailInfoDisplayDialog::display()
{
    ui->infoTextEdit->clear();
    ui->infoTextEdit->insertPlainText(obj.getInfo());

    ui->timeLbl->setText(obj.getTime().toString("yyyy-MM-dd hh:mm:ss"));

    if(!imgList.isEmpty())
    {
        showImg(imgList[0]);
    }
}

void DetailInfoDisplayDialog::showImg(const QString& path)
{
    ui->imgLabel->clear();
    QImage img(path);
    ui->imgLabel->setPixmap(QPixmap::fromImage(img.scaled(ui->imgLabel->size(),Qt::KeepAspectRatio)));
}

QList<DetailDataTabWidget*>& DetailInfoDisplayDialog::getTabList()
{
    return tabList;
}

void DetailInfoDisplayDialog::setCurrRow(int row)
{
    currRow = row;
}

void DetailInfoDisplayDialog::initMenu()
{
    menu.addAction("查看大图");
    menu.addAction("查看视频");

    connect(menu.actions()[0],SIGNAL(triggered(bool)),this,SLOT(onViewBigImage()));
    connect(menu.actions()[1],SIGNAL(triggered(bool)),this,SLOT(onViewVideo()));
}

bool DetailInfoDisplayDialog::event(QEvent* e)
{
    if(e->type() == QEvent::MouseButtonPress )
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(e);

        if(mouse->button() == Qt::LeftButton)
        {
            if(rec.contains(mouse->pos()))
            {
                if(!(*m_editable))
                {
                    onViewBigImage();
                }
            }
            else
            {
                press = true;

                last = mouse->globalPos();
            }
        }
    }

    if(e->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(e);

        if(rec.contains(mouse->pos()))
        {
            if(!(*m_editable))
            {
                setCursor(QCursor(QPixmap(":/res/pic/bigImg.png")));
            }
        }
        else
        {
            setCursor(Qt::ArrowCursor);
        }

        if(press)
        {
            int dx = mouse->globalX() - last.x();
            int dy = mouse->globalY() - last.y();
            last = mouse->globalPos();
            move(x() + dx, y() + dy);
        }
     }


    if(e->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(e);

        if(mouse->button() == Qt::LeftButton && press )
        {
            press = false;

            int dx = mouse->globalX() - last.x();
            int dy = mouse->globalY() - last.y();
            move(x() + dx, y() + dy);
        }
    }

    return QWidget::event(e);
}

void DetailInfoDisplayDialog::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(0,0,QPixmap(":/res/pic/1.png"));
}

bool DetailInfoDisplayDialog::eventFilter(QObject* obj, QEvent* evt)
{
    if( (obj == ui->imgLabel) && (evt->type() == QEvent::ContextMenu) )
    {
        menu.exec(cursor().pos());
    }

    return QDialog::eventFilter(obj, evt);
}

void DetailInfoDisplayDialog::on_editCheckBox_clicked()
{
    foreach (QWidget* w, QApplication::allWidgets())
    {
        OMSystemMainWin* mainWin = dynamic_cast<OMSystemMainWin*>(w);

        if(mainWin != nullptr)
        {
            mainWin->onViewEditable();
        }
    }
}

void DetailInfoDisplayDialog::on_cancelBtn_clicked()
{
    close();
}

void DetailInfoDisplayDialog::on_preBtn_clicked()
{
    CompolentInfoModel* model =  nullptr;

    foreach (QWidget* w, QApplication::topLevelWidgets())
    {
        DataDisplayWidget* disWin = dynamic_cast<DataDisplayWidget*>(w);

        if(disWin != nullptr)
        {
            model = disWin->getCompolentInfoModel();
        }
    }


    if(model != nullptr && 0 < currRow && currRow <= model->count() - 1)
    {
        CompolentInfo obj;
        int preID = model->getItemId(--currRow);

        if(pConnect->selectData(obj,preID))
        {
            setWindowTitle(obj.getName());
            setCompolentInfo(obj);
            getTabList()[0]->setCompolentInfoOnTab1(obj);
        }
    }
}

void DetailInfoDisplayDialog::on_nextBtn_clicked()
{
    CompolentInfoModel* model =  nullptr;

    foreach (QWidget* w, QApplication::topLevelWidgets())
    {
        DataDisplayWidget* disWin = dynamic_cast<DataDisplayWidget*>(w);

        if(disWin != nullptr)
        {
            model = disWin->getCompolentInfoModel();
        }
    }

    if(model != nullptr && 0 <= currRow && currRow < model->count() - 1)
    {
        CompolentInfo obj;
        int nextID = model->getItemId(++currRow);

        if(pConnect->selectData(obj,nextID))
        {
            setWindowTitle(obj.getName());
            setCompolentInfo(obj);
            getTabList()[0]->setCompolentInfoOnTab1(obj);
        }
    }
}

void DetailInfoDisplayDialog::on_wordBtn_clicked()
{
    QString path = FileTool::showFileDialog(this,QFileDialog::AcceptSave,"另存为",FileTool::Word);

    if(!path.isEmpty())
    {
        wordThread->setPath(path);
        wordThread->start();
    }

}

void DetailInfoDisplayDialog::on_picBtn_clicked()
{
    QString path = FileTool::showFileDialog(this,QFileDialog::AcceptSave,"另存为",FileTool::Image);

    if(!path.isEmpty())
    {
        QScreen* screen = QGuiApplication::primaryScreen();
        if(screen->grabWindow(winId()).save(path))
        {
            showSuccess(this,"成功","截图成功！");
        }
        else
        {
            showError(this,"失败","截图失败！");
        }
    }
}

void DetailInfoDisplayDialog::on_saveBtn_clicked()
{
    obj.setInfo(ui->infoTextEdit->toPlainText().trimmed());
    obj.setName(tab1->getValue0().trimmed());
    obj.setPara0(tab1->getValue1().trimmed().toDouble());
    obj.setPara1(tab1->getValue2().trimmed().toDouble());
    obj.setPara2(tab1->getValue3().trimmed().toDouble());
    obj.setPara3(tab1->getValue4().trimmed().toDouble());
    obj.setPara4(tab1->getValue5().trimmed().toDouble());
    obj.setPara5(tab1->getValue6().trimmed().toDouble());
    obj.setPara6(tab1->getValue7().trimmed().toDouble());
    obj.setPara7(tab1->getValue8().trimmed().toDouble());
    obj.setPara8(tab1->getValue9().trimmed().toDouble());
    obj.setPara9(tab1->getValue10().trimmed().toDouble());
    obj.setPara10(tab1->getValue11().trimmed().toDouble());
    obj.setPara11(tab1->getValue12().trimmed().toDouble());
    obj.setPara12(tab1->getValue13().trimmed().toDouble());
    obj.setPara13(tab1->getValue14().trimmed().toDouble());
    obj.setPara14(tab1->getValue15().trimmed().toDouble());
    wordThread->setCompolentInfo(obj);

    pConnect->update(obj);

    foreach (QWidget* w, QApplication::topLevelWidgets())
    {
        DataDisplayWidget* disWin = dynamic_cast<DataDisplayWidget*>(w);

        if(disWin != nullptr)
        {
            disWin->currentPageChanged();
        }
    }

    close();
}

void DetailInfoDisplayDialog::onWordSuccess()
{
    showSuccess(this,"成功","导出成功！");
}

void DetailInfoDisplayDialog::onWordFaliure()
{
    showError(this,"失败","导出失败！");
}

void DetailInfoDisplayDialog::on_preImgBtn_clicked()
{
    if(!imgList.isEmpty())
    {
        if(0 < index && index < imgList.count())
        {
            index--;
        }
        showImg(imgList[index]);
    }
}

void DetailInfoDisplayDialog::on_nextImgBtn_clicked()
{
    if(!imgList.isEmpty())
    {
        if(0 <= index && index < imgList.count() - 1)
        {
            index++;
        }
        showImg(imgList[index]);
    }
}

void DetailInfoDisplayDialog::onViewBigImage()
{
    BigImageDialog* biDly = new BigImageDialog(imgList[index]);
    biDly->exec();
    delete biDly;
}

void DetailInfoDisplayDialog::onViewVideo()
{
    XVideoUI* xvUI = new XVideoUI(videoPath);
    xvUI->exec();
    delete xvUI;
}
