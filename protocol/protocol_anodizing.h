#ifndef PTOTOCOL_ANODIZING_H
#define PTOTOCOL_ANODIZING_H
#include "protocol.h"


//专用封装类。用于封装特定接口，增加特定参数属性

class Ptotocol_Anodizing : public Myprotocol
{
public:
    Ptotocol_Anodizing();

    QString str;

private:
//特定接口对应的参数
    int     ID;
    int Anodizing_UPV;
    int Anodizing_IPV;
    int Anodizing_USV;
    int Anodizing_ISV;
    bool flag;
    char check;
    QString databuf;
    QString timebuf;

};

#endif // PTOTOCOL_ANODIZING_H
