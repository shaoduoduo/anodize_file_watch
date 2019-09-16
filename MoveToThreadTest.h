#ifndef MOVETOTHREADTEST_H
#define MOVETOTHREADTEST_H

#include <QObject>
#include <QThread>

#include <QMutex>
#include <QDebug>
#include <QTimer>


class MoveToThreadTest : public QObject
{
    Q_OBJECT
public:
    explicit MoveToThreadTest(QObject *parent = nullptr);
    ~MoveToThreadTest();

    QMutex m_Mutex;
    bool m_bRun;
//            QTimer *m_pTimer;//定时器
//            void    handleTimeout();  //定时器超时处理函数
public slots:
//     void doWork();
//     void start();
//     void stop();

private:

};

#endif // MOVETOTHREADTEST_H
