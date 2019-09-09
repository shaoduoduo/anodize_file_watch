#ifndef THREAD_FILEREAD_H
#define THREAD_FILEREAD_H
#include <QObject>
#include "MoveToThreadTest.h"

class Thread_FileRead  : public MoveToThreadTest
{
        Q_OBJECT
public:
    explicit Thread_FileRead(MoveToThreadTest *parent = nullptr);


signals:


public slots:
    virtual void doWork();
    virtual void start();
    virtual void stop();

};

#endif // THREAD_FILEREAD_H
