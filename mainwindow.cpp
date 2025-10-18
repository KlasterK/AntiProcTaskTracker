#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tasktypedelegate.h"
#include "tasktimedelegate.h"

#include <QMessageBox>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(std::make_unique<Ui::MainWindow>())
    , m_currentModel(std::in_place_type<EditTaskModel>, m_tasks)
{
    m_ui->setupUi(this);

    m_ui->tableTasks->setModel(&std::get<EditTaskModel>(m_currentModel));
    m_ui->tableTasks->setItemDelegateForColumn(EditTaskModel::Type, new TaskTypeDelegate(this));
    m_ui->tableTasks->setItemDelegateForColumn(EditTaskModel::Time, new TaskTimeDelegate(this));

    connect(m_ui->actionAddTask, &QAction::triggered, this, &MainWindow::addTask);
    connect(m_ui->actionRemoveTasks, &QAction::triggered, this, &MainWindow::deleteTask);
    connect(m_ui->actionStartCountdown, &QAction::triggered, this, &MainWindow::switchMode);
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::deleteLater);
}

MainWindow::~MainWindow()
{}

void MainWindow::addTask()
{
    if(!std::holds_alternative<EditTaskModel>(m_currentModel))
        return;
    const auto &model = std::get<EditTaskModel>(m_currentModel);

    int last_row = model.rowCount(QModelIndex()) - 1;
    auto idx = model.index(last_row, EditTaskModel::Brief);
    m_ui->tableTasks->edit(idx);
}

void MainWindow::deleteTask()
{
    if(!std::holds_alternative<EditTaskModel>(m_currentModel))
        return;
    auto &model = std::get<EditTaskModel>(m_currentModel);

    auto selectionModel = m_ui->tableTasks->selectionModel();
    auto selectedRows = selectionModel->selectedRows();
    for(const auto &index : selectedRows)
    {
        model.removeRow(index.row());
    }
}

void MainWindow::switchMode()
{
    if(std::holds_alternative<EditTaskModel>(m_currentModel))
    {
        m_currentModel.emplace<CountingTaskModel>(m_tasks);
        auto &model = std::get<CountingTaskModel>(m_currentModel);
        m_ui->tableTasks->setModel(&model);
        connect(&model, &CountingTaskModel::taskFinished, this, &MainWindow::notifyTaskFinished);
        connect(&model, &CountingTaskModel::taskListEmptied, this, &MainWindow::notifyTaskListEmptied);
    }
    else if(std::holds_alternative<CountingTaskModel>(m_currentModel))
    {
        m_currentModel.emplace<EditTaskModel>(m_tasks);
        auto &model = std::get<EditTaskModel>(m_currentModel);
        m_ui->tableTasks->setModel(&model);
    }
}

void MainWindow::notifyTaskFinished(const TaskItem &task)
{
    const char *msgBody = nullptr;
    switch(task.type())
    {
    case TaskItem::Work:
        msgBody = "Work session '%1' is finished.";
        break;
    case TaskItem::Rest:
        msgBody = "Break time for '%1' is over.";
        break;
    }

    QMessageBox::information(
        this,
        tr("Time's up!"),
        tr(msgBody).arg(task.brief())
    );
}

void MainWindow::notifyTaskListEmptied()
{
    QMessageBox::information(
        this,
        tr("Tracker"),
        tr("Task list is over!")
    );
}
