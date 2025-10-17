#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskitem.h"
#include "edittaskmodel.h"

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    QList<TaskItem> m_tasks;
    EditTaskModel m_editTaskModel{m_tasks};

public slots:
    void deleteTask();
};

#endif // MAINWINDOW_H
