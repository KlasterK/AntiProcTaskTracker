#include "tasktypedelegate.h"
#include "taskitem.h"

QWidget* TaskTypeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    auto *combobox = new QComboBox(parent);
    combobox->addItem(tr("Work"), TaskItem::Work);
    combobox->addItem(tr("Rest"), TaskItem::Rest);
    combobox->setEditable(false);
    return combobox;
}

void TaskTypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
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

void TaskTypeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto *combobox = qobject_cast<QComboBox*>(editor);
    if(combobox == nullptr)
        return;

    int taskType = combobox->currentData().toInt();
    model->setData(index, taskType, Qt::EditRole);
}
