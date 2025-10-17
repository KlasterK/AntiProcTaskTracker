#ifndef TASKTYPEDELEGATE_H
#define TASKTYPEDELEGATE_H

#include <QComboBox>
#include <QStyledItemDelegate>

class TaskTypeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    inline explicit TaskTypeDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent) {}

    QWidget* createEditor(
        QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index
    ) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(
        QWidget *editor,
        QAbstractItemModel *model,
        const QModelIndex &index
    ) const override;
};

#endif // TASKTYPEDELEGATE_H
