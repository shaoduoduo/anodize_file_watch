#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <MoveToThreadTest.h>
#include <QHostAddress>
#include <QTcpSocket>
#include    <QMessageBox>
#include    <QByteArray>

#include  "protocol/protocol.h"


#define CLIENTTIMER_TIMEOUT   (5*1000)



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
        void signalClientlisttomain(QStringList s);

        void signalEnter();
        void signalDiscon();

        void signalSend(QString str);
public slots:
             void doWork();
             void start();
             void stop();
            void    handleTimeout();  //定时器超时处理函数
            void    dealmesfrommain(QStringList s);
            void    dealmesfromfile(QStringList s);

            //TCP
            void    slotEnter();
            void    slotConnected();
            void    slotDisconnected();
            void    dataReceived();
            void    slotSend(QString str);
};

#endif // TCPCLIENT_H
