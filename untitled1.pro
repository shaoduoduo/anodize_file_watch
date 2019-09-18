#-------------------------------------------------
#
# Project created by QtCreator 2019-09-05T19:39:32
#
#-------------------------------------------------

QT       += core gui widgets
QT += network
TARGET = untitled1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    MoveToThreadTest.cpp \
    MoveToThreadTest2.cpp \
    Thread_MySQL.cpp \
    Thread_FileRead.cpp \
    Fileinfo_Class.cpp \
    protocol/protocol_anodizing.cpp \
    protocol/protocol.cpp \
    Thread_Client.cpp

HEADERS += \
        MainWindow.h \
    MoveToThreadTest.h \
    MoveToThreadTest2.h \
    Thread_MySQL.h \
    Thread_FileRead.h \
    Fileinfo_Class.h \
    protocol/protocol_list.h \
    protocol/protocol_anodizing.h \
    protocol/protocol.h \
    Thread_Client.h

FORMS += \
        MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    说明.txt
