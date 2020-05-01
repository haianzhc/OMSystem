#pragma execution_character_set("utf-8")

#ifndef COREARITHMETIC_H
#define COREARITHMETIC_H

#include <QObject>
#include <Python.h>
#include <QPoint>

class CoreArithmetic : public QObject
{
    Q_OBJECT

    explicit CoreArithmetic(QObject *parent = nullptr);

    static PyObject* prepare(const QString& file,const QString& module);
public:

    static void init();
    static void terminate();

    static void mathc_img(const QString& filePath,const QString& templatePath,double value = 0.9);
    static void edge(const QString& filePath);
    static void distanceCalculate(QPoint& start,QPoint& end,const QString& direction);
    static void findLine(QPoint& start,QPoint& end,const QString& direction);
    static void getCircle(const QString& filePath);
};

#endif // COREARITHMETIC_H
