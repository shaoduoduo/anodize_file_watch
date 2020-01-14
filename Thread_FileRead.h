#ifndef THREAD_FILEREAD_H
#define THREAD_FILEREAD_H
#include <QObject>
#include "MoveToThreadTest.h"


#include <QFileDialog>

#include <iostream>
#include <iomanip>
#include <QByteArray>

#include    <QDebug>
#include    <QThread>
#include    <QDataStream>
#include    <QTextStream>
#include    <QStringList>
#include    <QFileSystemWatcher>
#include    <Fileinfo_Class.h>
#include    <QTimer>
#include    <protocol/protocol_anodizing.h>
#include  "protocol/protocol.h"
#include "hislog/HistoryLog.h"

#define TIMER_TIMEOUT   (5*1000)
class QTimer;
class Thread_FileRead  : public MoveToThreadTest
{
        Q_OBJECT
public:
    explicit Thread_FileRead(MoveToThreadTest *parent = nullptr);
        ~Thread_FileRead();
void    fileread_init();
void    fileread_init_textstream();
signals:
        void signalFileS(QString s);
        void signalFileStr(QStringList s);
        void signalFiletoClient(QStringList s);
        void signalFileStrtoSql(QString s);
        void signalFilelisttoSql(QStringList s);
private:
//读文件相关

        QFileSystemWatcher *fswatcher;//文件监视器
        void    Start_file_watcher();

        Fileinfo_Class  myfile[FILENUM];        //面向文件操作的类

        const  QStringList defaultdirlist=(QStringList()<<"/Alarm/"<<"/Anod1-Historic/"<<"/Anod2-Historic/"
                                    <<"/Anod3-Historic/"<<"/TC_Data/"<<"/TC_Data/"<<"/TEMP-Historic/");
       // const   QString defaultpath="//10.10.10.98/anodize_data";
        QString defaultpath="C:/Users/gyshao/Desktop/data";

        QTimer *m_pTimer;//定时器

        QString getQStringListIntersect( QStringList& commonColumns,
                                         QStringList& currentColumns);

        HistoryLog *hislog;
public slots:
             void doWork();
             void start();
             void stop();
        //文件监视器 处理槽函数
            void    dirChanged(QString path);
            void    fileChanged(QString path);
            void    dealmesfrommain(QString s);

            void    handleTimeout();  //定时器超时处理函数

};

#endif // THREAD_FILEREAD_H
