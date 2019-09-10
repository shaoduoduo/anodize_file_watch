#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MoveToThreadTest.h"
#include "MoveToThreadTest2.h"
#include <Thread_MySQL.h>
#include "Thread_FileRead.h"
#include    <QFileSystemWatcher>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void threadFinished();
    void on_pushButton_stop_clicked();

    void on_pushButton_start_clicked();
    void deal_from_fileread(QStringList s);



private:
    Ui::MainWindow *ui;
    MoveToThreadTest    *   m_pMoveThread ;
    QThread     m_Thread;

    MoveToThreadTest2   *   m_pMoveThread2 ;
    QThread     m_Thread2;

    Thread_MySQL        *thread_mysql;
    QThread     m_thread_sql;


    Thread_FileRead        *thread_fileread;
    QThread     m_thread_fileread;


signals:


        signalsendtofile(QString s);
        signalsendtoMysql(QString s);
};

#endif // MAINWINDOW_H
