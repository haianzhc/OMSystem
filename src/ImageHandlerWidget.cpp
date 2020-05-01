#include "ImageHandlerWidget.h"
#include "CoreArithmetic.h"
#include "PaintTool.h"
#include "XmlHandler.h"

#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPixmap>
#include <QDebug>
#include <QList>
#include <QFile>

static bool press = false;
static QPoint PreDot;

static MeasureType selectMode = Global;
static bool isMeasuring = false;
static bool isCorrecting = false;

ImageHandlerWidget::ImageHandlerWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    CoreArithmetic::init();
}

ImageHandlerWidget::~ImageHandlerWidget()
{
    CoreArithmetic::terminate();
}

void ImageHandlerWidget::append(QPoint p)
{
    if(points.count() == 2)
    {
        points.removeLast();
    }

    points.append(p);
}

void ImageHandlerWidget::drawSelctRect(QPainter& painter)
{
    if(points.count() == 2)
    {
        int x = (points[0].x() < points[1].x()) ? points[0].x() : points[1].x();
        int y = (points[0].y() < points[1].y()) ? points[0].y() : points[1].y();
        int w = qAbs(points[0].x() - points[1].x()) + 1;
        int h = qAbs(points[0].y() - points[1].y()) + 1;

        QPen pen(Qt::cyan,2);
        painter.setPen(pen);
        painter.drawRect(x, y, w, h);

        relativePoints.clear();
        dimension.clear();

        if(!myImg.empty())
        {
            int startPointX = int((x - zero.x()) / ratio);
            int startPointY = int((y - zero.y()) / ratio);
            int endPointX = int((x + w - zero.x()) / ratio);
            int endPointY = int((y + h - zero.y()) / ratio);

            if(startPointX < 0)
            {
                startPointX = 0;
            }

            if(startPointY < 0)
            {
                startPointY = 0;
            }

            if(endPointX > myImg.cols)
            {
                endPointX = myImg.cols;
            }

            if(endPointY > myImg.rows)
            {
                endPointY = myImg.rows;
            }

            QPoint relative0(startPointX,startPointY);
            QPoint relative1(endPointX,endPointY);

            if(relative0.x() >= 0 && relative0.x() <= myImg.cols &&
                    relative0.y() >= 0 && relative0.y() <= myImg.rows &&
                    relative1.x() >= 0  && relative1.x() <= myImg.cols &&
                    relative1.y() >= 0 && relative1.y() <= myImg.rows)
            {
                relativePoints.append(relative0);
                relativePoints.append(relative1);

                qDebug() << relativePoints[0].x() << ":" << relativePoints[0].y();
                qDebug() << relativePoints[1].x() << ":" << relativePoints[1].y();
            }
        }
    }
}

void ImageHandlerWidget::globalMeasure(const QString& path)
{
    CoreArithmetic::getCircle(path);
    XmlHandler::parseXML(QApplication::applicationDirPath() + "/temp/dimension.xml",dimension);
    update();
}

void ImageHandlerWidget::partMeasure()
{
    if(relativePoints.count() == 2)
    {
//        qDebug() << relativePoints.at(0).x() << ":" <<relativePoints.at(0).y();
//        qDebug() << relativePoints.at(1).x() << ":" <<relativePoints.at(1).y();

        QFile::remove(QApplication::applicationDirPath() + "/temp/dimension.xml");

        if(selectMode == Width)
        {
            CoreArithmetic::findLine(relativePoints[0],relativePoints[1],"top");
        }
        else if(selectMode == Height)
        {
            CoreArithmetic::distanceCalculate(relativePoints[0],relativePoints[1],"left");
        }

        XmlHandler::parseXML(QApplication::applicationDirPath() + "/temp/dimension.xml",dimension);
    }
}

