#include "Thread_FileRead.h"

    Thread_FileRead::Thread_FileRead(MoveToThreadTest *parent) : MoveToThreadTest(parent)
    {
        hislog = new HistoryLog("./his.json");
        QString key = hislog->keylist[0];
//        hislog->setfileindex(key,99);
        hislog->isok = true;
//        hislog->isok = false;


    }

    Thread_FileRead::~Thread_FileRead()
    {
                delete fswatcher;
                delete m_pTimer;
            for(int i=0;i<FILENUM;i++)
            {
    //            if(true == myfile[i].isOK)
    //            {
    //                delete myfile[i].textStream;
    //            }
    //            myfile[i].pfile->close();
    //            delete myfile[i].pfile;
            }
            delete hislog;
    }

    void Thread_FileRead::doWork()
    {
            fileread_init();//文件初始化，读取当前已有文件内容//读取失败，对方未开机。如何处理？？更新的读取进度应该和数据库内容一致才行。
            Start_file_watcher();//监视当前有效的路径和最新的文件
            m_pTimer = new QTimer(this);
            connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
            m_pTimer->start(TIMER_TIMEOUT);

            m_rabbitClient =  new QRabbitMQ();


    }

    void Thread_FileRead::start()
    {
        doWork();
    }

    void Thread_FileRead::stop()
    {
    }

    void Thread_FileRead::fileread_init()//
    {
    //read history
        for(int i=0;i<FILENUM;i++)
        {
            myfile[i].fileDirPath =defaultpath+defaultdirlist.at(i);//"//10.10.10.98/anodize_data/Anod1-Historic"//文件目录
            myfile[i].dir       =QDir(myfile[i].fileDirPath);//打开路径
            myfile[i].nameFilters<< "*.csv";//文件类型
            myfile[i].filelist =myfile[i].dir.entryList(myfile[i].nameFilters,QDir::Files|QDir::Readable, QDir::Name);
            //已有文件数量
            if(0 == myfile[i].filelist.size()){
                continue;
            }
      //更新--》把上次没读取的记录读取上传，并保存记录，然后开始监视
            updateinfo(&myfile[i],hislog,i);
            /****************
            取消更新部分，统一使用更新函数updateinfo,调用之前，更新myfile信息，传入hislog，根据记录更新读取的信息
            ****************/
        }

    }



    void Thread_FileRead::fileread_init_textstream()
{
/*
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
*/

}

    void Thread_FileRead::Start_file_watcher(void)
{
          fswatcher = new QFileSystemWatcher();
               for(int i=0;i<FILENUM;i++)
               {

                   bool isOK= fswatcher->addPath(myfile[i].fileDirPath);

                    if(true==isOK)
                        qDebug()<<myfile[i].fileDirPath<<"路径监视成功";
                    else
                        qDebug()<<myfile[i].fileDirPath<<"路径监视添加失败";
                    if(true == myfile[i].isOK)
                   {
                        isOK= fswatcher->addPath(myfile[i].srcDirPath);
                     if(true==isOK)
                         qDebug()<<myfile[i].srcDirPath<<"文件监视成功";
                     else
                         qDebug()<<myfile[i].srcDirPath<<"文件监视添加失败";
                    }
               }
                connect(fswatcher,SIGNAL(directoryChanged(QString)),this,SLOT(dirChanged(QString)));
                connect(fswatcher,SIGNAL(fileChanged(QString)),this,SLOT(fileChanged(QString)));
}

    void    Thread_FileRead::dealmesfrommain(QString s)
    {
        qDebug()<<s;
    }

    void    Thread_FileRead::dirChanged(QString path)
    {
        int i =0;
        qDebug()<<path<<"-------dir修改";
//                  有文件被修改
//                  1、文件数量变更
//                  2、文件被修改
//                  判断有没有新文件更新（检查文件列表）----》删除旧的文件，将新文件更新到监视器里

        //？？这里需要将最新的文件放在监视器里，两个文件列表对比应该返回一个list，可以是一个，也可以是多个，需要监视最新的那个
        //应该返回新的那个，添加进监视器
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
                if(newsrcDirPath!=nullptr)//add this file in filewatcher
                {
                    bool isOK= fswatcher->removePath(myfile[i].srcDirPath);
                     if(true==isOK)
                        {
                            qDebug()<<myfile[i].srcDirPath<<"旧文件移除监视成功";
                            myfile[i].srcDirPath =path+newsrcDirPath;
                            myfile[i].filelist = newfilelist;
                            isOK= fswatcher->addPath(myfile[i].srcDirPath);
                            if(true==isOK)
                            {
                                qDebug()<<newsrcDirPath<<"更新文件监视成功";
/********************************
取消更新部分，统一使用更新函数
********************************/
                                updateinfo(&myfile[i],hislog,i);
                            }
                        }
                }
            }
        }
    }

    void    Thread_FileRead::fileChanged(QString path)
    {
        int i=0;
//        QStringList filedata_temp;
//        filedata_temp.clear();
        qDebug()<<path<<"------file修改";
        for(i=0;i<FILENUM;i++)//make sure which file is changed
        {
            if(path == myfile[i].srcDirPath){
                updateinfo(&myfile[i],hislog,i);
                break;
                }
        }

    }

    //i  == PRO_INDEX_ANODIZE
    void Thread_FileRead::updateinfo(Fileinfo_Class *ptrfile,HistoryLog *his,int i)//文件信息保存在ptrfile，包括文件内容，，读取指针位置信息保存在hislog内
    {

            if (his->isok==false){
                qDebug()<<"文件读取记录初始化错误";
                return;
            }
            QString key =his->keylist[i];  //key == {"alarm","anod1","anod2","anod3","TC1","TC2","TEMP"};

            int index = his->getfileindex(key);
            int lines = hislog->getfileline(key);

            if(ptrfile->filelist.isEmpty())  { //
                his->setfileflag(key,false);
                return;
            }

            if(ptrfile->filelist.size()<=index){//实际文件比记录的少，记录错误，从0开始
                lines = 0;
                index = 0;
                his->setfileline(key,lines);
                his->setfileindex(key,index);
            }
            //判断上次读取的当前文件位置 ,读当前文件内内剩下的内容---上次读取的也是这个文件,每次进入都要判断，需要才进行读取
            ptrfile->srcDirPath=ptrfile->fileDirPath+ptrfile->filelist.at(index);//具体文件路径

                if(i==TCDATA1||i==TCDATA2)
                {
                    if(ptrfile->filelist.size()!=2){//if it has two file
                        qDebug()<<"天车目录出现异常文件,数量不是2";
                        return;
                    }
                        if(i==TCDATA1)//针对天车数据，专门进行特殊处理
                            ptrfile->srcDirPath =ptrfile->fileDirPath+ptrfile->filelist.at(0);
                        else
                            ptrfile->srcDirPath =ptrfile->fileDirPath+ptrfile->filelist.at(1);
                }
                QThread::msleep(500);
                ptrfile->pfile=new QFile(ptrfile->srcDirPath);
                ptrfile->isOK = ptrfile->pfile->open(QIODevice::ReadOnly);//以只读的方式打开文件
                if(true == ptrfile->isOK)
                {
                    qDebug()<<"打开文件成功";
                    ptrfile->textStream = new QTextStream(ptrfile->pfile);
                    ptrfile->textStream->setCodec("GB2312");
                    ptrfile->textStream->readLine();//drop first line
                    ptrfile->filedata.clear();

                    //初始化：更新文件行数清单等变量
                    while(ptrfile->textStream->atEnd() == false)
                    {
                        ptrfile->filedata <<ptrfile->textStream->readLine();//reload existing data dont need to send
                    }
                    if(ptrfile->filedata.size()>=lines){
                        for(int n=lines;n<ptrfile->filedata.size();n++){
                            emit signalFileS(ptrfile->filedata.at(n));//发送当前文件剩下内容
                            packJson(ptrfile->filedata.at(n),n);
                        }
                    }
                }

                lines = ptrfile->filedata.size();//只是读上次记录的文件，index没有发生改变
//                index = index+1;
                his->setfileline(key,lines);
//                his->setfileindex(key,index);
                qDebug()<<"已经更新到"<<lines<<index;

                //判断当前列表内剩下的文件
                if(ptrfile->filelist.size()>index+1)
                {
                    for(int j=index+1;j<myfile[i].filelist.size();j++)
                    {
                        ptrfile->srcDirPath=ptrfile->fileDirPath+ptrfile->filelist.at(j);//具体文件路径
                        if(i==TCDATA1||i==TCDATA2){//天车数据不会新增文件
                            continue;
                        }
                        ptrfile->pfile->setFileName(ptrfile->srcDirPath);
                        ptrfile->isOK = ptrfile->pfile->open(QIODevice::ReadOnly);//以只读的方式打开文件
                        if(true == ptrfile->isOK)
                        {
                            qDebug()<<"打开文件成功";
                            delete ptrfile->textStream;
                            ptrfile->textStream = new QTextStream(ptrfile->pfile);
                            ptrfile->textStream->setCodec("GB2312");
                            ptrfile->textStream->readLine();//drop first line
                            //初始化：更新文件行数清单等变量
                //            QStringList buflist=QStringList();
                            ptrfile->filedata.clear();

                            while(ptrfile->textStream->atEnd() == false)
                            {
                                 ptrfile->filedata <<ptrfile->textStream->readLine();//reload existing data dont need to send
                            }
                            int n=0;

                                for( n=0;n<ptrfile->filedata.size();n++){
                                    emit signalFileS(ptrfile->filedata.at(n));//发送当前文件剩下内容
                                    packJson(ptrfile->filedata.at(n),n);
                                }
                                qDebug()<<"fileline  已经更新到"<<n<<key<<j;

//                                lines =(n)?(n-1):n;
                                lines = ptrfile->filedata.length();
                                index = j;
                                his->setfileline(key,lines);
                                his->setfileindex(key,index);
                        }
                        //保存lines index
                    }
                }
    /********************************************
                     *
                     *  释放内存
                     *
    ********************************************/
            if(true == ptrfile->isOK)
                delete ptrfile->textStream;
            ptrfile->pfile->close();
            delete ptrfile->pfile;
    }

    //求两个QStringList最新结果返回   （新，旧 ）
    QString Thread_FileRead::getQStringListIntersect( QStringList& commonColumns, QStringList& currentColumns)
    {
        if(commonColumns.count()>currentColumns.count())
        {
            return commonColumns.at(commonColumns.size()-1);
        }
        return nullptr;
    }

    void Thread_FileRead::handleTimeout()
    {
        if(m_pTimer->isActive()){
            m_pTimer->start();
        }
        hislog->trigsavejson();//定时保存记录

    }

    void Thread_FileRead::packJson(QString datastr, PRO_INDEX_ANODIZE item)
    {
        if (datastr.isEmpty())
            return;
        switch(item)
        {
        case ALARM:
            QStringList paralist = datastr.split('\t');
            if (paralist.size()!=4)
                return;//无效数据
            QJsonObject obj;
            obj.insert("time",paralist.at(0));
            obj.insert("date",paralist.at(1));
            obj.insert("status",paralist.at(2));
            obj.insert("msg",paralist.at(3));
            QJsonDocument doc(obj);
            QByteArray databyte= doc.toJson();
            QString datastr(databyte);
            m_rabbitClient->sendMsg(datastr);
        break;
        case ANOD1:
            break;
        case ANOD2:
            break;
        case ANOD3:
            break;
        case TCDATA1:
            break;
        case TCDATA2:
            break;
        case TEMPHIS:
            break;
        }

    }


