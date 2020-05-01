#ifndef IMAGEHANDLERWIDGET_H
#define IMAGEHANDLERWIDGET_H

#include <QOpenGLWidget>
#include <opencv2/opencv.hpp>

#include "DimensionInfo.h"

using namespace cv;

enum MeasureType
{
    Global,
    Width,
    Height
};

class ImageHandlerWidget : public QOpenGLWidget
{
    Q_OBJECT

    enum  Type
    {
        None,
        Amplification ,
        Shrink,
        Left,
        Right,
        Move
    };

    Mat myImg;
    QImage myQImg;

    Type action;
    double ratio;
    int pixW;
    int pixH;
    QPoint offset;
    QPoint AllOffset;

    QList<QPoint> points;
    QList<QPoint> relativePoints;
    QPoint zero;
    QPoint center;

    DimensionInfo dimension;

    void append(QPoint p);
    void drawSelctRect(QPainter& painter);
    void partMeasure();
    void drawMeasurePixmap(QPainter& painter);
    void drawDimension(QPainter& painter);

    void paintGL();
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void wheelEvent(QWheelEvent* e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);

public:

    explicit ImageHandlerWidget(QWidget *parent = nullptr);
    ~ImageHandlerWidget();

    void globalMeasure(const QString& path);

    void initImgPara();
    void initImage(QString imgPath);
    void clearPoints();

    void updateImage();

    void changeSelectMode(MeasureType mode);
    void changeMeasureMode();
    void changeMeasureMode(bool isStart);
    void changeCorrectMode();
    void changeCorrectMode(bool isStart);
    MeasureType getSelectMode();
    bool getMeasureMode();
    bool getCorrectMode();
    bool hasImage();

    void takePtoto(Mat mat);
    void fileOpen(const QString& path);
    void fileSave(const QString& path);
    void imageBig();
    void imageSmall();

signals:

    void signalRatioChanged(double ratio);
    void signalFileChanged(const QString& path);
    void signalData(const QList<double>& list);

};

#endif // IMAGEHANDLERWIDGET_H
