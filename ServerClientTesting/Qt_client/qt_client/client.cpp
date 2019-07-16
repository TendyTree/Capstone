#include "client.h"
/*
 * Andrew Brashich
 * Network testing
 * V1 please iginore.
*/
client::client(QObject *parent) : QObject(parent)
{
    tcp = new QTcpSocket(this);
    connect(tcp,SIGNAL(readyRead()),this,SLOT(recvmsg()));
    connect(tcp,SIGNAL(connected()), this, SLOT(sendmsg()));

}
void client::Connect(){

    qInfo() <<"Connecting to server!";
    tcp->connectToHost("127.0.0.1",35000);
    tcp->waitForConnected(1000);

}
void client::sendmsg(){
    QTextStream msg(stdin);
    QString sendingmsg;
    qInfo() << "What would you like to send?";
    while(true){
        sendingmsg = msg.readLine();
        if(sendingmsg == "close"){
            tcp->disconnectFromHost();
            break;
        }
        qInfo() << "send";
        tcp->write(sendingmsg.toUtf8());
        tcp->flush();
        QCoreApplication::processEvents();
    }
    return;
}
void client::recvmsg(){
    qInfo() << "recv";
    qInfo() << tcp->readAll();
}
