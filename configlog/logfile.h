#ifndef LOGFILE_H
#define LOGFILE_H
#include <QApplication>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif // LOGFILE_H
