#include "clientv3.h"

ClientV3::ClientV3(QObject *parent) : QObject(parent)
{
    start_commands = {"ATZ\r","ATD0\r","ATSP0\r","ATE0\r","ATH1\r","ATST64\r","ATS0\r","ATAT1\r","0100\r"};
    run_commands = {"0105\r","010C\r","010D\r","0144\r","0146\r","0149\r","ATRV\r"};
    tcp = new QTcpSocket(this);
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
        qInfo() << temp_array;
        if(temp_array.contains("NODATA") || temp_array.contains("CAM ERROR") || temp_array == nullptr ){
            return false;
        //unlock
        }
        //unlock
    }
    qInfo() << "return from start";
    return true;
}
void ClientV3::run(){
    QByteArray temp_recieve;
    qInfo() << "Starting client";
    while(quit){
        for(int i = 0; i < run_commands.size(); i++){
            //mutex here
            temp_recieve = send(run_commands.at(i));
            if(!temp_recieve.contains("CAN ERROR") && temp_recieve != nullptr){
            }else {
            qInfo() <<"can error";
            quit =false;
            break;
            }
            switch (i) {
            case 0:
                coolant_temp(temp_recieve);
                break;
            case 1:
                engine_rpm(temp_recieve);
                break;
            case 2:
                vehicle_speed(temp_recieve);
                break;
            case 3:
                air_fuel(temp_recieve);
                break;
            case 4:
                air_Temp(temp_recieve);
                break;
            case 5:
                throttle_position(temp_recieve);
                break;
            case 6:
                current_voltage(temp_recieve);
                break;
            }
        }
        qInfo() << "coolant temp:" << coolant;
        qInfo() << "RPM:" << rpm;
        qInfo() << "Speed:" << speed;
        qInfo() << "Tempature:" << tempature;
        qInfo() << "Voltage:" << voltage;
        qInfo() << "Throttle:" << throttle;
        qInfo() << "Air Fuel" << airfuel;

    }
    qInfo() <<"ending";
    tcp->close();
}
QByteArray ClientV3::send(QByteArray command){
    tcp->write(command);
    QByteArray buffer;
    bool command_finished = false;
    if(!tcp->waitForBytesWritten(3000)){
        //lock
        quit = false;
        //unlock
    }
    while(!command_finished){
        if(!tcp->waitForReadyRead(3000)){
             emit socketerror(tcp->error());
            //mutex
            quit = false;
            return nullptr;
            //unlock
        }
        buffer.append(tcp->readAll());
        if(buffer.contains('>')){
            command_finished = true;
        }
    }
    //lock
    return buffer;
    //unlock
}
void ClientV3::coolant_temp(QByteArray coolantTemp){
    int temp = 0;
    temp = get_values("4105",coolantTemp);
    coolant = temp - 40;
}
void ClientV3::engine_rpm(QByteArray engineRpm){
    int temp = 0;
    temp = get_values("410C",engineRpm);
    rpm = temp/4;
}
void ClientV3::vehicle_speed(QByteArray vehiclSpeed){
    int temp = 0;
    temp = get_values("410D",vehiclSpeed);
    speed = temp;
}
void ClientV3::air_fuel(QByteArray airFuel){
    float temp = 0;
    temp = get_values("4144", airFuel);
    airfuel = (temp*2)/65536;
}
void ClientV3::air_Temp(QByteArray airTemp){
    int temp = 0;
    temp = get_values("4146",airTemp);
    tempature = temp - 40;
}
void ClientV3::throttle_position(QByteArray throttlePostion){
    float temp = 0;
    temp = get_values("4149", throttlePostion);
    throttle = (temp*100)/255;
}
void ClientV3::current_voltage(QByteArray currentVoltage){
    float tempvalue = 0;
    int temp_int = currentVoltage.indexOf('V');
    QByteArray temp = "";
    temp = currentVoltage.mid(0, temp_int);
    tempvalue = temp.toFloat();
    voltage = tempvalue;
}
int ClientV3::get_values(QByteArray command, QByteArray message){
    bool tempTrue = true;
    int tempValue = 0;
    int tempIter = 0;
    int index = 0;
    while(tempTrue){
        index = message.indexOf(command, index+1);
        if(index != -1){
            tempValue = message.mid(index+4, message.indexOf('\r',index)-index-4).toInt(&tempTrue,16) + tempValue;
        }else {
        break;
        }
        tempIter++;
    }
    return tempValue/tempIter;
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