void ImageHandlerWidget::drawMeasurePixmap(QPainter& painter)
{
    int canvasW = width();
    int canvasH = height();

    int NowW = int(ratio * pixW);
    int NowH = int(ratio * pixH);

    if(abs(AllOffset.y()) >= (canvasH / 2 + NowH / 2 - 10))
    {
        if(AllOffset.y() > 0)
        {
            AllOffset.setY(canvasH / 2 + NowH / 2 - 10);
        }
        else
        {
            AllOffset.setY(- canvasH / 2 - NowH / 2 + 10);
        }
    }

    int x = canvasW / 2 + AllOffset.x() - NowW / 2;

    if(x < 0)
    {
        x = 0;
    }

    int y = canvasH / 2 + AllOffset.y() - NowH / 2;

    if(y < 0)
    {
        y = 0;
    }

    int  sx = NowW / 2 - canvasW / 2 - AllOffset.x();

    if(sx < 0)
    {
        sx = 0;
    }

    int  sy = NowH / 2 - canvasH / 2 - AllOffset.y();

    if(sy < 0)
    {
        sy = 0;
    }

    int w = (NowW - sx) > canvasW ? canvasW : (NowW - sx);

    if(w > (canvasW - x))
    {
        w = canvasW - x;
    }

    int h = (NowH - sy) > canvasH ? canvasH : (NowH - sy);

    if(h > (canvasH - y))
    {
        h = canvasH - y;
    }

    painter.drawTiledPixmap(x,y,w,h,QPixmap::fromImage(myQImg),sx,sy);
}

void ImageHandlerWidget::drawDimension(QPainter& painter)
{
    QList<double> list;

    if(!dimension.isEmpty())
    {
        if(dimension.hasCircle())
        {           
            if(isCorrecting)
            {
                center.setX(width() / 2);
                center.setY(height() / 2);
                center = (center - zero) / ratio;
            }

            QList<DimensionInfo::Circle> circleList = dimension.getCircleList();

            for (int i = 0;i < circleList.count();i++)
            {
                QPoint circleCenter = circleList[i].center;
                double radius = circleList[i].radius;
                int x = circleCenter.x() - center.x();
                int y = circleCenter.y() - center.y();

                list.append(radius * 2);

                if(qAbs(x) < qAbs(y))
                {
                    if(y < 0)
                    {
                        QPoint drawStart = (circleCenter - QPoint(int(radius),0)) * ratio + zero;
                        QPoint drawEnd = (circleCenter + QPoint(int(radius),0)) * ratio + zero;

                        PaintTool::drawLinearDimension(painter,drawStart,drawEnd,PaintTool::Top,
                                                       i,radius * 2,int(radius * 1.8),ratio);
                    }
                    else
                    {
                        QPoint drawStart = (circleCenter - QPoint(int(radius),0)) * ratio + zero;
                        QPoint drawEnd = (circleCenter + QPoint(int(radius),0)) * ratio + zero;

                        PaintTool::drawLinearDimension(painter,drawStart,drawEnd,PaintTool::Bottom,
                                                       i,radius * 2,int(radius * 1.8),ratio);
                    }
                }
                else
                {
                    if(x < 0)
                    {
                        QPoint drawStart = (circleCenter - QPoint(0,int(radius))) * ratio + zero;
                        QPoint drawEnd = (circleCenter + QPoint(0,int(radius))) * ratio + zero;

                        PaintTool::drawLinearDimension(painter,drawStart,drawEnd,PaintTool::Left,
                                                       i,radius * 2,int(radius * 1.8),ratio);
                    }
                    else
                    {
                        QPoint drawStart = (circleCenter - QPoint(0,int(radius))) * ratio + zero;
                        QPoint drawEnd = (circleCenter + QPoint(0,int(radius))) * ratio + zero;

                        PaintTool::drawLinearDimension(painter,drawStart,drawEnd,PaintTool::Right,
                                                       i,radius * 2,int(radius * 1.8),ratio);
                    }
                }
            }
        }

        if(dimension.hasLine())
        {
            QList<DimensionInfo::Line> lineList = dimension.getLineList();

            for (int i = 0;i < lineList.count();i++)
            {
                list.append(lineList[i].distance);

//                qDebug() << lineList[i].points[0].x() << ":" << lineList[i].points[0].y();
//                qDebug() << lineList[i].points[1].x() << ":" << lineList[i].points[1].y();

                QPoint drawStart = lineList[i].points[0] * ratio + zero;
                QPoint drawEnd = lineList[i].points[1] * ratio + zero;

                if(lineList[i].direction == PaintTool::Left || lineList[i].direction == PaintTool::Right)
                {
                    PaintTool::drawLinearDimension(painter,drawStart,drawEnd,lineList[i].direction,
                                                   i,lineList[i].distance,150,ratio);
                }
                else
                {
                    PaintTool::drawLinearDimension(painter,drawStart,drawEnd,lineList[i].direction,
                                                   i,lineList[i].distance,50,ratio);
                }
            }
        }
    }

    emit signalData(list);
}

