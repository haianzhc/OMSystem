/*******************************************************
* @projectName   OMSystem
* @brief         Word导出线程类
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-24
*******************************************************/


#include "WordHandler.h"

#include <QAxObject>
#include <QDir>
#include <QVariant>

WordHandler::WordHandler(QObject *parent) : QObject(parent)
{
    moveToThread(&wordHandler);

    connect(&wordHandler,SIGNAL(started()),this,SLOT(wordTmain()));
}

WordHandler::~WordHandler()
{
    wordHandler.wait();
}

/**
* @brief         将详细信息导出至Word
* @param         None
* @return        None
*/
void WordHandler::exportToWord()
{
    QAxObject* myWord = new QAxObject("Word.Application");
    QAxObject* myDocs = myWord->querySubObject("Documents");
    myDocs->dynamicCall("Add(void)");
    QAxObject* document = myWord->querySubObject("ActiveDocument");
    QAxObject* paragraph = myWord->querySubObject("Selection");

//    QAxObject* pShape = paragraph->querySubObject("InlineShapes");
//    pShape->dynamicCall("AddPicture(const QString&)",QDir::toNativeSeparators(obj.getImgUrl()));

    QAxObject* font = paragraph->querySubObject("Font");
    font->setProperty("Name","楷体");
    font->setProperty("Size","16");
    paragraph->dynamicCall("TypeText(const QString&)","\n\n名称：" + obj.getName());
    paragraph->dynamicCall("TypeText(const QString&)","      时间：" + obj.getTime().toString("yyyy-MM-dd hh:mm:ss"));
    paragraph->dynamicCall("TypeText(const QString&)","\n参数0：" + QString::number(obj.getPara0()));
    paragraph->dynamicCall("TypeText(const QString&)","      参数1：" + QString::number(obj.getPara1()));
    paragraph->dynamicCall("TypeText(const QString&)","      参数2：" + QString::number(obj.getPara2()));
    paragraph->dynamicCall("TypeText(const QString&)","\n参数3：" + QString::number(obj.getPara3()));
    paragraph->dynamicCall("TypeText(const QString&)","      参数4：" + QString::number(obj.getPara4()));
    paragraph->dynamicCall("TypeText(const QString&)","      参数5：" + QString::number(obj.getPara5()));
    paragraph->dynamicCall("TypeText(const QString&)","\n参数6：" + QString::number(obj.getPara6()));
    paragraph->dynamicCall("TypeText(const QString&)","      参数7：" + QString::number(obj.getPara7()));
    paragraph->dynamicCall("TypeText(const QString&)","      参数8：" + QString::number(obj.getPara8()));
    paragraph->dynamicCall("TypeText(const QString&)","\n参数9：" + QString::number(obj.getPara9()));
    paragraph->dynamicCall("TypeText(const QString&)","     参数10：" + QString::number(obj.getPara10()));
    paragraph->dynamicCall("TypeText(const QString&)","     参数11：" + QString::number(obj.getPara11()));
    paragraph->dynamicCall("TypeText(const QString&)","\n参数12：" + QString::number(obj.getPara12()));
    paragraph->dynamicCall("TypeText(const QString&)","     参数13：" + QString::number(obj.getPara13()));
    paragraph->dynamicCall("TypeText(const QString&)","     参数14：" + QString::number(obj.getPara14()));
    paragraph->dynamicCall("TypeText(const QString&)","\n\n备注：");
    paragraph->dynamicCall("TypeText(const QString&)","\n       " + obj.getInfo());

    document->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(path));
    document->dynamicCall("Close()");
    myWord->dynamicCall("Quit()");
    delete myWord;
}

void WordHandler::wordTmain()
{
    emit wordBegin();

    exportToWord();

    emit wordSuccess();

    wordHandler.quit();
}

void WordHandler::start()
{
    wordHandler.start();
}

void WordHandler::setPath(const QString& path)
{
    this->path = path;
}

void WordHandler::setCompolentInfo(const CompolentInfo& obj)
{
    this->obj = obj;
}
