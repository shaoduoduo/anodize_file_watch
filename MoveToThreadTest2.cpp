#include "MoveToThreadTest2.h"

MoveToThreadTest2::MoveToThreadTest2(QObject *parent) : QObject(parent)
{


    m_bRun = true;

}


MoveToThreadTest2::~ MoveToThreadTest2()
{


}
void MoveToThreadTest2::doWork()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());

    qDebug() << msg;
}

void MoveToThreadTest2::start()
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
        qDebug() << "MoveToThreadTest --->2  isRuning ";

        {
            QMutexLocker locker(&m_Mutex);
            if(m_bRun == false)
                break;
        }
    }
}

void MoveToThreadTest2::stop()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    QMutexLocker locker(&m_Mutex);
    m_bRun = false;
}