void ImageHandlerWidget::paintGL()
{
    QPainter painter(this);

    painter.fillRect(contentsRect(),Qt::black);

    int canvasW = width();
    int canvasH = height();

    if(!myImg.empty())
    {
        int NowW = int(ratio * pixW);
        int NowH = int(ratio * pixH);

        if(action == Amplification)
        {
            ratio -= 0.1 * ratio;
            if(ratio < 0.018)
            {
                ratio = 0.01;
            }
        }

        if(action == Shrink)
        {
            ratio += 0.1 * ratio;

            if(ratio > 2.9)
            {
                ratio = 3.00;
            }
        }

        if(action == Amplification || action == Shrink)
        {
            NowW = int(ratio * pixW);
            NowH = int(ratio * pixH);

            emit signalRatioChanged(ratio * 100.0);

            myQImg = QImage(reinterpret_cast<const unsigned char*>(myImg.data),myImg.cols,myImg.rows,
                            int(myImg.step),QImage::Format_RGB888).scaled(NowW,NowH,Qt::KeepAspectRatio);

            action = None;
        }

        if(action == Move)
        {

            int offsetx = AllOffset.x() + offset.x();
            AllOffset.setX(offsetx);

            int offsety = AllOffset.y() + offset.y();
            AllOffset.setY(offsety);

            action = None;
        }

        if(abs(AllOffset.x()) >= (canvasW / 2 + NowW / 2 - 10))
        {
            if(AllOffset.x() > 0)
            {
                AllOffset.setX(canvasW / 2 + NowW / 2 - 10);
            }
            else
            {
                AllOffset.setX(- canvasW / 2 -NowW / 2 + 10);
            }
        }

        if(abs(AllOffset.y()) >= (canvasH / 2 + NowH / 2 - 10))
        {
            if(AllOffset.y() > 0)
            {
                AllOffset.setY(canvasH / 2 + NowH / 2 - 10);
            }
            else
            {
                AllOffset.setY(- canvasH / 2 - NowH / 2 + 10);
            }
        }

        int x = canvasW / 2 + AllOffset.x() - NowW / 2;

        if(x < 0)
        {
            x = 0;
        }

        int y = canvasH / 2 + AllOffset.y() - NowH / 2;

        if(y < 0)
        {
            y = 0;
        }

        int  sx = NowW / 2 - canvasW / 2 - AllOffset.x();

        if(sx < 0)
        {
            sx = 0;
        }

        int  sy = NowH / 2 - canvasH / 2 - AllOffset.y();

        if(sy < 0)
        {
            sy = 0;
        }

        int w = (NowW - sx) > canvasW ? canvasW : (NowW - sx);

        if(w > (canvasW - x))
        {
            w = canvasW - x;
        }

        int h = (NowH - sy) > canvasH ? canvasH : (NowH - sy);

        if(h > (canvasH - y))
        {
            h = canvasH - y;
        }

        zero.setX(x - sx);
        zero.setY(y - sy);

        painter.drawTiledPixmap(x,y,w,h,QPixmap::fromImage(myQImg),sx,sy);
    }

    if(selectMode != Global)
    {
        painter.setBrush(Qt::NoBrush);
        drawSelctRect(painter);        
    }
    else
    {
        points.clear();
        relativePoints.clear();
    }

    if(isMeasuring)
    {
        partMeasure();
        drawDimension(painter);
    }
    else
    {
        dimension.clear();
    }
}

void ImageHandlerWidget::mousePressEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton && contentsRect().contains(e->pos()))
    {
        press = true;

        if(selectMode != Global && !isMeasuring)
        {
            points.clear();
            append(e->pos());
        }
        else
        {
            PreDot = e->pos();
        }
    }
}

void ImageHandlerWidget::mouseMoveEvent(QMouseEvent* e)
{
    if(contentsRect().contains(e->pos()))
    {
        if(selectMode != Global && !isMeasuring)
        {
            setCursor(Qt::CrossCursor);
        }
        else
        {
            setCursor(QCursor(QPixmap(":/res/pic/cursor.png")));
        }
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }

    if(press)
    {
        if(selectMode != Global && !isMeasuring)
        {
            append(e->pos());
        }
        else
        {
            offset.setX(e->x() - PreDot.x());
            offset.setY(e->y() - PreDot.y());
            PreDot = e->pos();
            action = Move;
        }

        update();
    }
}

