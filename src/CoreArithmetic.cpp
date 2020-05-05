#include "CoreArithmetic.h"
#include "CustomWindow/MessageBox.h"
#include "GetCircle.h"

#include <QApplication>

CoreArithmetic::CoreArithmetic(QObject *parent) : QObject(parent)
{

}

/**
* @brief         初始化Python模块
* @param         None
* @return        None
*/
void CoreArithmetic::init()
{
    //Py_SetPythonHome(const_cast<wchar_t*>(L"Python36"));
    Py_Initialize();
    GetCircleInitialize();
}

void CoreArithmetic::terminate()
{
    Py_Finalize();
    GetCircleTerminate();
}

PyObject* CoreArithmetic::prepare(const QString& file,const QString& module)
{
    if(!Py_IsInitialized())
    {
        showError(nullptr,"错误","初始化Python失败！");
        return nullptr;
    }

    PyObject* pModule = PyImport_ImportModule(file.toStdString().c_str());

    if(!pModule)
    {
        showError(nullptr,"错误","打开Python文件 " + file + ".py 失败！");
        return nullptr;
    }

    PyObject* python_module = PyObject_GetAttrString(pModule,module.toStdString().c_str());

    if(!python_module)
    {
        showError(nullptr,"错误","获取Python模块 " + module + " 失败！");
        return nullptr;
    }

    return python_module;
}

void CoreArithmetic::mathc_img(const QString& filePath,const QString& templatePath,double value)
{
    PyObject* python_module = prepare("arithmetic","mathc_img");

    if(python_module)
    {
        QString dirPath = QApplication::applicationDirPath() + "/temp/";

        PyObject *pArgs = Py_BuildValue("sssd",filePath.toStdString().c_str(),templatePath.toStdString().c_str(),
                                        dirPath.toStdString().c_str(),value);
        PyObject_CallObject(python_module,pArgs);
    }
}

void CoreArithmetic::edge(const QString& filePath)
{
    PyObject* python_module = prepare("arithmetic","edge");

    if(python_module)
    {
        QString dirPath = QApplication::applicationDirPath() + "/temp/";

        PyObject *pArg = PyTuple_New(2);
        PyTuple_SetItem(pArg, 0, Py_BuildValue("s", filePath.toStdString().c_str()));
        PyTuple_SetItem(pArg, 1, Py_BuildValue("s", dirPath.toStdString().c_str()));
        PyObject_CallObject(python_module,pArg);
    }
}

void CoreArithmetic::distanceCalculate(QPoint& start,QPoint& end,const QString& direction)
{
    PyObject* python_module = prepare("arithmetic","distanceCalculate");

    if(python_module)
    {
        QString dirPath = QApplication::applicationDirPath() + "/temp/";

        PyObject *pArgs = Py_BuildValue("s[ii][ii]s",dirPath.toStdString().c_str(),
                                        start.x(),start.y(),end.x(),end.y(),
                                        direction.toStdString().c_str());
        PyObject_CallObject(python_module,pArgs);
    }
}

void CoreArithmetic::findLine(QPoint& start,QPoint& end,const QString& direction)
{
    PyObject* python_module = prepare("arithmetic","findLine");

    if(python_module)
    {
        QString dirPath = QApplication::applicationDirPath() + "/temp/";

        PyObject *pArgs = Py_BuildValue("s[ii][ii]s",dirPath.toStdString().c_str(),
                                        start.x(),start.y(),end.x(),end.y(),
                                        direction.toStdString().c_str());
        PyObject_CallObject(python_module,pArgs);
    }
}

void CoreArithmetic::getCircle(const QString& filePath)
{
    QString des = QApplication::applicationDirPath() + "/temp/dimension.xml";
    mwArray path(filePath.toStdString().c_str());
    mwArray desFile(des.toStdString().c_str());

    GetCircle(path,desFile);
}
