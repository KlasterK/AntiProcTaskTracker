#ifndef EDITTASKMODEL_H
#define EDITTASKMODEL_H

#include "taskitem.h"

#include <QAbstractTableModel>
#include <QList>
#include <QVariant>

class EditTaskModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Columns { Brief = 0, Type, Time, COLUMNS_COUNT };

    inline explicit EditTaskModel(QList<TaskItem> &tasks) : m_tasks(tasks) {}

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QList<TaskItem> &m_tasks;
};

#endif // EDITTASKMODEL_H