void ImageHandlerWidget::mouseReleaseEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton && press )
    {
        press = false;
    }
}

void ImageHandlerWidget::wheelEvent(QWheelEvent* e)
{
    if(!myImg.empty())
    {
        if(e->delta() > 0)
        {
            action = Shrink;

            update();
        }
        else
        {
            action = Amplification;

            update();
        }
    }

    e->accept();
}

void ImageHandlerWidget::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
    else
    {
        e->ignore();
    }
}

void ImageHandlerWidget::dropEvent(QDropEvent* e)
{
    const QMimeData* mimeData = e->mimeData();

    if(mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        QString fileName = urlList.at(0).toLocalFile();

        if(!fileName.isEmpty())
        {
            if(fileName.endsWith(".jpg") || fileName.endsWith(".png") || fileName.endsWith(".bmp"))
            {
                QFile::remove(QApplication::applicationDirPath() + "/temp/measure.jpg");
                emit signalFileChanged(fileName);

                CoreArithmetic::edge(fileName);
                initImage(QApplication::applicationDirPath() + "/temp/" + "3-6canny1.jpg");
                //initImage(fileName);
            }
        }
    }
}

void ImageHandlerWidget::initImgPara()
{
    ratio = 1.0;
    AllOffset.setX(0);
    AllOffset.setY(0);
    offset.setX(0);
    offset.setY(0);
    action = None;

    points.clear();
    relativePoints.clear();

    dimension.clear();
    myImg.release();

    emit signalRatioChanged(100.0);
}

void ImageHandlerWidget::initImage(QString imgPath)
{
    initImgPara();

    myImg = imread(imgPath.toStdString());

    cvtColor(myImg,myImg,COLOR_BGR2RGB);

    myQImg = QImage(reinterpret_cast<const unsigned char*>(myImg.data),myImg.cols,myImg.rows,
                    int(myImg.step),QImage::Format_RGB888);
    pixW = myQImg.width();
    pixH = myQImg.height();

    center.setX(pixW / 2);
    center.setY(pixH / 2);

    update();
}

void ImageHandlerWidget::clearPoints()
{
    points.clear();
    relativePoints.clear();
    dimension.clear();
}

void ImageHandlerWidget::updateImage()
{
    update();
}

void ImageHandlerWidget::changeSelectMode(MeasureType mode)
{
    selectMode = mode;
}

void ImageHandlerWidget::changeMeasureMode()
{
    isMeasuring = !isMeasuring;
}

void ImageHandlerWidget::changeMeasureMode(bool isStart)
{
    isMeasuring = isStart;
}

void ImageHandlerWidget::changeCorrectMode()
{
    isCorrecting = !isCorrecting;
}

void ImageHandlerWidget::changeCorrectMode(bool isStart)
{
    isCorrecting = isStart;
}

MeasureType ImageHandlerWidget::getSelectMode()
{
    return selectMode;
}

bool ImageHandlerWidget::getMeasureMode()
{
    return isMeasuring;
}

bool ImageHandlerWidget::getCorrectMode()
{
    return isCorrecting;
}

bool ImageHandlerWidget::hasImage()
{
    return !myImg.empty();
}

void ImageHandlerWidget::takePtoto(Mat mat)
{
    initImgPara();

    myImg = mat.clone();
    myQImg = QImage(reinterpret_cast<const unsigned char*>(myImg.data),
                    myImg.cols,myImg.rows,QImage::Format_RGB888);
    pixW = myQImg.width();
    pixH = myQImg.height();

    update();
}

void ImageHandlerWidget::fileOpen(const QString& path)
{
    CoreArithmetic::edge(path);   
    initImage(QApplication::applicationDirPath() + "/temp/" + "3-6canny1.jpg");
    //initImage(path);
}

void ImageHandlerWidget::fileSave(const QString& path)
{
    QPainter painter;
    QPixmap map(width(),height());
    map.fill(Qt::black);

    painter.begin(&map);    
    drawMeasurePixmap(painter);
    drawDimension(painter);
    painter.end();
    map.save(path);
}

void ImageHandlerWidget::imageBig()
{
    if(!myImg.empty())
    {
        action = Shrink;
        update();
    }
}

void ImageHandlerWidget::imageSmall()
{
    if(!myImg.empty())
    {
        action = Amplification;
        update();
    }
}
