#ifndef COMPOLENTINFODELEGATE_H
#define COMPOLENTINFODELEGATE_H

#include <QStyledItemDelegate>

class CompolentInfoDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit CompolentInfoDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COMPOLENTINFODELEGATE_H
