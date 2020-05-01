/***********************************************
* @projectName   OMSystem
* @brief         文件工具类
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-03-06
************************************************/

#include "FileTool.h"

#include <QMap>
#include <QFile>
#include <QDir>

const char* FileTool::excelFilter[][2] =
{
    {"Microsoft Excel 工作表(*.xlsx)", ".xlsx"},
    {"Microsoft Excel 97-2003 工作表(*.xls)", ".xls"},
    {nullptr,                 nullptr  }
};

const char* FileTool::imageFilter[][2] =
{
    {"BMP 图片文件 (*.bmp)", ".bmp"},
    {"PNG 图片文件 (*.png)", ".png"},
    {"JPG 图片文件 (*.jpg)", ".jpg"},
    {nullptr,                 nullptr  }
};

const char* FileTool::wordFilter[][2] =
{
    {"Microsoft Word 文档(*.docx)", ".docx"},
    {"Microsoft Word 97-2003 文档(.doc)", ".doc"},
    {nullptr,                 nullptr  }
};

const char* FileTool::videoFilter[] =
{
    "视频文件(*.avi *.wmv *.mkv *.mp4)",
    nullptr
};

FileTool::FileTool(QObject *parent) : QObject(parent)
{

}

QString FileTool::showFileDialog(QWidget* parent,QFileDialog::AcceptMode mode, QString title,FileFilter fileFilter)
{
    QString ret = "";
    QFileDialog fd(parent);
    QStringList filters;
    QMap<QString, QString> map;

    switch (fileFilter)
    {
        case Excel:

            for(int i = 0; excelFilter[i][0] != nullptr; i++)
            {
                filters.append(excelFilter[i][0]);
                map.insert(excelFilter[i][0], excelFilter[i][1]);
            }

            break;

        case Image:

            for(int i = 0; imageFilter[i][0] != nullptr; i++)
            {
                filters.append(imageFilter[i][0]);
                map.insert(imageFilter[i][0], imageFilter[i][1]);
            }

            break;

        case Word:

            for(int i = 0; wordFilter[i][0] != nullptr; i++)
            {
                filters.append(wordFilter[i][0]);
                map.insert(wordFilter[i][0], wordFilter[i][1]);
            }

            break;

        case Video:

        for(int i = 0; videoFilter[i]!= nullptr; i++)
        {
            filters.append(videoFilter[i]);
        }

        break;
    }

    fd.setWindowTitle(title);
    fd.setAcceptMode(mode);
    fd.setNameFilters(filters);

    if( mode == QFileDialog::AcceptOpen )
    {
        fd.setFileMode(QFileDialog::ExistingFile);
    }

    if( fd.exec() == QFileDialog::Accepted )
    {
        ret = fd.selectedFiles()[0];

        if( mode == QFileDialog::AcceptSave )
        {
            QString postfix = map[fd.selectedNameFilter()];

            if( (postfix != "*") && !ret.endsWith(postfix) )
            {
                ret = ret + postfix;
            }
        }
    }

    return ret;
}

QString FileTool::loadSyleSheet(QWidget* w,const QString& name)
{
    QString styleSheet = "";
    QFile file(":/res/pic/qss/" + name + ".qss");
    file.open(QFile::ReadOnly | QIODevice::Text);

    if (file.isOpen())
    {
        styleSheet += QString(file.readAll());

        if(!styleSheet.isEmpty())
        {
            w->setStyleSheet(styleSheet);
        }
    }

    file.close();

    return styleSheet;
}

void FileTool::findFilesInDir(const QString& dirPath,const QStringList& nameFilter,QStringList& fileNameList)
{
    QDir dir(dirPath);
    QStringList fileNames;

    fileNames = dir.entryList(nameFilter, QDir::Files | QDir::Readable, QDir::Name);

    for(int i = 0;i < fileNames.count();i++)
    {
        fileNameList.append(dirPath + fileNames[i]);
    }
}

bool FileTool::removeFolderContent(const QString &folderDir)
{
    QDir dir(folderDir);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())  {return false;}//文件不存，则返回false
    fileList=dir.entryInfoList(QDir::Dirs|QDir::Files
                               |QDir::Readable|QDir::Writable
                               |QDir::Hidden|QDir::NoDotAndDotDot
                               ,QDir::Name);
    while(fileList.size()>0)
    {
        int infoNum=fileList.size();
        for(int i=infoNum-1;i>=0;i--)
        {
            curFile=fileList[i];
            if(curFile.isFile())//如果是文件，删除文件
            {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir())//如果是文件夹
            {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1=dirTemp.entryInfoList(QDir::Dirs|QDir::Files
                                                              |QDir::Readable|QDir::Writable
                                                              |QDir::Hidden|QDir::NoDotAndDotDot
                                                              ,QDir::Name);
                if(fileList1.size()==0)//下层没有文件或文件夹
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else//下层有文件夹或文件
                {
                    for(int j=0;j<fileList1.size();j++)
                    {
                        if(!(fileList.contains(fileList1[j])))
                            fileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
    return true;
}
