#pragma once

#include <QString>
#include <QTime>

class TaskItem
{
public:
    enum Type { Work, Rest };

    static constexpr const char* typeToString(Type type)
    {
        switch(type)
        {
        case Work:
            return "Work";
        case Rest:
            return "Rest";
        default:
            throw std::logic_error("TaskItem::typeToString: invalid type");
        }
    }

public:
    TaskItem() = default;

    inline TaskItem(const QString &brief)
        : m_brief(brief) {}

    inline QString brief() const
    {
        return m_brief;
    }

    inline void setBrief(const QString &newBrief)
    {
        m_brief = newBrief;
    }

    inline Type type() const
    {
        return m_type;
    }

    inline void setType(Type newType)
    {
        m_type = newType;
    }

private:
    QString m_brief;
    Type m_type;
};
