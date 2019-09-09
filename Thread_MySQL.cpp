#include "Thread_MySQL.h"

Thread_MySQL::Thread_MySQL(MoveToThreadTest *parent) : MoveToThreadTest(parent)
{
        m_bRun = true;
}



void Thread_MySQL::doWork()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());

    qDebug() << msg;
}

void Thread_MySQL::start()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    doWork();

    for(;;)
    {
        QThread::sleep(3);
        qDebug() << "Thread_MySQL isRuning ";

        {
            QMutexLocker locker(&m_Mutex);
            if(m_bRun == false)
                break;
        }
    }
}

void Thread_MySQL::stop()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    QMutexLocker locker(&m_Mutex);
    m_bRun = false;
}
