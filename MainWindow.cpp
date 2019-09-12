#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(TIMER_TIMEOUT);
}

MainWindow::~MainWindow()
{
        closethread();
        delete      m_pMoveThread2 ;
        delete      thread_mysql;
        delete      thread_fileread;

        delete m_pTimer;
        delete ui;

}
    void MainWindow::threadFinished()
    {


    }


//停止线程
void MainWindow::on_pushButton_stop_clicked()
{

     //   closethread();
}

//启动线程
 void MainWindow::starthread()
 {
     //    qDebug() << "MainThreadid: " << (int)QThread::currentThreadId();
     //这个线程已经做成父类，改为调用他的子类
         #if 0
         m_pMoveThread = new MoveToThreadTest();
         m_pMoveThread->moveToThread(&m_Thread);
         connect(&m_Thread,&QThread::started,m_pMoveThread,&MoveToThreadTest::start);
         connect(&m_Thread,&QThread::finished,m_pMoveThread,&MoveToThreadTest::deleteLater);

         //connect(&m_Thread,&QThread::finished,this,&MainWindow::threadFinished);
         m_pMoveThread->doWork();
         m_Thread.start();
         #endif
     #if 1
         m_pMoveThread2 = new MoveToThreadTest2();
         m_pMoveThread2->moveToThread(&m_Thread2);
         connect(&m_Thread2,&QThread::started,m_pMoveThread2,&MoveToThreadTest2::start);
         connect(&m_Thread2,&QThread::finished,m_pMoveThread2,&MoveToThreadTest2::deleteLater);
         //connect(&m_Thread2,&QThread::finished,this,&MainWindow::threadFinished);
         //
         m_Thread2.start();
     #endif
     #if 1
         //开启数据库线程
         thread_mysql    =new Thread_MySQL();
         thread_mysql->moveToThread(&m_thread_sql);
         connect(&m_thread_sql,&QThread::started,thread_mysql,&Thread_MySQL::start);
         connect(&m_thread_sql,&QThread::finished,thread_mysql,&Thread_MySQL::deleteLater);
         connect(this,SIGNAL(signalsendtoMysql(QString)),thread_mysql,SLOT(dealmesfrommain(QString)),Qt::QueuedConnection);

     #endif

         //开启文件读取线程
         thread_fileread    =new Thread_FileRead();
         thread_fileread->moveToThread(&m_thread_fileread);
         connect(&m_thread_fileread,&QThread::started,thread_fileread,&Thread_FileRead::start);
         connect(&m_thread_fileread,&QThread::finished,thread_fileread,&Thread_FileRead::deleteLater);
         //connect(thread_fileread,&Thread_FileRead::signalFileStr,this,&MainWindow::deal_from_fileread);
         connect(thread_fileread,&Thread_FileRead::signalFileStr,this,&MainWindow::deal_from_fileread);
         connect(thread_fileread,&Thread_FileRead::signalFileS,this,&MainWindow::deals_from_fileread);

     #if 1
         //通信
         connect(this,&MainWindow::signalsendtofile,thread_fileread,&Thread_FileRead::dealmesfrommain);//,Qt::DirectConnection);
         connect(thread_fileread,&Thread_FileRead::signalFilelisttoSql,thread_mysql,&Thread_MySQL::deallistfromfile);//data list from file to mysql


     #endif

             m_pMoveThread2->doWork();
             m_thread_sql.start();
             m_thread_fileread.start();
 }

//关闭线程
 void MainWindow::closethread()
 {
     /*
     if(m_pMoveThread)
     {
           qDebug() << "线程有效，关闭线程1 " ;
         m_pMoveThread->stop();
         m_Thread.quit();
         m_Thread.wait();

     m_pMoveThread= NULL;
     }
 */
     if(m_pMoveThread2)
     {
         qDebug() << "线程有效，关闭线程2 " ;
         m_pMoveThread2->stop();
         m_Thread2.quit();
         m_Thread2.wait();
         m_pMoveThread2= NULL;
     }

     if(thread_mysql)
     {
         qDebug() << "线程有效，关闭线程thread_mysql " ;
         thread_mysql->stop();
         m_thread_sql.quit();
         m_thread_sql.wait();

         thread_mysql= NULL;
     }

     if(thread_fileread)
     {
         qDebug() << "线程有效，关闭线程thread_fileread " ;
         thread_fileread->stop();
         m_thread_fileread.quit();
         m_thread_fileread.wait();

         thread_fileread= NULL;
     }
 }


 void MainWindow::on_pushButton_start_clicked()
{
        starthread();

}

 void MainWindow::deal_from_fileread(QStringList s)
    {
        for(int i = 0; i< s.size();++i)
        {
            ui->text_output->append(s.at(i));
        }
    }
    void MainWindow::deals_from_fileread(QString s)
    {
            ui->text_output->append(s);
    }

    void MainWindow::handleTimeout()
    {
        QString msg = QString("%1 -> %2 threadid:[%3]")
                .arg(__FILE__)
                .arg(__FUNCTION__)
                .arg((int)QThread::currentThreadId());
        qDebug() << msg;

        if(m_pTimer->isActive()){
            m_pTimer->start();
        }
    }
