#include "Thread_Client.h"
#include <QHostInfo>
Thread_Client ::Thread_Client(MoveToThreadTest *parent) : MoveToThreadTest(parent)
{
    status = false;
    port    = 0;
    serverIP    =   new    QHostAddress();
    tcpSocket   =   new     QTcpSocket(this);


    connect(this,SIGNAL(signalEnter()),this,SLOT(slotEnter()));
    connect(this,SIGNAL(signalSend()),this,SLOT(slotSend()));
    connect(this,SIGNAL(signalDiscon()),this,SLOT(slotEnter()));

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(TIMER_TIMEOUT);

}
Thread_Client::~Thread_Client()

{

            delete  m_pTimer;
            delete  serverIP;
            delete  tcpSocket;
}


void Thread_Client::doWork()
{
    QString localHostName = QHostInfo::localHostName();

    QHostInfo hostInfo =QHostInfo::fromName(localHostName);

    //获得IP

    QList<QHostAddress>listAddress =    hostInfo.addresses();
    if(!listAddress.isEmpty())
    {
      //  listAddress.at(2).toString()
        QStringList s = QStringList(QString("%1").arg(PRO_CLIENT_IP));
        s<<listAddress.at(5).toString();
        emit signalClientlisttomain(s);
    }
}
    void Thread_Client::start()
    {
        QString msg = QString("%1 -> %2 threadid:[%3]")
                .arg(__FILE__)
                .arg(__FUNCTION__)
                .arg((int)QThread::currentThreadId());
        qDebug() << msg;

        doWork();

    }
    void Thread_Client::stop()
    {


    }



        void Thread_Client::handleTimeout()
        {
        //    QString msg = QString("%1 -> %2 threadid:[%3]")
        //            .arg(__FILE__)
        //            .arg(__FUNCTION__)
        //            .arg((int)QThread::currentThreadId());
        //    qDebug() << msg;


                QString  msg ="";
                       msg=QString::number(ANODIZE)+","+QString::number(HEART);
                       msg+=",";
              //  tcpSocket->write(msg.toLatin1(),msg.length());//发送握手信号
                tcpSocket->write(msg.toUtf8().data());
            if(m_pTimer->isActive()){
                m_pTimer->start();
            }
        }



            void    Thread_Client::dealmesfrommain(QStringList s)
            {
                switch (s.at(0).toInt()) {
                case PRO_MAIN_INFO:
                     qDebug()<<"client recieve"<< "PRO_MAIN_INFO"<<s.at(1)<<s.at(2)<<s.at(3);

                     useName =s.at(1);
                     ip =s.at(2);
                     port    =   s.at(3).toInt();
                     emit signalEnter();//开启TCP通信
                    break;
                case PRO_MAIN_DISCON:
                    //
                    emit    signalDiscon();
                    break;
                case PRO_MAIN_SEND:
//                     qDebug()<<"client recieve"<< "PRO_MAIN_SEND"<<s.at(1);
//                     emit   signalSend(s.at(1));
                     //取消信号，采用直接发送的方式
                   // if(false == s.at(1).isEmpty())
                    {


                             QString   msg=QString::number(ANODIZE)+",";
                                msg+=QString::number(SEND_MES)+","+s.at(1);
                                msg+=",";
                       // tcpSocket->write(msg.toLatin1(),msg.length());
                        tcpSocket->write(msg.toUtf8().data());
                     }
                    break;
                case PRO_MAIN_ERROR:

                    break;
                default:
                    break;
                }

            }


    void    Thread_Client::slotEnter()
    {
            if(!status)
            {
                if(!serverIP->setAddress(ip))
                {

                    QStringList s = QStringList(QString("%1").arg(PRO_CLIENT_ERROR));
                    s<<"invalid ip";
                    emit signalClientlisttomain(s);
                    return;
                }
                if(true ==  useName.isEmpty())
                {
                    QStringList s = QStringList(QString("%1").arg(PRO_CLIENT_ERROR));
                    s<<"invalid username";
                    emit signalClientlisttomain(s);
                    return;
                }
                connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()),Qt::UniqueConnection);//防止重复链接
                connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()),Qt::UniqueConnection);
                connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()),Qt::UniqueConnection);

                tcpSocket->connectToHost(*serverIP,port);

                status  =   true;
            }
            else {//改为心跳包
                int length  =0;
                QString msg=useName+tr(":is leave ");
                if((length = tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
                    return;
                tcpSocket->disconnectFromHost();
                status  =   false;

            }
    }
    void    Thread_Client::slotConnected()
    {
        QStringList s = QStringList(QString("%1").arg(PRO_CLIENT_CONN));
        s<<"connect to host";
        emit    signalClientlisttomain(s);

              QString  msg ;
              msg.clear();
             msg =QString::number(ANODIZE)+","+QString::number(HEART);
             msg+=",";
        //tcpSocket->write(msg.toLatin1(),msg.length());//发送握手信号
        tcpSocket->write(msg.toUtf8().data());
    }
    void    Thread_Client::slotDisconnected()
    {
        QStringList s = QStringList(QString("%1").arg(PRO_CLIENT_DISCONN));
        s<<"disconnect from host";
        emit    signalClientlisttomain(s);


    }
    void    Thread_Client::dataReceived()
    {
        while (tcpSocket->bytesAvailable()>0) {
            QByteArray datagram;
            datagram.resize(tcpSocket->bytesAvailable());
            tcpSocket->read(datagram.data(),datagram.size());
            QString msg=datagram.data();

            QStringList s = QStringList(QString("%1").arg(PRO_CLIENT_RECEIVE));
            s<<msg;
            emit    signalClientlisttomain(s);
        }

    }
    void    Thread_Client::slotSend( QString str )
    {
        if(true == str.isEmpty())
            return;

        //tcpSocket->write(str.toLatin1(),str.length());
        tcpSocket->write(str.toUtf8().data());

    }


    void    Thread_Client::dealmesfromfile(QStringList s)//处理文件读取线程获得的数据
    {
        if(true == s.isEmpty())
            return;

        QString msg =s.join(",");
      //  msg+=",";
        switch (s.at(0).toInt()) {
        case ANODIZE:
//需要将协议包分成四种数据来源子包吗？
//---》不分，server直接分配就可以了
           // tcpSocket->write(msg.toLatin1(),msg.length());
            tcpSocket->write(msg.toUtf8().data());
            break;
        case PLASMA:

            break;
        case OPC:

            break;
        case ARCSPRAY:

            break;
        case OEE:

            break;
        default:
            break;
        }

    }


