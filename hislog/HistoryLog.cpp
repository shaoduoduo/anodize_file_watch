#include "HistoryLog.h"



HistoryLog::HistoryLog(const QString path)
{
//    path = "./his.json";
    qDebug()<<path;
    globalpath =path;


    openjson(globalpath);//获取json文件对象

//初始化，如果没有文件，需要检查，并输入默认参数
/*
 * 后续应该添加默认参数，并保存
 *
*/


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

        isok=false;
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
             isok = false;
             return false;
         }

        if(globaldoc.isObject())
        {
            //把json文档转换为json对象
            globalobj=globaldoc.object();
            isok=true;
            return true;
//            QJsonObject re = getjson("alarm");
//            qDebug()<<re<<"isempty"<<re.isEmpty();
        }
        else {
            qDebug()<<"不是json文件";
        }

//        for (int n =0;n<this->keylist.size();n++)
//        {
//            QString k = this->keylist[n];
//            if (this->getfileflag(k)==false)
//            {
//                this->setfileflag(k,true);
//                this->setfileline(k,0);
//                this->setfileindex(k,0);
//            }
//        }


        return isok;
}

bool HistoryLog::savejson(QString path)
{

    //内存中的数据写到文件
   QJsonDocument doc(globalobj);
   //将json对象转换成字符串
   QByteArray data=doc.toJson();
   QFile file(path);
   file.open(QIODevice::WriteOnly);
   file.write(data);
//   qint64 lines = file.write(data);
//   qDebug()<<lines<<"file.write bytes actually";
   file.close();
   return true;
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
//    getjson(key).value("filename")= value;
//    getjson(key).insert("filename",QJsonValue(value));
//    subObj.insert(secondFlag,jsonvalue);

    QJsonObject obj=  getjson(key);
    obj.insert("filename",QJsonValue(value));
    globalobj.insert(key,QJsonValue(obj));

}
void HistoryLog::setfileline(QString key,int line)
{
//    getjson(key).value("lines")= line;
//    getjson(key).insert("lines",QJsonValue(line));

    QJsonObject obj=  getjson(key);
    obj.insert("lines",QJsonValue(line));
    globalobj.insert(key,QJsonValue(obj));
}

bool HistoryLog::getfileflag(QString key)
{
    bool flag =getjson(key).value("isok").toBool();
    return flag;
}
void HistoryLog::setfileflag(QString key,bool flag)
{
//        getjson(key).value("isok")=flag;
//        getjson(key).insert("isok",QJsonValue(flag));

        QJsonObject obj=  getjson(key);
        obj.insert("isok",QJsonValue(flag));
        globalobj.insert(key,QJsonValue(obj));
}


int HistoryLog::getfileindex(QString key)
{
    return getjson(key).value("index").toInt();
}
void HistoryLog::setfileindex(QString key,int index)
{

    QJsonObject obj=  getjson(key);
    obj.insert("index",QJsonValue(index));
    globalobj.insert(key,QJsonValue(obj));

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
