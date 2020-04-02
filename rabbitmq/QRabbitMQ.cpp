#include "QRabbitMQ.h"


//https://github.com/mbroadst/qamqp
QRabbitMQ::QRabbitMQ(QObject *parent) :
    QObject(parent),
    globalexchanger(nullptr)
{

    m_serverPort = 0;

    /*
    */
    Readconfig *m_cfg = new Readconfig("../build-untitled1-Desktop_Qt_5_13_1_MinGW_64_bit-Release/config.ini");

    ip=m_cfg->Get("rabbit_mq","ip","127.0.0.1").toString();
    usrname = m_cfg->Get("rabbit_mq","usrname","python_c").toString();
    pwd=m_cfg->Get("rabbit_mq","pwd","python_c").toString();
    virtualhost = m_cfg->Get("rabbit_mq","virtualhost","anodize").toString();
    queues = m_cfg->Get("rabbit_mq","queue","anod_queue").toString();

    delete m_cfg;
//    qDebug()<<"queues ---->>>"<<queues;



    m_client.setHost(ip);
    m_client.setUsername(usrname);
    m_client.setPassword(pwd);
    m_client.setVirtualHost(virtualhost);
    connect(&m_client, SIGNAL(connected()), this, SLOT(clientConnected()));
    m_client.connectToHost();
}

void QRabbitMQ::start()
{
//    connect(&m_client, SIGNAL(connected()), this, SLOT(clientConnected()));

    //Localhost
    //m_client.connectToHost();

    //m_client.connectToHost(QHostAddress(m_serverIP), m_serverPort);


}
void QRabbitMQ::clientConnected()
{
    QAmqpQueue *queue = m_client.createQueue(queues);
    connect(queue, SIGNAL(declared()), this, SLOT(queueDeclared()));
    queue->declare(QAmqpQueue::NoOptions);//这里需要加QAmqpQueue::NoOptions，因为默认是自动删除，可能会被删掉
    qDebug() << "RabbitMQ connect to server ok";
}

void QRabbitMQ::exchangeDeclared()
{

}

void QRabbitMQ::queueDeclared()
{
    QAmqpQueue *queue = qobject_cast<QAmqpQueue*>(sender());
    if (!queue)
        return;
    QAmqpExchange *defaultExchange = m_client.createExchange();
    globalexchanger = defaultExchange;
}

void QRabbitMQ::messageReceived()
{
    QAmqpQueue *temporaryQueue = qobject_cast<QAmqpQueue*>(sender());
    if (!temporaryQueue)
        return;
    QAmqpMessage message = temporaryQueue->dequeue();
    QString msg = "Recv: [x] " + message.routingKey() + ":" + message.payload();
    qDebug() << msg;
    emit msgSig(msg);
}

void QRabbitMQ::sendMsg(const QString &msg)
{
    if(!globalexchanger)
        return;
    globalexchanger->publish(msg, queues);
    qDebug() << " sendMsg() Sent "<<msg;
}

void QRabbitMQ::setServerParam(const QString &ip, int port)
{
    m_serverIP = ip;
    m_serverPort = port;
}

void QRabbitMQ::setRabbitClientParam(const QString &routingKey, const QStringList &bindingKeyList)
{
    m_routingKey = routingKey;
    m_bindingKeyList = bindingKeyList;
}
