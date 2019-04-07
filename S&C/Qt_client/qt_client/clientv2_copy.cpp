#include "clientv2.h"

ClientV2::ClientV2(QObject *parent) : QObject(parent)
{
    tcp = new QTcpSocket(this);
    connect(tcp, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcp, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(goterror(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(socketerror(QAbstractSocket::SocketError)), this, SLOT(goterror(QAbstractSocket::SocketError)));
}
void ClientV2::start(){
    tcp->connectToHost("127.0.0.1",35000);
    if(!tcp->waitForConnected(1000)){
        emit socketerror(tcp->error());
    }
}
void ClientV2::connected(){
    qInfo() << "Welcome to the server!";
    QTextStream msg(stdin);
    QString sendingmsg;
    while(true){
        sendingmsg = msg.readLine();
        if(sendingmsg == "close"){
            break;
        }
        tcp->write(sendingmsg.toUtf8());
        if(!tcp->waitForBytesWritten(1000)){
            break;
        }
        if(!tcp->waitForReadyRead(1000)){
            emit socketerror(tcp->error());
            break;
        }
        qInfo() << tcp->readAll();

    }
    tcp->close();
}
void ClientV2::goterror(QAbstractSocket::SocketError socError){
    switch (socError) {
        case 0:
            qInfo() << "Connection Refused";
            break;
        case 1:
            qInfo() << "Remote Host Closed";
            break;
        case 2:
            qInfo() << "Host Not Found";
            break;
        case 3:
            qInfo() << "Socket Access Error";
            break;
        case 4:
            qInfo() << "Socket Resource Error";
            break;
        case 5:
            qInfo() << "Socket Timeout Error";
            break;
        default:
            qInfo() << "Unkown Error";
    }
}

