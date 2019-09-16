
#ifndef MYSQLTHREAD_H
#define MYSQLTHREAD_H

#include <QObject>
#include "MoveToThreadTest.h"
#include    <protocol/protocol_anodizing.h>



#define TIMER_TIMEOUT   (1*1000)
class Thread_MySQL : public MoveToThreadTest
{
    Q_OBJECT
public:
    explicit Thread_MySQL(MoveToThreadTest *parent = nullptr);
~Thread_MySQL();

                QTimer *m_pTimer;//定时器

signals:


public slots:
    virtual void doWork();
    virtual void start();
    virtual void stop();

    void    dealmesfrommain(QString s);
    void    deallistfromfile(QStringList s);
            void    handleTimeout();  //定时器超时处理函数
};

#endif // MYSQLTHREAD_H
