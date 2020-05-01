#include <QEvent>
#include <QPushButton>
#include <QStatusBar>

#include "MessageBox.h"
#include "FileTool.h"

MessageBox::MessageBox(QWidget *parent,const QString& title,const QString& text,
                       QMessageBox::StandardButtons buttons,
                       QMessageBox::StandardButton defaultButton) : BasicDialog(parent)
{
    setTitle(title);
    setMinimumSize(300,150);
    m_pButtonBox = new QDialogButtonBox(this);
    FileTool::loadSyleSheet(m_pButtonBox,"MessageBox");
    m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    setDefaultButton(defaultButton);

    m_pIconLabel = new QLabel(this);
    m_pLabel = new QLabel(this);

    QPixmap pixmap(":/res/pic/title/information.png");
    m_pIconLabel->setPixmap(pixmap);
    m_pIconLabel->setFixedSize(48, 48);
    m_pIconLabel->setScaledContents(true);

    m_pLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pLabel->setObjectName("whiteLabel");
    m_pLabel->setOpenExternalLinks(true);
    m_pLabel->setText(text);

    m_pGridLayout = new QGridLayout();
    m_pGridLayout->addWidget(m_pIconLabel, 0, 0, 2, 1, Qt::AlignTop);
    m_pGridLayout->addWidget(m_pLabel, 0, 1, 2, 1);
    m_pGridLayout->addWidget(m_pButtonBox, m_pGridLayout->rowCount(), 0, 1, m_pGridLayout->columnCount());
    m_pGridLayout->setSizeConstraint(QLayout::SetNoConstraint);
    m_pGridLayout->setHorizontalSpacing(10);
    m_pGridLayout->setVerticalSpacing(10);
    m_pGridLayout->setContentsMargins(10, 10, 10, 10);

    m_pVBoxLayout->addLayout(m_pGridLayout);

    translateUI();

    connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

    FileTool::loadSyleSheet(this,"MessageBox");
    setLayout(m_pVBoxLayout);
}

void MessageBox::translateUI()
{
    QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
    if (pYesButton != nullptr)
    {
        pYesButton->setText("是");
    }

    QPushButton *pNoButton = m_pButtonBox->button(QDialogButtonBox::No);
    if (pNoButton != nullptr)
    {
        pNoButton->setText("否");
    }

    QPushButton *pOkButton = m_pButtonBox->button(QDialogButtonBox::Ok);
    if (pOkButton != nullptr)
    {
        pOkButton->setText("确定");
    }

    QPushButton *pCancelButton = m_pButtonBox->button(QDialogButtonBox::Cancel);
    if (pCancelButton != nullptr)
    {
        pOkButton->setText("取消");
    }
}

QMessageBox::StandardButton MessageBox::standardButton(QAbstractButton *button) const
{
    return (QMessageBox::StandardButton)m_pButtonBox->standardButton(button);
}

QAbstractButton *MessageBox::clickedButton() const
{
    return m_pClickedButton;
}

int MessageBox::execReturnCode(QAbstractButton *button)
{
    int nResult = m_pButtonBox->standardButton(button);
    return nResult;
}

void MessageBox::onButtonClicked(QAbstractButton *button)
{
    m_pClickedButton = button;
    done(execReturnCode(button));
}

void MessageBox::setDefaultButton(QPushButton *button)
{
    if (!m_pButtonBox->buttons().contains(button))
    {
        return;
    }

    m_pDefaultButton = button;
    button->setDefault(true);
    button->setFocus();
}

void MessageBox::setDefaultButton(QMessageBox::StandardButton button)
{
    setDefaultButton(m_pButtonBox->button(QDialogButtonBox::StandardButton(button)));
}

void MessageBox::setTitle(const QString &title)
{
    setTitleWidget(title);
    m_pVBoxLayout = new QVBoxLayout();
    m_pVBoxLayout->setContentsMargins(0,0,0,0);
    m_pVBoxLayout->addWidget(m_titleWidget);
}

void MessageBox::setText(const QString &text)
{
    m_pLabel->setText(text);
}

void MessageBox::setIcon(const QString &icon)
{
    m_pIconLabel->setPixmap(QPixmap(icon));
}

void MessageBox::addWidget(QWidget *pWidget)
{
    m_pLabel->hide();
    m_pGridLayout->addWidget(pWidget, 0, 1, 2, 1);
}

QMessageBox::StandardButton showInformation(QWidget *parent, const QString &title,
                                            const QString &text, QMessageBox::StandardButtons buttons,
                                            QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/res/pic/title/information.png");

    if (msgBox.exec() == -1)
    {
        return QMessageBox::Cancel;
    }

    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showError(QWidget *parent, const QString &title,
                                      const QString &text, QMessageBox::StandardButtons buttons,
                                      QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/res/pic/title/error.png");

    if (msgBox.exec() == -1)
    {
        return QMessageBox::Cancel;
    }

    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showSuccess(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons,
                                        QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/res/pic/title/success.png");

    if (msgBox.exec() == -1)
    {
        return QMessageBox::Cancel;
    }

    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showQuestion(QWidget *parent, const QString &title,
                                         const QString &text, QMessageBox::StandardButtons buttons,
                                         QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/res/pic/title/question.png");

    if (msgBox.exec() == -1)
    {
        return QMessageBox::Cancel;
    }

    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showWarning(QWidget *parent, const QString &title,
                                        const QString &text, QMessageBox::StandardButtons buttons,
                                        QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/res/pic/title/warning.png");

    if (msgBox.exec() == -1)
    {
        return QMessageBox::Cancel;
    }

    return msgBox.standardButton(msgBox.clickedButton());
}

QMessageBox::StandardButton showCritical(QWidget *parent, const QString &title,
                                         const QString &text, QMessageBox::StandardButtons buttons,
                                         QMessageBox::StandardButton defaultButton)
{
    MessageBox msgBox(parent, title, text, buttons, defaultButton);
    msgBox.setIcon(":/res/pic/title/warning.png");

    if (msgBox.exec() == -1)
    {
        return QMessageBox::Cancel;
    }

    return msgBox.standardButton(msgBox.clickedButton());
}
