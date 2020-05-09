#ifndef READCONFIG_H
#define READCONFIG_H


#include <QSettings>
#include <QVariant>
#include <QString>
#include <QDebug>

class Readconfig
{
public:
    Readconfig(QString qstrfilename ="");
    ~Readconfig();

    void Set(QString,QString,QVariant);
    QVariant Get(QString,QString);
    QVariant Get(QString,QString,QVariant);
    QVariant Get_and_Default(QString,QString,QVariant);
private:
    QString  m_qstrFileName;
    QSettings *m_psetting;
};

#endif // READCONFIG_H
