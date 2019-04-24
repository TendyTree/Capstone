#include "networkthread.h"
#include <QtCore>
#include <QDebug>

networkThread::networkThread(QObject *parent): QThread(parent)
{
    start_commands = {"ATZ\r","ATD0\r","ATSP0\r","ATE0\r","ATH1\r","ATST64\r","ATS0\r","ATAT1\r","0100\r"};
    run_commands = {"0105\r","010C\r","010D\r","0144\r","0146\r","0149\r","ATRV\r"};
    tcp = new QTcpSocket();
    connect(tcp, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(goterror(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(socketerror(QAbstractSocket::SocketError)), this, SLOT(goterror(QAbstractSocket::SocketError)));
}
bool networkThread::begin(){
    tcp->connectToHost("127.0.0.1",35000);
    if(!tcp->waitForConnected(5000)){
        emit socketerror(tcp->error());
        return false;
    }
    return true;

}
bool networkThread::initstart(){
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
    qInfo() << "return from start and starting thread";
    if (!isRunning()){
        start();
        tcp->moveToThread(this);

    }else {
        qInfo() << "something messed";
    }
    return true;
}
void networkThread::run(){

    QByteArray temp_recieve;
    qInfo() << "Starting client";
    while(quit){
        for(int i = 0; i < run_commands.size(); i++){
            temp_recieve = send(run_commands.at(i));
            if(!temp_recieve.contains("CAN ERROR") && temp_recieve != nullptr){
            }else {
                qInfo() <<"can error";
                quit =false;
            break;
            }
            if(!temp_recieve.contains("NODATA") && temp_recieve != nullptr){

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
QByteArray networkThread::send(QByteArray command){
    QMutexLocker locker(&mutex);
    tcp->write(command);
    QByteArray buffer;
    bool command_finished = false;
    if(!tcp->waitForBytesWritten(5000)){
        quit = false;
    }
    while(!command_finished){
        if(!tcp->waitForReadyRead(5000)){
             emit socketerror(tcp->error());
            quit = false;
            return nullptr;
        }
        buffer.append(tcp->readAll());
        if(buffer.contains('>')){
            command_finished = true;
        }
    }
    return buffer;
}






void networkThread::coolant_temp(QByteArray coolantTemp){
    int temp = 0;
    temp = get_values("4105",coolantTemp);
    coolantmutex.lock();
    coolant = temp - 40;
    emit coolantchange();
    coolantmutex.unlock();
}
void networkThread::engine_rpm(QByteArray engineRpm){
    int temp = 0;
    temp = get_values("410C",engineRpm);
    rpmmutex.lock();
    rpm = temp/4;
    emit rpmchange();
    rpmmutex.unlock();
}
void networkThread::vehicle_speed(QByteArray vehiclSpeed){
    int temp = 0;
    temp = get_values("410D",vehiclSpeed);
    speedmutex.lock();
    speed = temp;
    emit speedchange();
    speedmutex.unlock();
}
void networkThread::air_fuel(QByteArray airFuel){
    float temp = 0;
    temp = get_values("4144", airFuel);
    airfuelmutex.lock();
    airfuel = (temp*2)/65536;
    emit airfuelchange();
    airfuelmutex.unlock();
}
void networkThread::air_Temp(QByteArray airTemp){
    int temp = 0;
    temp = get_values("4146",airTemp);
    airtempmutex.lock();
    tempature = temp - 40;
    emit tempaturechange();
    airtempmutex.unlock();
}
void networkThread::throttle_position(QByteArray throttlePostion){
    float temp = 0;
    temp = get_values("4149", throttlePostion);
    throttlemutex.lock();
    throttle = (temp*100)/255;
    emit throttlechange();
    throttlemutex.unlock();
}
void networkThread::current_voltage(QByteArray currentVoltage){
    float tempvalue = 0;
    int temp_int = currentVoltage.indexOf('V');
    QByteArray temp = "";
    temp = currentVoltage.mid(0, temp_int);
    tempvalue = temp.toFloat();
    voltagemutex.lock();
    voltage = tempvalue;
    emit voltagechange();
    voltagemutex.unlock();
}
int networkThread::get_values(QByteArray command, QByteArray message){
    bool tempTrue = true;
    int tempValue = 0;
    int tempIter = 0;
    int index = 0;
    while(tempTrue){
        index = message.indexOf(command, index+1);
        if(index != -1){
            tempValue = message.mid(index+4, message.indexOf('\r',index)-index-4).toInt(&tempTrue,16) + tempValue;
            tempIter++;
        }else if(tempIter == 0 && index == -1) {
            tempValue = message.mid(0,message.indexOf('\r')).toInt(&tempTrue,16);
            tempIter++;
            break;
        }else {
            break;
        }
    }
    return tempValue/tempIter;

}







int networkThread::getcoolant(){
    int temp;
    coolantmutex.lock();
    temp = coolant;
    coolantmutex.unlock();
    return temp;
}
int networkThread::getrpm(){
    int temp;
    rpmmutex.lock();
    temp = rpm;
    rpmmutex.unlock();
    return temp;
}
int networkThread::getspeed(){
    int temp;
    speedmutex.lock();
    temp = speed;
    speedmutex.unlock();
    return temp;
}
int networkThread::gettempature(){
    int temp;
    airtempmutex.lock();
    temp = tempature;
    airtempmutex.unlock();
    return temp;
}
float networkThread::getairfuel(){
    float temp;
    airfuelmutex.lock();
    temp = airfuel;
    airfuelmutex.unlock();
    return temp;
}
float networkThread::getthrottle(){
    float temp;
    throttlemutex.lock();
    temp = throttle;
    throttlemutex.unlock();
    return temp;
}
float networkThread::getvoltage(){
    float temp;
    voltagemutex.lock();
    temp = voltage;
    voltagemutex.unlock();
    return temp;
}




void networkThread::goterror(QAbstractSocket::SocketError socError){
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
