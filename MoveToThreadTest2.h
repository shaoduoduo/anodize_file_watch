#ifndef MOVETOTHREADTEST2_H
#define MOVETOTHREADTEST2_H




#include <QObject>
#include <QThread>

#include <QMutex>
#include <QDebug>
class MoveToThreadTest2 : public QObject
{
    Q_OBJECT
public:
    explicit MoveToThreadTest2(QObject *parent = nullptr);
    ~ MoveToThreadTest2();
public slots:
    void doWork();
    void start();
    void stop();

private:
    QMutex m_Mutex;
    bool m_bRun;

};


#endif // MOVETOTHREADTEST2_H
