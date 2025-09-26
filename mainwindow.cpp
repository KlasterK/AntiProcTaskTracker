#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tasktypedelegate.h"

#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableTasks->setModel(&m_taskModel);
    ui->tableTasks->setItemDelegateForColumn(TaskModel::Type, new TaskTypeDelegate(this));

    QShortcut *deleteShortcut = new QShortcut(QKeySequence::Delete, ui->tableTasks);
    connect(deleteShortcut, &QShortcut::activated, this, &MainWindow::deleteTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteTask()
{
    auto selectionModel = ui->tableTasks->selectionModel();
    auto selectedRows = selectionModel->selectedRows();
    for(const auto &index : selectedRows)
    {
        m_taskModel.removeRow(index.row());
    }
}
