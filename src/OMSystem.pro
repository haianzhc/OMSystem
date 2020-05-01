#-------------------------------------------------
#
# Project created by QtCreator 2020-03-13T22:54:28
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += axcontainer
QT       += xml
QT       += concurrent
RC_ICONS = measure.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OMSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    CoreArithmetic.cpp \
    DimensionInfo.cpp \
    ImageHandlerWidget.cpp \
    XVideoThread.cpp \
    XVideoUI.cpp \
    XVideoWidget.cpp \
    XmlHandler.cpp \
        main.cpp \
        OMSystemMainWin.cpp \
    AppConfig.cpp \
    BigImageDialog.cpp \
    CompolentInfo.cpp \
    CompolentInfoModel.cpp \
    DataDisplayWidget.cpp \
    DataSource.cpp \
    DetailDataTabWidget.cpp \
    DetailInfoDisplayDialog.cpp \
    ExcelExporter.cpp \
    ExcelImporter.cpp \
    FileTool.cpp \
    SearchDialog.cpp \
    WaitDialog.cpp \
    WordHandler.cpp \
    OMSystem.cpp \
    LoginDialog.cpp \
    CustomWindow/BasicDialog.cpp \
    CustomWindow/BasicWidget.cpp \
    CustomWindow/SysTray.cpp \
    CustomWindow/TitleWidget.cpp \
    CustomWindow/CustomMenu.cpp \
    CustomWindow/MessageBox.cpp \
    PaintTool.cpp \
    CompolentInfoDelegate.cpp

HEADERS += \
    CoreArithmetic.h \
    DimensionInfo.h \
    GetCircle.h \
    ImageHandlerWidget.h \
        OMSystemMainWin.h \
    AppConfig.h \
    BigImageDialog.h \
    CompolentInfo.h \
    CompolentInfoModel.h \
    DataDisplayWidget.h \
    DataSource.h \
    DetailDataTabWidget.h \
    DetailInfoDisplayDialog.h \
    ExcelExporter.h \
    ExcelImporter.h \
    FileTool.h \
    SearchDialog.h \
    WaitDialog.h \
    WordHandler.h \
    OMSystem.h \
    LoginDialog.h \
    CustomWindow/BasicDialog.h \
    CustomWindow/BasicWidget.h \
    CustomWindow/SysTray.h \
    CustomWindow/TitleWidget.h \
    CustomWindow/CustomMenu.h \
    CustomWindow/MessageBox.h \
    PaintTool.h \
    CompolentInfoDelegate.h \ \
    XVideoThread.h \
    XVideoUI.h \
    XVideoWidget.h \
    XmlHandler.h

FORMS += \
        OMSystemMainWin.ui \
    DataDisplayWidget.ui \
    DetailDataTabWidget.ui \
    DetailInfoDisplayDialog.ui \
    SearchDialog.ui \
    WaitDialog.ui \
    OMSystem.ui \
    CustomWindow/TitleWidget.ui \
    XVideoUI.ui

RESOURCES += \
    res.qrc

INCLUDEPATH += C:/Qt/opencv/build/include
LIBS += C:/Qt/opencv/build/x64/vc15/lib/*.lib

win32: LIBS += -LC:/Python36/libs/ -lpython36

INCLUDEPATH += C:/Python36/include
DEPENDPATH += C:/Python36/include

win32:!win32-g++: PRE_TARGETDEPS += C:/Python36/libs/python36.lib
else:win32-g++: PRE_TARGETDEPS += C:/Python36/libs/libpython36.a

INCLUDEPATH += C:/MATLAB/R2019b/extern/include
DEPENDPATH += C:/MATLAB/R2019b/extern/include
INCLUDEPATH += C:/MATLAB/R2019b/extern/include/win64
DEPENDPATH += C:/MATLAB/R2019b/extern/include/win64

win32: LIBS += -LC:/MATLAB/R2019b/extern/lib/win64/microsoft/ -llibeng
win32: LIBS += -LC:/MATLAB/R2019b/extern/lib/win64/microsoft/ -llibmat
win32: LIBS += -LC:/MATLAB/R2019b/extern/lib/win64/microsoft/ -llibmex
win32: LIBS += -LC:/MATLAB/R2019b/extern/lib/win64/microsoft/ -llibmx
win32: LIBS += -LC:/MATLAB/R2019b/extern/lib/win64/microsoft/ -lmclmcr
win32: LIBS += -LC:/MATLAB/R2019b/extern/lib/win64/microsoft/ -lmclmcrrt

win32: LIBS += -L$$PWD/../lib/ -lGetCircle

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
