#include "timeserver.h"
#include "timethread.h"
#include "dialog.h"

TimeServer::TimeServer(QObject *parent)
    :QTcpServer(parent)
{
    dlg =(Dialog *)parent;      //把parent参数传递给TimeServer类的数据成员，使得在此类中可以访问到调用的Dialog类
}

void TimeServer::incomingConnection(int socketDescriptor)
{
    qDebug() << "a new connection coming!!";
    TimeThread *thread = new TimeThread(socketDescriptor,0);

    QString temp = "new QString";
    connect(thread,SIGNAL(finished()),dlg,SLOT(slotShow()));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()),Qt::DirectConnection);

    thread->start();
}
