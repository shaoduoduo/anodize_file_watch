#ifndef MYPROTOCOL_H
#define MYPROTOCOL_H

#include <QString>

#include "protocol_list.h"
#include<QByteArray>


//基本封装类，用于通用封装

class Myprotocol
{
public:
    Myprotocol();
   // Package成 qtring
    void packdata(QString s);
    //unPack成数据
    void unpackdata(QString s);
private:
    bool checkpack(QString s);//检查校验

};

#endif // MYPROTOCOL_H
