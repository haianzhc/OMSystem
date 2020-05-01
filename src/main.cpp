/***********************************************
* @projectName   OMSystem
* @brief         The main function
* @author        ZhuHaocheng-Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-28
************************************************/

#pragma execution_character_set("utf-8")

#include "LoginDialog.h"
#include "DataSource.h"
#include "OMSystem.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QSqlDatabase>
#include <QSurfaceFormat>

//static bool ValidateUserID(QString id)
//{
//    bool ret = true;
//    QString invalid = "~`!@#$%^&*()_-+={}[]|\\:;\'\",.?/<>";

//    for(int i=0; i<invalid.length(); i++)
//    {
//        if( id.contains(invalid[i]) )
//        {
//            ret = false;
//            break;
//        }
//    }

//    return ret;
//}

int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

//    LoginDialog login;

//    login.setValFunc(ValidateUserID);

//    if(login.exec() == QDialog::Accepted)
//    {
//        QPixmap p(":res/pic/splash.png");
//        QSplashScreen splash(p);
//        splash.show();
//        a.processEvents();

//        OMSystem w(login.sendConnection());
//        w.show();
//        splash.finish(&w);
//        return a.exec();
//    }

//    return 0;

    QPixmap p(":res/pic/splash.png");
    QSplashScreen splash(p);
    splash.show();
    a.processEvents();

    OMSystem w(new DataSource("root","xjtuzhc"));
    w.show();
    splash.finish(&w);

    return a.exec();
}
