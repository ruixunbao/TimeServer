#include "dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "timeserver.h"
#include <QString>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(QString::fromLocal8Bit("���߳�ʱ�������"));

    Label1 =new QLabel(QString::fromLocal8Bit("�������˿ڣ�"));
    Label2 = new QLabel;

    quitBtn = new QPushButton(QString::fromLocal8Bit("�˳�"));
    QHBoxLayout *BtnLayout = new QHBoxLayout;
    BtnLayout->addStretch(1);
    BtnLayout->addWidget(quitBtn);
    BtnLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(Label1);
    mainLayout->addWidget(Label2);
    mainLayout->addLayout(BtnLayout);

    connect(quitBtn,SIGNAL(clicked()),this,SLOT(close()));

    count=0;
    timeServer = new TimeServer(this);      //pass the dialog ptr to TimeServer class through this ptr
    if(!timeServer->listen())
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("���߳�ʱ�������"),
        QString::fromLocal8Bit("�޷�������������%1.").arg(timeServer->errorString()));
        close();
        return;
    }
    Label1->setText(QString::fromLocal8Bit("�������˿ڣ�%1.").arg(timeServer->serverPort()));
}

Dialog::~Dialog()
{
    
}

void Dialog::slotShow()
{

    Label2->setText(QString::fromLocal8Bit("��%1������ʱ��").arg(++count));
}
