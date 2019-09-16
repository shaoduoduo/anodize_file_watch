#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MoveToThreadTest.h"
#include "MoveToThreadTest2.h"
#include <Thread_MySQL.h>
#include "Thread_FileRead.h"
#include    <QFileSystemWatcher>
#include    <QProcess>
#include    "Thread_Client.h"

class QProcess;


namespace Ui {
class MainWindow;
}
#define TIMER_TIMEOUT   (1*1000)
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void starthread();
    void closethread();
private slots:

    void threadFinished();
    void on_pushButton_stop_clicked();

    void on_pushButton_start_clicked();
    void deal_from_fileread(QStringList s);
    void deals_from_fileread(QString s);

            void    handleTimeout();  //定时器超时处理函数
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

    Thread_Client        *thread_client;
    QThread     m_thread_client;

    QTimer *m_pTimer;//定时器
signals:


        signalsendtofile(QString s);
        signalsendtoMysql(QString s);
};

#endif // MAINWINDOW_H
