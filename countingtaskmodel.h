#ifndef COUNTINGTASKMODEL_H
#define COUNTINGTASKMODEL_H

#include "taskitem.h"

#include <QAbstractTableModel>
#include <QList>
#include <QTimer>
#include <QVariant>

class CountingTaskModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Columns { Brief = 0, Type, Time, COLUMNS_COUNT };

    explicit CountingTaskModel(QList<TaskItem> &tasks);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

signals:
    void taskFinished(const TaskItem &task);
    void taskListEmptied();

private:
    QList<TaskItem> &m_tasks;
    QTimer *m_taskTimer = new QTimer(this);

private slots:
    void taskTimerTimeout();
};

#endif // COUNTINGTASKMODEL_H
