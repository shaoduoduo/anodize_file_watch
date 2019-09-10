#include "Thread_FileRead.h"

Thread_FileRead::Thread_FileRead(MoveToThreadTest *parent) : MoveToThreadTest(parent)
{
        m_bRun = true;
        Start_file_watcher();
}

Thread_FileRead::~Thread_FileRead()
{
        delete fswatcher;
}
void Thread_FileRead::doWork()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());

    qDebug() << msg;



}



void Thread_FileRead::start()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    doWork();
    fileread_init_textstream();
//    while(1)
//    {
//        QThread::sleep(1);
//   //     qDebug() << "Thread_FileRead isRuning ";
//        {
//            QMutexLocker locker(&m_Mutex);
//            if(m_bRun == false)
//                break;
//        }


//    }
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


void Thread_FileRead::fileread_init()//函数不再使用
{

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
                    array +=file.readLine();
                  while(file.atEnd() == false)
                 {
                        array += file.readLine();//将文件中的读取的内容保存在字节数组中。
                  }
    }
     else
         qDebug()<<"文件读取失败";
    file.close();//文件读取完毕后关闭文件。
 //   qDebug()<<array;
//    QString str="filethread id= ";
        QString str=array;
//    str += QString::number(int(QThread::currentThreadId()));
//   str += "  ->";
//   str +=array.data();
    qDebug()<<str;
    //emit signalFileStr(str);
    //emit signalFileStrtoSql("kevin");



}


    void Thread_FileRead::fileread_init_textstream()
{
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


}

    void Thread_FileRead::Start_file_watcher(void)
{
    #if 1
 QFileSystemWatcher *fswatcher = new QFileSystemWatcher();
//                QStringList list ;
//                    list<<"//10.10.10.98/anodize_data/Anod1-Historic/Alarm";
//                    list<<"//10.10.10.98/anodize_data/Anod1-Historic/Anod1-Historic";
//                    list<<"//10.10.10.98/anodize_data/Anod1-Historic/Anod2-Historic";
//                    list<<"//10.10.10.98/anodize_data/Anod1-Historic/Anod3-Historic";
//                      list<<"//10.10.10.98/anodize_data/Anod1-Historic/TC_Data";
//                      list<<"//10.10.10.98/anodize_data/Anod1-Historic/TEMP-Historic";
//                      QStringList s=  fswatcher.addPaths(list);
//                     qDebug()<<"文件监视器添加"<<"------>"<<s.at(0);
               bool isOK= fswatcher->addPath("//10.10.10.98/anodize_data/Alarm");
                if(true==isOK)
                    qDebug()<<"监视成功";
                 isOK= fswatcher->addPath("//10.10.10.98/anodize_data/Alarm/Alarm_190824.csv");
                 if(true==isOK)
                     qDebug()<<"监视成功";
                connect(fswatcher,SIGNAL(directoryChanged(QString)),this,SLOT(dirChanged(QString)));
                connect(fswatcher,SIGNAL(fileChanged(QString)),this,SLOT(fileChanged(QString)));

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
