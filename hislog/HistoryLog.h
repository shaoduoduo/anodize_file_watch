#ifndef HISTORYLOG_H
#define HISTORYLOG_H

#include <QObject>
#include <Fileinfo_Class.h>
#include <QString>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include <QJsonParseError>
#include <QDebug>

class HistoryLog
{
public:
    HistoryLog(const QString path);

    ~HistoryLog();

    bool openjson(QString path);//首次打开配置
    bool savejson(QString path);//析构调用
    bool trigsavejson(void);//单次调用保存

    QString getfilename(QString key);
    int getfileline(QString key);

    void setfilename(QString key,QString value);
    void setfileline(QString key,int line);

    bool getfileflag(QString key);
    void setfileflag(QString key,bool flag);

    int getfileindex(QString key);
    void setfileindex(QString key,int index);

    QJsonObject::iterator insertsubkey(QString key,QString subkey,QString value);
    QJsonObject::iterator insertkey(QString key,QJsonObject obj);


    bool isok;
    QJsonObject getjson(QString svalue);
    QJsonObject globalobj;
    QJsonDocument globaldoc;
    QString globalpath;


};

#endif // HISTORYLOG_H
