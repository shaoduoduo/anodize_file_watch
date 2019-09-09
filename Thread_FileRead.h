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

class Thread_FileRead  : public MoveToThreadTest
{
        Q_OBJECT
public:
    explicit Thread_FileRead(MoveToThreadTest *parent = nullptr);

void    fileread_init();
void    fileread_init_textstream();
signals:
        signalFileStr(QStringList s);
        signalFileStrtoSql(QString s);
private:
//读文件相关

        QString  srcDirPath;//文件路径
        QDir dir;//文件地址
        QStringList nameFilters;//文件类型
        QStringList filelist;//文件清单
        int filenum;//文件数量
        QString q_filelist;//文件清单字符串，用于显示用

        QByteArray array;
        QStringList filedata;//文件读取内容
public slots:
    virtual void doWork();
    virtual void start();
    virtual void stop();
        //文件监视器 处理槽函数
    void    dirChanged(QString path);
    void    fileChanged(QString path);


};

#endif // THREAD_FILEREAD_H
