#include "Thread_FileRead.h"

Thread_FileRead::Thread_FileRead(MoveToThreadTest *parent) : MoveToThreadTest(parent)
{
        m_bRun = true;




}

Thread_FileRead::~Thread_FileRead()
{
            delete fswatcher;
            delete m_pTimer;
        for(int i=0;i<FILENUM;i++)
        {
            if(true == myfile[i].isOK)
            {
                delete myfile[i].textStream;
            }
            myfile[i].pfile->close();
            delete myfile[i].pfile;
        }
}



void Thread_FileRead::doWork()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());

    qDebug() << msg;


        fileread_init();
        Start_file_watcher();//监视当前有效的路径和最新的文件
        m_pTimer = new QTimer(this);
        connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
        m_pTimer->start(TIMER_TIMEOUT);
}



void Thread_FileRead::start()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    doWork();

//    while(1)
//    {
//         QThread::sleep(1);
//         qDebug() << "Thread_FileRead isRuning ";
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


void Thread_FileRead::fileread_init()//
{

    #if 1
    for(int i=0;i<FILENUM;i++)
    {

        myfile[i].fileDirPath =defaultpath+defaultdirlist.at(i);//"//10.10.10.98/anodize_data/Anod1-Historic"//文件目录

        myfile[i].dir       =QDir(myfile[i].fileDirPath);//打开路径

        myfile[i].nameFilters<< "*.csv";//文件类型

        myfile[i].filelist =myfile[i].dir.entryList(myfile[i].nameFilters,QDir::Files|QDir::Readable, QDir::Name);

        myfile[i].filenum =myfile[i].filelist.size();//文件数量
        if(0 == myfile[i].filenum)
            continue;
        myfile[i].srcDirPath =myfile[i].fileDirPath+myfile[i].filelist.at(myfile[i].filenum-1);//具体文件路径
        myfile[i].pfile=new QFile(myfile[i].srcDirPath);
        myfile[i].isOK = myfile[i].pfile->open(QIODevice::ReadOnly);//以只读的方式打开文件
        if(true == myfile[i].isOK)
        {
            qDebug()<<"打开文件成功";
            myfile[i].textStream = new QTextStream(myfile[i].pfile);
            myfile[i].textStream->setCodec("GB2312");
            myfile[i].textStream->readLine();//drop first line

            //初始化：更新文件行数清单等变量

            while(myfile[i].textStream->atEnd() == false)
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
          fswatcher = new QFileSystemWatcher();

#if 1

               for(int i=0;i<FILENUM;i++)
               {

                   bool isOK= fswatcher->addPath(myfile[i].fileDirPath);

                    if(true==isOK)
                        qDebug()<<myfile[i].fileDirPath<<"路径监视成功";

                    if(true == myfile[i].isOK)
                   {
                        isOK= fswatcher->addPath(myfile[i].srcDirPath);
                     if(true==isOK)
                         qDebug()<<myfile[i].srcDirPath<<"文件监视成功";
                    }


               }

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
        int i =0;
//        qDebug()<<path<<"-------dir修改";
//                  有文件被修改
//                  1、文件数量变更
//                  2、文件被修改
//                  判断有没有新文件更新（检查文件列表）----》删除旧的文件，将新文件更新到监视器里
        for(i=0;i<FILENUM;i++)
        {
            if(path == myfile[i].fileDirPath)
                break;
        }
        if(true==myfile[i].isOK)
        {
            QStringList newfilelist=myfile[i].dir.entryList(myfile[i].nameFilters,QDir::Files|QDir::Readable, QDir::Name);//
        //find the dif between newfilelist and myfile[i].filelist when new file was added into the dir
            if(newfilelist.count()>myfile[i].filelist.count())//当且仅当文件增加才进行判断
            {
                QString newsrcDirPath =getQStringListIntersect(newfilelist,myfile[i].filelist);
                if(newsrcDirPath!=NULL)//add this file in filewatcher
                {
                    bool isOK= fswatcher->removePath(myfile[i].srcDirPath);
                     if(true==isOK)
                        {
                            qDebug()<<myfile[i].srcDirPath<<"旧文件移除监视成功";
                            myfile[i].srcDirPath =path+newsrcDirPath;
                            myfile[i].filelist = newfilelist;
                            isOK= fswatcher->addPath(path+newsrcDirPath);
                         if(true==isOK)
                            {
                                qDebug()<<newsrcDirPath<<"更新文件监视成功";
                             }
                        }
                }
            }
        }
    }


    void    Thread_FileRead::fileChanged(QString path)
    {
        int i=0,j=0;
        int n=0;
        QStringList filedata_temp;
        qDebug()<<path<<"------file修改";
        for(i=0;i<FILENUM;i++)//make sure which file is changed
        {
            if(path == myfile[i].srcDirPath)
                break;
        }
        if(true == myfile[i].isOK)
        {

//            myfile[i].textStream->seek(0);//set pos
//            myfile[i].textStream->pos();//return pos
            myfile[i].textStream->seek(0);
            myfile[i].textStream->readLine();
            while(myfile[i].textStream->atEnd() == false)
            {
                 filedata_temp <<myfile[i].textStream->readLine();
            }
            if(filedata_temp.size()>myfile[i].filedata.size())//have new line
            {
                n =filedata_temp.size()-myfile[i].filedata.size();
                qDebug()<<n;
                for(j=0;j<n;j++)
                  {
                    emit signalFileS(filedata_temp.at(myfile[i].filedata.size()+j));
                    }
                    myfile[i].filedata =   filedata_temp;
            }



        }
    }
    void Thread_FileRead::handleTimeout()
    {
      //  qDebug()<<"Enter timeout processing function\n";
        if(m_pTimer->isActive()){
            m_pTimer->start();
        }
    }


    //求两个QStringList的区别，结果返回   （旧 ，新）
    QString Thread_FileRead::getQStringListIntersect( QStringList& commonColumns, QStringList& currentColumns)
    {
        if( commonColumns.count() == 0 || currentColumns.count() == 0 )
        {
    //      commonColumns.clear();
            return NULL;
        }
    //    commonColumns.sort();
    //    currentColumns.sort();
bool same =false;
    //    if(commonColumns.count()>currentColumns.count())
        {
                for( int i = 0; i < commonColumns.count(); i++ )
                  {
                        same =false;
                    for( int j = 0; j < currentColumns.count(); j++ )
                    {
                         if(QString::compare( commonColumns[i], currentColumns[j] ) == 0)
                              {
                              same =true;
                             break;
                         }
                    }
                    if(false==same)
                        return commonColumns[i];


                  }

        }
        return NULL;
    }
