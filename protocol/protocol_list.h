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



#endif // PROTOCOL_LIST_H
