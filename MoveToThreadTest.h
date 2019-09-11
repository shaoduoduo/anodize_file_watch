#ifndef MOVETOTHREADTEST_H
#define MOVETOTHREADTEST_H

#include <QObject>
#include <QThread>

#include <QMutex>
#include <QDebug>



class MoveToThreadTest : public QObject
{
    Q_OBJECT
public:
    explicit MoveToThreadTest(QObject *parent = nullptr);


    QMutex m_Mutex;
    bool m_bRun;

public slots:
    virtual void doWork();
    virtual void start();
    virtual void stop();

private:

};

#endif // MOVETOTHREADTEST_H
