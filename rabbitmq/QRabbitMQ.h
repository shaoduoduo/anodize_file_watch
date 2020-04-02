#ifndef QRABBITMQ_H
#define QRABBITMQ_H

#include <QObject>
#include <QCoreApplication>
#include <QStringList>
#include <QDebug>

#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"
#include "configlog/readconfig.h"

class QRabbitMQ : public QObject
{
    Q_OBJECT
public:
    explicit QRabbitMQ(QObject *parent = nullptr);

    void setServerParam(const QString &ip, int port);
    void setRabbitClientParam(const QString &routingKey, const QStringList &bindingKeyList);

    void sendMsg(const QString &msg);

signals:
    void msgSig(QString msg);

public slots:
    void start();

private slots:
    void clientConnected();
    void exchangeDeclared();
    void queueDeclared();
    void messageReceived();
//    void channelopen();
private:
    QAmqpClient m_client;

    QString m_routingKey;

    //One client can bind many keys
    QStringList m_bindingKeyList;

    QString m_serverIP;
    int m_serverPort;

    QString m_exchangerName;
    QAmqpExchange *globalexchanger;


    QString ip;
    QString usrname;
    QString pwd;
    QString virtualhost;
    QString queues;

};

#endif // QRABBITMQ_H
