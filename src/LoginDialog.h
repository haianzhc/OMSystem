/*******************************************************
* @projectName   OMSystem
* @brief         登录对话框
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-03
*******************************************************/

#pragma execution_character_set("utf-8")

#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>

#include "DataSource.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:

    typedef bool (*ValFunc)(QString);

private:

    QLabel TitleLabel;
    QLabel SystemTitle;
    QLabel UserLabel;
    QLabel PwdLabel;
    QLineEdit UserEdit;
    QLineEdit PwdEdit;
    QLineEdit CaptEdit;
    QPushButton LoginBtn;
    QPushButton ExitBtn;
    QLabel  hideLabel;
    QString m_user;
    QString m_pwd;
    QString m_captcha;
    Qt::GlobalColor* m_colors;
    QTimer m_timer;
    ValFunc m_vf;
    DataSource* pds;

protected:

    void paintEvent(QPaintEvent*);
    QString getCaptcha();
    Qt::GlobalColor* getColors();

    bool event(QEvent* e);
    void showEvent(QShowEvent *);
    void mouseReleaseEvent(QMouseEvent*);

private slots:

    void LoginBtn_Clicked();
    void Timer_Timeout();

public:

    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    QString getUser();
    QString getPwd();

    DataSource* sendConnection();
    void setValFunc(ValFunc);

};

#endif
