#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <MoveToThreadTest.h>

#define TIMER_TIMEOUT   (1*1000)


class Thread_Client : public MoveToThreadTest
{
    Q_OBJECT
public:
    explicit Thread_Client(MoveToThreadTest *parent = nullptr);
    ~Thread_Client();

            QTimer *m_pTimer;//定时器


signals:

public slots:
             void doWork();
             void start();
             void stop();
            void    handleTimeout();  //定时器超时处理函数


};

#endif // TCPCLIENT_H
