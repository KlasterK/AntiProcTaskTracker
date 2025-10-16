#ifndef TASKTYPEDELEGATE_H
#define TASKTYPEDELEGATE_H

#include "taskitem.h"

#include <QComboBox>
#include <QStyledItemDelegate>


class TaskTypeDelegate : public QStyledItemDelegate
{
public:
    explicit TaskTypeDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {}

    inline QWidget* createEditor(
        QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
    ) const override
    {
        auto *combobox = new QComboBox(parent);
        combobox->addItem("Work", TaskItem::Work);
        combobox->addItem("Rest", TaskItem::Rest);
        combobox->setEditable(false);
        return combobox;
    }

    inline void setEditorData(QWidget *editor, const QModelIndex &index) const override
    {
        auto *combobox = qobject_cast<QComboBox*>(editor);
        if(combobox == nullptr)
            return;

        int taskType = index.data(Qt::EditRole).toInt();
        int cbIndex = combobox->findData(taskType);
        if(cbIndex >= 0)
        {
            combobox->setCurrentIndex(cbIndex);
        }
    }

    inline void setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index
    ) const override
    {
        auto *combobox = qobject_cast<QComboBox*>(editor);
        if(combobox == nullptr)
            return;

        int taskType = combobox->currentData().toInt();
        model->setData(index, taskType, Qt::EditRole);
    }
};

#endif // TASKTYPEDELEGATE_H
