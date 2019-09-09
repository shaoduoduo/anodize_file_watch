#include "Thread_FileRead.h"

Thread_FileRead::Thread_FileRead(MoveToThreadTest *parent) : MoveToThreadTest(parent)
{
        m_bRun = true;
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

    for(;;)
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
