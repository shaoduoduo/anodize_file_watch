#include "MoveToThreadTest.h"

MoveToThreadTest::MoveToThreadTest(QObject *parent) : QObject(parent)
{
   // m_bRun = true;

//    m_pTimer = new QTimer(this);
//    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
//    m_pTimer->start(TIMER_TIMEOUT);
}

MoveToThreadTest::~MoveToThreadTest()
{

           // delete m_pTimer;
}
//void MoveToThreadTest::doWork()
//{
//    QString msg = QString("%1 -> %2 threadid:[%3]")
//            .arg(__FILE__)
//            .arg(__FUNCTION__)
//            .arg((int)QThread::currentThreadId());

//    qDebug() << msg;
//}

//void MoveToThreadTest::start()
//{
//    QString msg = QString("%1 -> %2 threadid:[%3]")
//            .arg(__FILE__)
//            .arg(__FUNCTION__)
//            .arg((int)QThread::currentThreadId());
//    qDebug() << msg;

//    doWork();

//    for(;;)
//    {
//        QThread::sleep(1);
//        qDebug() << "MoveToThreadTest isRuning ";

//        {
//            QMutexLocker locker(&m_Mutex);
//            if(m_bRun == false)
//                break;
//        }
//    }
//}

//void MoveToThreadTest::stop()
//{
//    QString msg = QString("%1 -> %2 threadid:[%3]")
//            .arg(__FILE__)
//            .arg(__FUNCTION__)
//            .arg((int)QThread::currentThreadId());
//    qDebug() << msg;

//    QMutexLocker locker(&m_Mutex);
//    m_bRun = false;
//}

//void MoveToThreadTest::handleTimeout()
//{
//    QString msg = QString("%1 -> %2 threadid:[%3]")
//            .arg(__FILE__)
//            .arg(__FUNCTION__)
//            .arg((int)QThread::currentThreadId());
//    qDebug() << msg;

//    if(m_pTimer->isActive()){
//        m_pTimer->start();
//    }
//}

