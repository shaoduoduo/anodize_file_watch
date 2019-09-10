#include "Thread_FileRead.h"

Thread_FileRead::Thread_FileRead(MoveToThreadTest *parent) : MoveToThreadTest(parent)
{
        m_bRun = true;




}

Thread_FileRead::~Thread_FileRead()
{
//           delete fswatcher;

//        for(int i=0;i<FILENAME_MAX;i++)
//        {
//            myfile[i].pfile->close();
//            delete myfile[i].pfile;
//            if(true == myfile[i].isOK)
//            {
//                delete myfile[i].textStream;

//            }
//        }
}



void Thread_FileRead::doWork()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());

    qDebug() << msg;

        Start_file_watcher();

}



void Thread_FileRead::start()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    doWork();

    while(1)
    {
         QThread::sleep(1);
         qDebug() << "Thread_FileRead isRuning ";
        {
            QMutexLocker locker(&m_Mutex);
            if(m_bRun == false)
                break;
        }
    }
}

void Thread_FileRead::stop()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    QMutexLocker locker(&m_Mutex);
    m_bRun = false;
}


void Thread_FileRead::fileread_init()//
{
    #if 0
    for(int i=0;i<FILENAME_MAX;i++)
    {

        myfile[i].fileDirPath =defaultpath;//"//10.10.10.98/anodize_data/Anod1-Historic"//文件目录
        myfile[i].dir       =QDir(myfile[i].srcDirPath);//打开路径
        myfile[i].nameFilters<< "*.csv";//文件类型
        myfile[i].filelist =myfile[i].dir.entryList(myfile[i].nameFilters,
                                                    QDir::Files|QDir::Readable, QDir::Name);
        myfile[i].filenum =myfile[i].filelist.size();//文件数量
        myfile[i].srcDirPath =defaultpath+defaultdirlist.at(i);//具体文件路径??
        myfile[i].pfile=new QFile(myfile[i].srcDirPath);
        myfile[i].isOK = myfile[i].pfile->open(QIODevice::ReadOnly);//以只读的方式打开文件
        if(true == myfile[i].isOK)
        {
            myfile[i].textStream = new QTextStream(myfile[i].pfile);
            myfile[i].textStream->setCodec("GB2312");
            myfile[i].textStream->readLine();

            while`(myfile[i].textStream->atEnd() == false)
            {
                 myfile[i].filedata <<myfile[i].textStream->readLine();
            }
             emit signalFileStr(myfile[i].filedata);

        }
    }
    #endif
}



    void Thread_FileRead::fileread_init_textstream()
{
#if 0
    //线程内容，执行文件读取
    srcDirPath = "//10.10.10.98/anodize_data/Anod1-Historic";//提供文件
    dir=QDir(srcDirPath);

    nameFilters << "*.csv" << "*.*";
    filelist = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    filenum = filelist.size();//文件数量
    q_filelist =filelist.join("\r");//文件清单
    srcDirPath += "/AN19082317020001.csv";//具体文件路径

//  QFile file;//文件指针

    QFile file(srcDirPath);//打开文件

    bool isok = file.open(QIODevice::ReadOnly);//以只读的方式打开文件
     if(isok == true)
    {
                   // QString data;
                   QTextStream textStream(&file);
                   textStream.setCodec("GB2312");
                   textStream.readLine();
                   while(textStream.atEnd() == false)
                   {
                        filedata <<textStream.readLine();
                        // QStringList firstData = textStream.readLine();
                   }
            //   qDebug()<<filedata;
                    emit signalFileStr(filedata);
    }
     else
         qDebug()<<"文件读取失败";
    file.close();//文件读取完毕后关闭文件。
#endif

}

    void Thread_FileRead::Start_file_watcher(void)
{

 //               QFileSystemWatcher *fswatcher = new QFileSystemWatcher();
                    #if 0
//                      QStringList list ;
//                    list<<"//10.10.10.98/anodize_data/Alarm";
//                    list<<"//10.10.10.98/anodize_data/Anod1-Historic";
//                    list<<"//10.10.10.98/anodize_data/Anod2-Historic";
//                    list<<"//10.10.10.98/anodize_data/Anod3-Historic";
//                    list<<"//10.10.10.98/anodize_data/TC_Data";
//                    list<<"//10.10.10.98/anodize_data/TEMP-Historic";
//                      QStringList s=  fswatcher.addPaths(list);
//                     qDebug()<<"文件监视器添加"<<"------>"<<s.at(0);
               bool isOK= fswatcher->addPath(defaultpath);
                if(true==isOK)
                    qDebug()<<"监视成功";
                 isOK= fswatcher->addPath(QString(defaultpath+defaultdirlist.at(0)) );
                 if(true==isOK)
                     qDebug()<<"监视成功";
                connect(fswatcher,SIGNAL(directoryChanged(QString)),this,SLOT(dirChanged(QString)),Qt::DirectConnection);
                connect(fswatcher,SIGNAL(fileChanged(QString)),this,SLOT(fileChanged(QString)),Qt::DirectConnection);

#endif

}
    void    Thread_FileRead::dealmesfrommain(QString s)
    {
        qDebug()<<s;

    }


    void    Thread_FileRead::dirChanged(QString path)
    {
        qDebug()<<path<<"  Thread_FileRead-------dir修改";


    }
    void    Thread_FileRead::fileChanged(QString path)
    {
        qDebug()<<path<<"  Thread_FileRead------file修改";

    }
