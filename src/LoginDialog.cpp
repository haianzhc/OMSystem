/*******************************************************
* @projectName   OMSystem
* @brief         登录对话框
* @author        ZhuHaocheng Xi'an Jiao Tong University
* @email         haianzhc970922@stu.xjtu.edu.cn
* @date          2020-02-03
*******************************************************/

#include "LoginDialog.h"
#include "FileTool.h"
#include "CustomWindow/MessageBox.h"

#include <QPainter>
#include <QTime>
#include <QPalette>
#include <QPixmap>
#include <QDebug>
#include <QBrush>
#include <QMouseEvent>

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent, Qt::WindowCloseButtonHint),
    TitleLabel(this),SystemTitle(this),UserLabel(this), PwdLabel(this),UserEdit(this),
    PwdEdit(this), CaptEdit(this), LoginBtn(this),ExitBtn(this),hideLabel(this),pds(nullptr)
{
    setAutoFillBackground(true);
    QPalette p;
    QPixmap Img;
    Img.load(":/res/pic/login.png");
    p.setBrush(QPalette::Window,QBrush(Img));
    setPalette(p);

    setWindowFlag(Qt::FramelessWindowHint);

    TitleLabel.setScaledContents(true);
    Img.load(":/res/pic/xjtu.png");
    TitleLabel.setPixmap(Img);
    TitleLabel.move(45, 17);
    TitleLabel.resize(Img.size());

    Img.load(":res/pic/systemtitle.png");
    SystemTitle.setPixmap(Img);
    SystemTitle.move(150,20);
    p = SystemTitle.palette();
    p.setColor(QPalette::WindowText,Qt::black);
    SystemTitle.setPalette(p);

    UserLabel.setScaledContents(true);
    Img.load(":/res/pic/user.png");
    UserLabel.setPixmap(Img);
    UserLabel.move(740, 413);
    UserLabel.resize(45, 45);

    UserEdit.setPlaceholderText("请输入用户名");
    UserEdit.move(800, 415);
    UserEdit.resize(360, 40);

    PwdLabel.setScaledContents(true);
    Img.load(":/res/pic/pwd.png");
    PwdLabel.setPixmap(Img);
    PwdLabel.move(740, 483);
    PwdLabel.resize(45,45);

    PwdEdit.setPlaceholderText("请输入密码");
    PwdEdit.move(800, 485);
    PwdEdit.resize(360, 40);
    PwdEdit.setEchoMode(QLineEdit::Password);

    CaptEdit.setPlaceholderText("请输入验证码");
    CaptEdit.move(800,550);
    CaptEdit.resize(170,50);

    hideLabel.move(990,550);
    hideLabel.resize(168,48);
    hideLabel.setToolTip("刷新验证码");

    LoginBtn.setText("登     录");
    LoginBtn.setObjectName("LoginBtn");
    LoginBtn.move(800, 630);
    LoginBtn.resize(357,40);

    ExitBtn.setText("×");
    ExitBtn.setObjectName("ExitBtn");
    ExitBtn.move(1160, 0);
    ExitBtn.resize(40,40);

    setFixedSize(1200, 768);

    m_timer.setParent(this);
    m_timer.start(100);

    connect(&LoginBtn, SIGNAL(clicked()), this, SLOT(LoginBtn_Clicked()));
    connect(&ExitBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(Timer_Timeout()));

    qsrand(uint(QTime::currentTime().second() * 1000 + QTime::currentTime().msec()));

    FileTool::loadSyleSheet(this,"LoginDialog");
}

void LoginDialog::LoginBtn_Clicked()
{
    QString captcha = CaptEdit.text().replace(" ","");

    if(m_captcha.toLower() == captcha.toLower())
    {
        m_user = UserEdit.text().trimmed();
        m_pwd = PwdEdit.text();

        if(m_user == "")
        {
            showInformation(this,"消息","用户名不能为空！");
        }
        else if(m_pwd == "")
        {
            showInformation(this,"消息","密码不能为空！");
        }
        else if( (m_vf != nullptr) && !m_vf(m_user) )
        {
             showError(this, "错误", "用户名不合法，请重新输入！");
        }
        else
        {
            pds = new DataSource(m_user,m_pwd);
            //done(Accepted);

            if(pds->isOpened())
            {
                done(Accepted);
            }
            else
            {
                showError(this, "错误", "数据库连接失败！");
                delete pds;
                m_captcha = getCaptcha();
                CaptEdit.clear();
            }
        }
    }
    else
    {
        showError(this,"错误","验证码输入错误！");

        m_captcha = getCaptcha();

        CaptEdit.clear();
    }

}

QString LoginDialog::getUser()
{
    return m_user;
}

QString LoginDialog::getPwd()
{
    return m_pwd;
}

LoginDialog::~LoginDialog()
{
    delete pds;
}

void LoginDialog::mouseReleaseEvent(QMouseEvent* e)
{
    if(990 <= e->x() && e->x() <= 1158 && 550 <= e->y() && e->y() <= 598)
    {
        m_captcha = getCaptcha();

        CaptEdit.clear();
    }

    QDialog::mouseReleaseEvent(e);
}

void LoginDialog::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    painter.fillRect(990,550,168,48,Qt::black);
    painter.setFont(QFont("Curlz MT",23));

    for(int i = 0;i < 150;i++)
    {
        painter.setPen(m_colors[i % 4]);
        painter.drawPoint(990 + qrand() % 168,550 + qrand() % 48);
    }

    for(int i = 0;i < 4;i++)
    {
        painter.setPen(m_colors[i]);
        painter.drawText(990 + 40 * i,550,40,48,Qt::AlignHCenter,QString(m_captcha[i]));
    }

    QDialog::paintEvent(e);
}

QString LoginDialog::getCaptcha()
{
    QString ret = "";

    for(int i = 0;i < 4;i++)
    {
        int c = (qrand() % 2) ? 'a' : 'A';
        ret += static_cast<QChar>(c + qrand() % 26);
    }

    return ret;
}

Qt::GlobalColor* LoginDialog::getColors()
{
    static Qt::GlobalColor colors[4];

    for(int i = 0;i < 4;i++)
    {
        colors[i] = static_cast<Qt::GlobalColor>(2 + qrand() % 16);
    }

    return colors;
}

void LoginDialog::Timer_Timeout()
{
    m_colors = getColors();

    update();
}

bool LoginDialog::event(QEvent* e)
{
    static bool press = false;
    static QPoint last;

    if(e->type() == QEvent::MouseButtonPress )
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(e);

        if(mouse->button() == Qt::LeftButton)
        {
            press = true;

            last = mouse->globalPos();
        }
    }

    if(e->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(e);

        if(mouse->button() == Qt::LeftButton && press )
        {
            press = false;

            int dx = mouse->globalX() - last.x();
            int dy = mouse->globalY() - last.y();
            move(x() + dx, y() + dy);
        }
    }

    if(e->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouse = dynamic_cast<QMouseEvent* >(e);

        if(press)
        {
            int dx = mouse->globalX() - last.x();
            int dy = mouse->globalY() - last.y();
            last = mouse->globalPos();
            move(x() + dx, y() + dy);
        }
     }

     return QDialog::event(e);
}

void LoginDialog::showEvent(QShowEvent* evt)
{
    m_captcha = getCaptcha();
    m_colors = getColors();

    QDialog::showEvent(evt);
}

void LoginDialog::setValFunc(ValFunc vf)
{
    m_vf = vf;
}

DataSource* LoginDialog::sendConnection()
{
    return pds;
}
