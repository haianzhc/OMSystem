/***********************************************
* @projectName   OMSystem
* @brief         文件工具类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-06
************************************************/

#pragma execution_character_set("utf-8")

#ifndef FILETOOL_H
#define FILETOOL_H

#include <QObject>
#include <QFileDialog>
#include <QWidget>

class FileTool : public QObject
{
    Q_OBJECT

    const static char* excelFilter[][2];
    const static char* imageFilter[][2];
    const static char* wordFilter[][2];
    const static char* videoFilter[];

    FileTool(QObject *parent = nullptr);
public:

    enum FileFilter
    {
        Excel,
        Image,
        Word,
        Video
    };

    static QString showFileDialog(QWidget* parent,QFileDialog::AcceptMode mode, QString title,FileFilter fileFilter);
    static QString loadSyleSheet(QWidget* w,const QString& name);
    static void findFilesInDir(const QString& dirPath,const QStringList& nameFilter,QStringList& fileNameList);
    static bool removeFolderContent(const QString& folderDir);
};

#endif // FILETOOL_H
