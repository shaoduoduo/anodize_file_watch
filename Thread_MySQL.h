
#ifndef MYSQLTHREAD_H
#define MYSQLTHREAD_H

#include <QObject>
#include "MoveToThreadTest.h"
class Thread_MySQL : public MoveToThreadTest
{
    Q_OBJECT
public:
    explicit Thread_MySQL(MoveToThreadTest *parent = nullptr);

signals:


public slots:
    virtual void doWork();
    virtual void start();
    virtual void stop();

};

#endif // MYSQLTHREAD_H
