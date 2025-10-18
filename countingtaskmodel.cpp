#include "countingtaskmodel.h"

#include <QApplication>
#include <QMessageBox>

CountingTaskModel::CountingTaskModel(QList<TaskItem> &tasks)
    : m_tasks(tasks)
{
    connect(m_taskTimer, &QTimer::timeout, this, &CountingTaskModel::taskTimerTimeout);
    m_taskTimer->start(1000);
}

int CountingTaskModel::rowCount(const QModelIndex &parent) const
{
    return m_tasks.length();
}

int CountingTaskModel::columnCount(const QModelIndex &parent) const
{
    return COLUMNS_COUNT;
}

QVariant CountingTaskModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    TaskItem task = m_tasks[index.row()];
    switch(index.column())
    {
    case Brief:
        return task.brief();
    case Type:
        return tr(TaskItem::typeToString(task.type()));
    case Time:
            return task.time().toString("mm:ss");
    default:
        return QVariant();
    }
}

QVariant CountingTaskModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    switch(section)
    {
    case Brief:
        return tr("Brief");
    case Type:
        return tr("Type");
    case Time:
        return tr("Time");
    default:
        return QVariant();
    }
}

void CountingTaskModel::taskTimerTimeout()
{
    if(m_tasks.isEmpty())
    {
        m_taskTimer->stop();
        return;
    }

    auto newTime = m_tasks[0].time().addSecs(-1);
    if(newTime > m_tasks[0].time())
    {
        // Time wrapped back = time ended
        emit taskFinished(m_tasks[0]);

        emit beginRemoveRows(QModelIndex(), 0, 0);
        m_tasks.pop_front();
        emit endRemoveRows();

        if(m_tasks.isEmpty())
        {
            // No more tasks left
            emit taskListEmptied();
            m_taskTimer->stop();
        }

        return;
    }
    m_tasks[0].setTime(newTime);
    emit dataChanged(index(0, Time), index(0, Time));
}


