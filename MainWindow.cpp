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
    m_pTimer->start(MAINTIMER_TIMEOUT);

    server_Flag = false;
    starthread();

    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
//    ui->textEdit_IP->setText("10.10.10.78");
//    ui->textEdit_port->setText("8888");
//    ui->textEdit_name->setText("kube");
    ui->pushButton_start->setEnabled(false);//关闭开始按键
//    qInstallMessageHandler(myMessageOutput);//会将qudebug输出至文件，暂时不打开

    //获得IP
    QString localHostName = QHostInfo::localHostName();
    QHostInfo hostInfo =QHostInfo::fromName(localHostName);
    QList<QHostAddress>listAddress =    hostInfo.addresses();
    if(listAddress.length()>=2)
        ui->textBrowser_server->append(QString("本地IP地址为 %1").arg(listAddress.at(1).toString()));
//    if(!listAddress.isEmpty())
//    {
//        qDebug()<<"打印本机IP"<<listAddress<<listAddress.length();
//        for (int i = 0;i++;i<listAddress.length()) {
//                ui->textBrowser_server->append(listAddress.at(i).toString());
//                 ui->textBrowser_server->append(QString("本地IP地址为 %1").arg(listAddress.at(i).toString()));
//        }
//    }
}

MainWindow::~MainWindow()
{
        closethread();
//        delete      m_pMoveThread2 ;
//        delete      thread_mysql;
        delete      thread_fileread;
//        delete      thread_client;
        delete      m_pTimer;
        delete      ui;

}
    void MainWindow::threadFinished()
    {


    }


//
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
     #if 0
         m_pMoveThread2 = new MoveToThreadTest2();
         m_pMoveThread2->moveToThread(&m_Thread2);
         connect(&m_Thread2,&QThread::started,m_pMoveThread2,&MoveToThreadTest2::start);
         connect(&m_Thread2,&QThread::finished,m_pMoveThread2,&MoveToThreadTest2::deleteLater);
         //connect(&m_Thread2,&QThread::finished,this,&MainWindow::threadFinished);
         //
         m_Thread2.start();
     #endif
     #if 0
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
         connect(thread_fileread,&Thread_FileRead::signalFiledebug,this,&MainWindow::dealdebug_from_fileread);

         connect(this,&MainWindow::signalsendtoclient,thread_fileread,&Thread_FileRead::dealmesfrommain);

     #if 1
         //通信
//         connect(this,&MainWindow::signalsendtofile,thread_fileread,&Thread_FileRead::dealmesfrommain);//,Qt::DirectConnection);
//         connect(thread_fileread,&Thread_FileRead::signalFilelisttoSql,thread_mysql,&Thread_MySQL::deallistfromfile);//data list from file to mysql
     #endif
     #if 0
         //开启TCP客户端线程
         thread_client    =new Thread_Client;
         thread_client->moveToThread(&m_thread_client);
         connect(&m_thread_client,&QThread::started,thread_client,&Thread_Client::start);
         connect(&m_thread_client,&QThread::finished,thread_client,&Thread_Client::deleteLater);
         connect(thread_client,&Thread_Client::signalClientlisttomain,this,&MainWindow::deal_from_client);
         connect(this,&MainWindow::signalsendtoclient,thread_client,&Thread_Client::dealmesfrommain);
         connect(thread_fileread,&Thread_FileRead::signalFiletoClient,thread_client,&Thread_Client::dealmesfromfile);
     #endif

//             m_thread_sql.start();
             m_thread_fileread.start();
//             m_thread_client.start();


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
//     if(m_pMoveThread2)
//     {
//         qDebug() << "线程有效，关闭线程2 " ;
//         m_pMoveThread2->stop();
//         m_Thread2.quit();
//         m_Thread2.wait();
//         m_pMoveThread2= nullptr;
//     }

//     if(thread_mysql)
//     {
//         qDebug() << "线程有效，关闭线程thread_mysql " ;
//         thread_mysql->stop();
//         m_thread_sql.quit();
//         m_thread_sql.wait();

//         thread_mysql= nullptr;
//     }

     if(thread_fileread)
     {
         qDebug() << "线程有效，关闭线程thread_fileread " ;
         thread_fileread->stop();
         m_thread_fileread.quit();
         m_thread_fileread.wait();

         thread_fileread= nullptr;
     }

//     if(thread_client)
//     {
//         qDebug() << "线程有效，关闭线程thread_client " ;
//         thread_client->stop();
//         m_thread_client.quit();
//         m_thread_client.wait();

//         thread_client= nullptr;
//     }
 }


void MainWindow::on_pushButton_start_clicked()
{
//        starthread();//不再由按键启动，改为自动启动线程，按键连接

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
void MainWindow::dealdebug_from_fileread(QString s)
{
        ui->textBrowser_server->append(s);
}

void MainWindow::handleTimeout()
{
//        QString msg = QString("%1 -> %2 threadid:[%3]")
//                .arg(__FILE__)
//                .arg(__FUNCTION__)
//                .arg((int)QThread::currentThreadId());
//        qDebug() << msg;

    if(m_pTimer->isActive()){
        m_pTimer->start();
    }
}

void MainWindow::deal_from_client(QStringList s)
        {
            switch (s.at(0).toInt())
            {
            case PRO_CLIENT_IP:
                //收到本机IP地址
              ui->label_IP->setText(QString("本地IP地址为 %1").arg(s.at(1)));
              ui->label_IP->setText(s.at(1));
              break;

            case PRO_CLIENT_CONN:
                 ui->text_output->append(s.at(1));
            break;

             case PRO_CLIENT_DISCONN:
                 ui->text_output->append(s.at(1));
             break;
             case PRO_CLIENT_RECEIVE:
                ui->text_output->append(s.at(1));
             break;


            case PRO_CLIENT_ERROR:

                ui->text_output->append(s.at(1));
                break;

            default:
                break;
            }

        }

void MainWindow::on_pushButton_clicked()
{
    //ui->stackedWidget->setCurrentIndex(3);




}

void MainWindow::on_pushButton_connect_clicked()
{
//    QString s;
//    s=QString("%1").arg(PRO_MAIN_INFO);
    //ui->textEdit_name->tex
//    QString str;
//   s<<ui->textEdit_name->toPlainText();
//   s<< ui->textEdit_IP->toPlainText();

//   s<<ui->textEdit_port->toPlainText();
//    emit    signalsendtoclient(s);

    ui->pushButton_connect->setEnabled(false);
    ui->pushButton_disconnect->setEnabled(true);
}
void MainWindow::on_pushButton_disconnect_clicked()
{
//    QString s;
//    s=QString("%1").arg(PRO_MAIN_DISCON);
//    emit    signalsendtoclient(s);

    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
}
//发送按键
void MainWindow::on_pushButton_send_clicked()
{
    QString s;
//    s<<QString("%1").arg(PRO_MAIN_SEND);

    s = ui->textEdit_send->toPlainText();
    if(false == ui->textEdit_send->toPlainText().isEmpty())
        emit    signalsendtoclient(s);

}


