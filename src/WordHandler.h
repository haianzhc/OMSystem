/*******************************************************
* @projectName   OMSystem
* @brief         Word导出线程类
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-24
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef WORDHANDLER_H
#define WORDHANDLER_H

#include <QObject>
#include <QThread>

#include <CompolentInfo.h>

class WordHandler : public QObject
{
    Q_OBJECT

    QThread wordHandler;
    QString path;
    CompolentInfo obj;

    void exportToWord();
public:

    explicit WordHandler(QObject *parent = nullptr);
    ~WordHandler();

    void start();
    void setPath(const QString& path);
    void setCompolentInfo(const CompolentInfo& obj);

signals:

    void wordBegin();
    void wordSuccess();
    void wordFaliure();

public slots:

    void wordTmain();
};

#endif // WORDHANDLER_H
