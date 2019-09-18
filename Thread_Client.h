#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <MoveToThreadTest.h>
#include <QHostAddress>
#include <QTcpSocket>
#include    <QMessageBox>
#include    <QByteArray>
#define TIMER_TIMEOUT   (5*1000)

enum pro_client
{
    PRO_CLIENT_IP,
    PRO_CLIENT_CONN,
    PRO_CLIENT_DISCONN,
    PRO_CLIENT_RECEIVE,
    PRO_CLIENT_ERROR,
    PRO_CLIENT_NUM
};

enum pro_main
{
    PRO_MAIN_INFO,
    PRO_MAIN_NAME,
    PRO_MAIN_IP,
    PRO_MAIN_PORT,
    PRO_MAIN_SEND,
    PRO_MAIN_DISCON,
    PRO_MAIN_ERROR,

    PRO_MAIN_NUM
};

class Thread_Client : public MoveToThreadTest
{
    Q_OBJECT
public:
    explicit Thread_Client(MoveToThreadTest *parent = nullptr);
    ~Thread_Client();

            QTimer *m_pTimer;//定时器

private:
            bool    status;
            int     port;
            QString ip;

            QHostAddress *serverIP;
            QString useName;
            QTcpSocket  *tcpSocket;

signals:
        signalClientlisttomain(QStringList s);

        signalEnter();
        signalDiscon();

        signalSend(QString str);
public slots:
             void doWork();
             void start();
             void stop();
            void    handleTimeout();  //定时器超时处理函数
            void    dealmesfrommain(QStringList s);


            //TCP
            void    slotEnter();
            void    slotConnected();
            void    slotDisconnected();
            void    dataReceived();
            void    slotSend(QString str);
};

#endif // TCPCLIENT_H
