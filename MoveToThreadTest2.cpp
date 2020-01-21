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
}

void MoveToThreadTest2::start()
{

    doWork();

}

void MoveToThreadTest2::stop()
{

}
