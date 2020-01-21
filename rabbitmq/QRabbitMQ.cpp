#include "QRabbitMQ.h"


//https://github.com/mbroadst/qamqp
QRabbitMQ::QRabbitMQ(QObject *parent) :
    QObject(parent),
    globalexchanger(nullptr)
{
    m_exchangerName = "tempex";
    m_serverPort = 0;

    /*
    */

    m_client.setHost("127.0.0.1");
    m_client.setUsername("python_c");
    m_client.setPassword("python_c");
    m_client.setVirtualHost("anodize");
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
    QAmqpQueue *queue = m_client.createQueue("hello");
    connect(queue, SIGNAL(declared()), this, SLOT(queueDeclared()));
    queue->declare();
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
//    defaultExchange->publish("1122", "hello");
//    defaultExchange->remove();

//    this->sendMsg("a");

//    this->sendMsg("b");
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

//    QAmqpQueue *queue = qobject_cast<QAmqpQueue*>(sender());
//    if (!queue)
//        return;


//    QAmqpExchange *defaultExchange = m_client.createExchange();
//    defaultExchange->publish(msg, "hello");

//    defaultExchange->close();
//    defaultExchange->remove();

    if(!globalexchanger)
        return;
    globalexchanger->publish(msg, "hello");
    qDebug() << " sendMsg() Sent "<<msg;


//    QAmqpExchange *exchange = m_client.createExchange(m_exchangerName);

//    exchange->publish(msg, "hello");

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
