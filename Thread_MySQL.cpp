#include "Thread_MySQL.h"

Thread_MySQL::Thread_MySQL(MoveToThreadTest *parent) : MoveToThreadTest(parent)
{
        m_bRun = true;
}


Thread_MySQL::~Thread_MySQL()
{
         delete m_pTimer;

}
void Thread_MySQL::doWork()
{
//    QString msg = QString("%1 -> %2 threadid:[%3]")
//            .arg(__FILE__)
//            .arg(__FUNCTION__)
//            .arg((int)QThread::currentThreadId());

//    qDebug() << msg;

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(TIMER_TIMEOUT);

}

void Thread_MySQL::start()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((uint64_t)QThread::currentThreadId());
    qDebug() << msg;

    doWork();

//    for(;;)
//    {
//        QThread::sleep(1);
//    //    qDebug() << "Thread_MySQL isRuning ";

//        {
//            QMutexLocker locker(&m_Mutex);
//            if(m_bRun == false)
//                break;
//        }
//    }
}

void Thread_MySQL::stop()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((uint64_t)QThread::currentThreadId());
    qDebug() << msg;
}
void    Thread_MySQL::dealmesfrommain(QString s)
{
    qDebug()<<s<<"sql thread";
}


    void    Thread_MySQL::deallistfromfile(QStringList s)
    {
            qDebug()<<"mysql 收到 data"<<s.at(1);
    }
    void Thread_MySQL::handleTimeout()
    {

        if(m_pTimer->isActive()){
            m_pTimer->start();
        }
    }
