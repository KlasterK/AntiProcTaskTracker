#ifndef TASKTIMEDELEGATE_H
#define TASKTIMEDELEGATE_H

#include "taskitem.h"

#include <QComboBox>
#include <QStyledItemDelegate>
#include <QTimeEdit>


class TaskTimeDelegate : public QStyledItemDelegate
{
public:
    explicit TaskTimeDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {}

    inline QWidget* createEditor(
        QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
    ) const override
    {
        auto *edit = new QTimeEdit(parent);
        edit->setDisplayFormat("mm:ss");
        edit->setTimeRange(QTime(0, 0, 0), QTime(1, 0, 0));
        return edit;
    }
};

#endif // TASKTIMEDELEGATE_H
