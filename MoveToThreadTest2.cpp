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
            .arg((uint64_t)QThread::currentThreadId());

    qDebug() << msg;
}

void MoveToThreadTest2::start()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((uint64_t)QThread::currentThreadId());
    qDebug() << msg;
    doWork();

}

void MoveToThreadTest2::stop()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((uint64_t)QThread::currentThreadId());
    qDebug() << msg;

}
