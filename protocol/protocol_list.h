#ifndef PROTOCOL_LIST_H
#define PROTOCOL_LIST_H
//系统所有设备参数目录


//协议声明文件  //以阳极氧化数据为例

//Date	Time	电流PV	电压PV	电流SV	电压SV

enum AnodizingProtocol
{
    AnodizingProtocol_I_PV=50,
    AnodizingProtocol_U_PV,
    AnodizingProtocol_I_SV,
    AnodizingProtocol_U_SV,
    AnodizingProtocol_end,

    PlasmaProtocol_=100,
    PlasmaProtocol_end,
};



enum pro_client//客户端线程发出协议
{
    PRO_CLIENT_IP,
    PRO_CLIENT_CONN,
    PRO_CLIENT_DISCONN,
    PRO_CLIENT_RECEIVE,
    PRO_CLIENT_ERROR,

    PRO_CLIENT_NUM
};

enum pro_main//主线程发出协议
{
    PRO_MAIN_INFO,
    PRO_MAIN_NAME,
    PRO_MAIN_IP,
    PRO_MAIN_PORT,
    PRO_MAIN_SEND,
    PRO_MAIN_DISCON,
    PRO_MAIN_ERROR,

    PRO_MAIN_NUM
};

enum pro_file//文件线程发出协议
{
    PRO_FILE_ALARM,
    PRO_FILE_ANODI,//
    PRO_FILE_TC,
    PRO_FILE_TEMP,

    PRO_FILE_NUM
};


//存放文件清单
enum PRO_INDEX_ANODIZE
{
    ALARM,
    ANOD1,
    ANOD2,
    ANOD3,
    TCDATA1,
    TCDATA2,
    TEMPHIS,
    FILENUM

};

enum PROTOCOL_INDEX
{
    ANODIZE,//阳极氧化数据
    PLASMA,
    OPC,
    ARCSPRAY,
    OEE,
    HEART,//心跳数据
    PROTOCOL_NUM
};
//协议顺序
//0               1:?   2                 3    4
//PROTOCOL_INDEX,SIZE,PRO_INDEX_ANODIZE,DATA,CHECK


#endif // PROTOCOL_LIST_H
