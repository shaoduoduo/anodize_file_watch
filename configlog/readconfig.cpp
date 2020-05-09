#include "readconfig.h"

Readconfig::Readconfig(QString qstrfilename)
    :
    m_qstrFileName("config.ini")
{

    if(qstrfilename.isEmpty()==false)
    {
        m_qstrFileName =qstrfilename;
    }
    m_psetting = new QSettings(m_qstrFileName,QSettings::IniFormat);

}

Readconfig::~Readconfig()
{
    delete m_psetting;
    m_psetting = NULL;

}

void Readconfig::Set(QString qstrnodename, QString qstrkeyname, QVariant qvarvalue)
{
    m_psetting->setValue(QString("%1/%2").arg(qstrnodename).arg(qstrkeyname),qvarvalue);
}
QVariant Readconfig::Get(QString qstrnodename, QString qstrkeyname)
{
    QVariant qvar =m_psetting->value(QString("%1/%2").arg(qstrnodename).arg(qstrkeyname));
    return qvar;
}
QVariant Readconfig::Get(QString qstrnodename, QString qstrkeyname, QVariant defailtvalue)
{
    QVariant qvar =m_psetting->value(QString("%1/%2").arg(qstrnodename).arg(qstrkeyname),defailtvalue);
    return qvar;
}
QVariant Readconfig::Get_and_Default(QString qstrnodename, QString qstrkeyname, QVariant defailtvalue)
{
    QVariant qvar =m_psetting->value(QString("%1/%2").arg(qstrnodename).arg(qstrkeyname),defailtvalue);
    return qvar;
}
