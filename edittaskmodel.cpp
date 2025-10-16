#include "edittaskmodel.h"

int EditTaskModel::rowCount(const QModelIndex &parent) const
{
    return m_tasks.length() + 1; // with <new> task
}

int EditTaskModel::columnCount(const QModelIndex &parent) const
{
    return COLUMNS_COUNT;
}

QVariant EditTaskModel::data(const QModelIndex &index, int role) const
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

bool EditTaskModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return false;

    if(index.row() == m_tasks.length()) // <new> task
    {
        beginInsertRows(QModelIndex(), m_tasks.size(), m_tasks.size());
        m_tasks.append(TaskItem{});
        endInsertRows();
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

QVariant EditTaskModel::headerData(int section, Qt::Orientation orientation, int role) const
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

Qt::ItemFlags EditTaskModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    if(index.row() == m_tasks.length() && index.column() != Brief)
        return Qt::NoItemFlags;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool EditTaskModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 || row + count > m_tasks.size() || count <= 0 || parent.isValid())
        return false;

    emit beginRemoveRows(QModelIndex(), row, row + count - 1);
    m_tasks.remove(row, count);
    emit endRemoveRows();

    return true;
}
