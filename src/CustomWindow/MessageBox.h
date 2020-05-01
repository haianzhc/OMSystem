#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "BasicDialog.h"

class MessageBox : public BasicDialog
{
    Q_OBJECT

public:

    MessageBox(QWidget *parent = nullptr,const QString& title = "",const QString& text = "",
               QMessageBox::StandardButtons buttons = QMessageBox::Ok,
               QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

    QAbstractButton *clickedButton() const;
    QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
    // 设置默认按钮
    void setDefaultButton(QPushButton *button);
    void setDefaultButton(QMessageBox::StandardButton button);
    // 设置窗体标题
    void setTitle(const QString &title);
    // 设置提示信息
    void setText(const QString &text);
    // 设置窗体图标
    void setIcon(const QString &icon);
    // 添加控件-替换提示信息所在的QLabel
    void addWidget(QWidget *pWidget);

private slots:

    void onButtonClicked(QAbstractButton *button);

private:

    void translateUI();
    int execReturnCode(QAbstractButton *button);

private:

    QLabel* m_pIconLabel;
    QLabel* m_pLabel;
    QGridLayout* m_pGridLayout;
    QVBoxLayout* m_pVBoxLayout;
    QDialogButtonBox* m_pButtonBox;
    QAbstractButton* m_pClickedButton;
    QAbstractButton* m_pDefaultButton;
};

QMessageBox::StandardButton showInformation(QWidget *parent = nullptr,const QString& title = "",
                                            const QString& text = "",
                                            QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                            QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton showError(QWidget *parent = nullptr,const QString& title = "",
                                      const QString& text = "",
                                      QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                      QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton showSuccess(QWidget *parent = nullptr,const QString& title = "",
                                        const QString& text = "",
                                        QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                        QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton showQuestion(QWidget *parent = nullptr,const QString& title = "",
                                         const QString& text = "",
                                         QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No,
                                         QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton showWarning(QWidget *parent = nullptr,const QString& title = "",
                                        const QString& text = "",
                                        QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                        QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

QMessageBox::StandardButton showCritical(QWidget *parent = nullptr,const QString& title = "",
                                         const QString& text = "",
                                         QMessageBox::StandardButtons buttons = QMessageBox::Ok,
                                         QMessageBox::StandardButton defaultButton = QMessageBox::Ok);

#endif // MESSAGEBOX_H
