#include "clientv3.h"

ClientV3::ClientV3(QObject *parent) : QObject(parent)
{
    start_commands = {"ATZ\r","ATD0\r","ATSP0\r","ATE0\r","ATH1\r","ATST64\r","ATS0\r","ATAT1\r","0100\r"};
    run_commands = {"0105\r","010C\r","010D\r","0144\r","0146\r","0149\r","ATRV\r"};
    tcp = new QTcpSocket(this);
    connect(tcp, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcp, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(goterror(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(socketerror(QAbstractSocket::SocketError)), this, SLOT(goterror(QAbstractSocket::SocketError)));
}
bool ClientV3::start(){
    tcp->connectToHost("127.0.0.1",35000);
    if(!tcp->waitForConnected(1000)){
        emit socketerror(tcp->error());
        return false;
    }
    return true;
}
bool ClientV3::connected(){
    QByteArray temp_array;
    qInfo() << "Welcome to the server!";
    for(int i = 0; i < start_commands.size(); i++){
        //mutex
        temp_array = send(start_commands.at(i));
        if(temp_array.contains("NODATA") || temp_array.contains("CAM ERROR") || temp_array == nullptr ){
            return false;
            break;
        //unlock
        }
        //unlock
    }
    return true;
}
void ClientV3::run(){
    QByteArray temp_recieve;
    while(quit){
        for(int i = 0; i < run_commands.size(); i++){
            //mutex here
            temp_recieve = send(run_commands.at(i));
            if(!temp_recieve.contains("CAN ERROR") && temp_recieve != nullptr){
                qInfo() << temp_recieve;
            }else {
            quit =false;
            }
            //unlock
        }
    }
}
QByteArray ClientV3::send(QByteArray command){
    tcp->write(command);
    QByteArray buffer;
    bool command_finished = false;
    if(!tcp->waitForBytesWritten(1000)){
        //lock
        quit = false;
        //unlock
    }
    while(!command_finished){
        if(!tcp->waitForReadyRead(1000)){
             emit socketerror(tcp->error());
            //mutex
            quit = false;
            return nullptr;
            //unlock
        }
        buffer.append(tcp->readAll());
        if(buffer.endsWith('>')){
            command_finished = true;
        }
    }
    //lock
    return buffer;
    //unlock
}
void ClientV3::goterror(QAbstractSocket::SocketError socError){
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
