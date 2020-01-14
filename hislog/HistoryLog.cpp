#include "HistoryLog.h"



HistoryLog::HistoryLog(const QString path)
{
//    path = "./his.json";
    qDebug()<<path;
    globalpath =path;
    openjson(globalpath);
//初始化，如果没有文件，需要检查，并输入默认参数


    qDebug()<<getfilename("alarm")<< getfilename("alarm").isEmpty();
    qDebug()<<getfileline("alarm");
    qDebug()<<getfileindex("alarm");
}




HistoryLog::~HistoryLog()
{
    trigsavejson();//每次关闭时保存--定时保存
}
bool HistoryLog::trigsavejson(void)
{
    return  savejson(globalpath);//每次关闭时保存--定时保存
}

bool HistoryLog::openjson(QString path)
{
    //打开文件
        QFile file(path);
        isok=file.open(QIODevice::ReadWrite);
        qDebug() <<"文件打开结果为"<<isok;
        if (isok==false)
            qDebug() <<"文件错误"<<isok;
        QByteArray data=file.readAll();
        file.close();

        QJsonParseError parseJsonErr;
        //使用json文件对象加载字符串
        globaldoc=QJsonDocument::fromJson(data,&parseJsonErr);
        globaldoc=QJsonDocument::fromJson(data);
        //判断是否对象

        if(!(parseJsonErr.error == QJsonParseError::NoError))
         {
             qDebug()<<("解析json文件错误！")<<parseJsonErr.error;
             return false;
         }

        if(globaldoc.isObject())
        {
            //把json文档转换为json对象
            globalobj=globaldoc.object();
            return true;
//            QJsonObject re = getjson("alarm");
//            qDebug()<<re<<"isempty"<<re.isEmpty();
        }
        else {
            qDebug()<<"不是json文件";

        }
        return false;
}

bool HistoryLog::savejson(QString path)
{

    //内存中的数据写到文件
   QJsonDocument doc(globalobj);
   //将json对象转换成字符串
   QByteArray data=doc.toJson();
   QFile file(path);
   file.open(QIODevice::WriteOnly);
   qint64 lines = file.write(data);
   qDebug()<<lines<<"actually";
   file.close();
   return lines;
}
QJsonObject HistoryLog::getjson(QString svalue)
{
    //            qDebug() <<"json对象  QJsonObject"<<obj;
    QJsonObject subobj;

    if(globalobj.contains(svalue))
     {
        subobj = globalobj.value(svalue).toObject();
     }
                    return subobj;
//
}

QString HistoryLog::getfilename(QString key)
{
    QString res;
    res = getjson(key).value("filename").toString();

    return res;
}
int HistoryLog::getfileline(QString key)
{
    int res = 0;
    res = getjson(key).value("lines").toInt();
    return res;
}
void HistoryLog::setfilename(QString key ,QString value)
{
    getjson(key).value("filename")= value;

}
void HistoryLog::setfileline(QString key,int line)
{
    getjson(key).value("lines")= line;

}

bool HistoryLog::getfileflag(QString key)
{
    bool flag =getjson(key).value("isok").toBool();
    return flag;
}
void HistoryLog::setfileflag(QString key,bool flag)
{
        getjson(key).value("isok")=flag;
}


int HistoryLog::getfileindex(QString key)
{
    return getjson(key).value("index").toInt();
}
void HistoryLog::setfileindex(QString key,int index)
{
    getjson(key).value("index")=index;
}


QJsonObject::iterator HistoryLog::insertsubkey(QString key,QString subkey,QString value)
{
        QJsonObject::iterator it = getjson(key).insert(subkey,QJsonValue(value));
        return it;
}

QJsonObject::iterator HistoryLog::insertkey(QString key,QJsonObject obj)
{
        QJsonObject::iterator it = globalobj.insert(key,QJsonValue(obj));
        return it;
}

//QJsonObject obj;
//QJsonObject sub;
//sub.insert("ip",QJsonValue("192.168.0.1"));
//sub.insert("port",QJsonValue("8080"));
//obj.insert("server",QJsonValue(sub));
