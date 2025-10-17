#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tasktypedelegate.h"
#include "tasktimedelegate.h"

#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(std::make_unique<Ui::MainWindow>())
{
    m_ui->setupUi(this);

    m_ui->tableTasks->setModel(&m_editTaskModel);
    m_ui->tableTasks->setItemDelegateForColumn(EditTaskModel::Type, new TaskTypeDelegate(this));
    m_ui->tableTasks->setItemDelegateForColumn(EditTaskModel::Time, new TaskTimeDelegate(this));

    connect(m_ui->actionAddTask, &QAction::triggered, this, [this]
    {
        int last_row = m_editTaskModel.rowCount(QModelIndex()) - 1;
        auto idx = m_editTaskModel.index(last_row, EditTaskModel::Brief);
        m_ui->tableTasks->edit(idx);
    });
    connect(m_ui->actionRemoveTasks, &QAction::triggered, this, &MainWindow::deleteTask);
    connect(m_ui->actionQuit, &QAction::triggered, this, &MainWindow::deleteLater);
}

MainWindow::~MainWindow()
{}

void MainWindow::deleteTask()
{
    auto selectionModel = m_ui->tableTasks->selectionModel();
    auto selectedRows = selectionModel->selectedRows();
    for(const auto &index : selectedRows)
    {
        m_editTaskModel.removeRow(index.row());
    }
}
