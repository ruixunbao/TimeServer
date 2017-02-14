#include "timeserver.h"
#include "timethread.h"
#include "dialog.h"

TimeServer::TimeServer(QObject *parent)
    :QTcpServer(parent)
{
    dlg =(Dialog *)parent;      //��parent�������ݸ�TimeServer������ݳ�Ա��ʹ���ڴ����п��Է��ʵ����õ�Dialog��
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
