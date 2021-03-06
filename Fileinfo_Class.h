#ifndef FILEINFO_CLASS_H
#define FILEINFO_CLASS_H

#include <QObject>
#include <QThread>

#include <QMutex>
#include <QDebug>
#include <QFileDialog>

#include    <iostream>
#include    <iomanip>
#include    <QByteArray>
#include    <QDataStream>
#include    <QTextStream>
#include    <QStringList>
#include    <QFileSystemWatcher>
#include  "protocol/protocol.h"

class Fileinfo_Class : public QObject
{
    Q_OBJECT
public:
    explicit Fileinfo_Class(QObject *parent = nullptr);
    ~ Fileinfo_Class();

    QTextStream *streamadodize[FILENUM];


    QString  srcDirPath;//文件路径      //10.10.10.98/anodize_data/Anod1-Historic/Aalrm_190824
    QString  fileDirPath;//文件目录     //10.10.10.98/anodize_data/Anod1-Historic
    QDir dir;//文件地址
    QStringList nameFilters;//文件类型
    QStringList filelist;//文件清单
//   int filenum;//文件数量
//    QString q_filelist;//文件清单字符串，用于显示用

//    QByteArray array;
    QStringList filedata;//target 文件读取内容

    QFile *pfile;
    bool isOK;
    QTextStream *textStream;


public slots:


private:


};


#endif // FILEINFO_CLASS_H
