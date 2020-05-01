#pragma execution_character_set("utf-8")

#include "CompolentInfoDelegate.h"

#include <QApplication>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QStyleOptionComboBox>

CompolentInfoDelegate::CompolentInfoDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void CompolentInfoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    if(index.column() == 1)
    {
        QStyleOptionViewItem viewOption(option);
        initStyleOption(&viewOption, index);

        if (option.state.testFlag(QStyle::State_HasFocus))
        {
            viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
        }

        // ... 省略
        // 设置显示文本为空，使用默认样式
        QStyle *pStyle = viewOption.widget ? viewOption.widget->style() : QApplication::style();

        viewOption.text = "";
        pStyle->drawControl(QStyle::CE_ItemViewItem, &viewOption, painter, viewOption.widget);

        // 需要显示的HTML
        QString strHTML = QString("<html> \
                                  <body>\
                                  <img src=\"" + index.data().toString() + "\" width=\"128\" height=\"128\"> \
                                  </body> \
                                  </html>");

        QTextDocument doc;
        doc.setHtml(strHTML);

        QAbstractTextDocumentLayout::PaintContext paintContext;

        QRect textRect = pStyle->subElementRect(QStyle::SE_ItemViewItemText, &viewOption);
        painter->save();
        // 坐标变换，将左上角设置为原点
        painter->translate(textRect.topLeft() + QPoint(30,10) );
        // 设置HTML绘制区域
        painter->setClipRect(textRect.translated(-textRect.topLeft() - QPoint(30,10)));

        doc.documentLayout()->draw(painter, paintContext);
        painter->restore();
    }
    else
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
