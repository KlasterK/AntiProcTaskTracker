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

    explicit EditTaskModel(QList<TaskItem> &tasks) : m_tasks(tasks)
    {}

private:
    QList<TaskItem> &m_tasks;

public:
    inline int rowCount(const QModelIndex &parent) const override
    {
        return m_tasks.length() + 1; // with <new> task
    }

    inline int columnCount(const QModelIndex &parent) const override
    {
        return COLUMNS_COUNT;
    }

    inline QVariant data(const QModelIndex &index, int role) const override
    {
        if(index.row() == m_tasks.length()) // <new> task
        {
            switch(index.column())
            {
            case Brief:
                switch(role)
                {
                case Qt::DisplayRole:
                    return tr("<new>");
                case Qt::EditRole:
                    return tr("brief here");
                default:
                    return QVariant();
                }
            default:
                return QVariant();
            }
        }

        TaskItem task = m_tasks[index.row()];
        switch(index.column())
        {
        case Brief:
            switch(role)
            {
            case Qt::DisplayRole:
            case Qt::EditRole:
                return task.brief();
            default:
                return QVariant();
            }
        case Type:
            switch(role)
            {
            case Qt::DisplayRole:
                return tr(TaskItem::typeToString(task.type()));
            case Qt::EditRole: // data for delegate
                return task.type();
            default:
                return QVariant();
            }
        case Time:
            switch(role)
            {
            case Qt::DisplayRole:
                return task.time().toString("mm:ss");
            case Qt::EditRole:
                return task.time();
            }
        default:
            return QVariant();
        }
    }

    inline bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        if(role != Qt::EditRole)
            return false;

        if(index.row() == m_tasks.length()) // <new> task
        {
            addTask(TaskItem{});
        }

        TaskItem &item = m_tasks[index.row()];
        switch(index.column())
        {
        case Brief:
            item.setBrief(value.toString());
            emit dataChanged(index, index);
            return true;
        case Type:
            item.setType(static_cast<TaskItem::Type>(value.toInt()));
            emit dataChanged(index, index);
            return true;
        case Time:
            item.setTime(value.toTime());
            emit dataChanged(index, index);
            return true;
        default:
            return false;
        }
    }

    inline QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
        if(orientation != Qt::Horizontal || role != Qt::DisplayRole)
            return QVariant();

        switch(section)
        {
        case Brief:
            return "Brief";
        case Type:
            return "Type";
        case Time:
            return "Time";
        default:
            return QVariant();
        }
    }

    inline Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if(!index.isValid())
            return Qt::NoItemFlags;

        if(index.row() == m_tasks.length() && index.column() != Brief)
            return Qt::NoItemFlags;

        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
    }

    inline bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override
    {
        if(row < 0 || row + count > m_tasks.size() || count <= 0 || parent.isValid())
            return false;

        beginRemoveRows(QModelIndex(), row, row + count - 1);
        m_tasks.remove(row, count);
        endRemoveRows();

        return true;
    }

    inline void addTask(const TaskItem &task)
    {
        beginInsertRows(QModelIndex(), m_tasks.size(), m_tasks.size());
        m_tasks.append(task);
        endInsertRows();
    }

    inline std::optional<TaskItem> taskAt(int row) const
    {
        if(row < 0 || row >= m_tasks.size())
            return std::nullopt;
        return m_tasks[row];
    }
};

#endif // EDITTASKMODEL_H
