#include "Thread_Client.h"

Thread_Client ::Thread_Client(MoveToThreadTest *parent) : MoveToThreadTest(parent)
{


    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(TIMER_TIMEOUT);

}
Thread_Client::~Thread_Client()

{

            delete m_pTimer;
}


void Thread_Client::doWork()
{


}
void Thread_Client::start()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    doWork();

}
void Thread_Client::stop()
{


}



void Thread_Client::handleTimeout()
{
    QString msg = QString("%1 -> %2 threadid:[%3]")
            .arg(__FILE__)
            .arg(__FUNCTION__)
            .arg((int)QThread::currentThreadId());
    qDebug() << msg;

    if(m_pTimer->isActive()){
        m_pTimer->start();
    }
}
