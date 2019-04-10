#ifndef CLIENTV3_H
#define CLIENTV3_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

class ClientV3 : public QObject
{
    Q_OBJECT
public:
    explicit ClientV3(QObject *parent = nullptr);
    bool start();
    void run();
signals:
    void socketerror(QAbstractSocket::SocketError);

public slots:
    bool connected();
    void goterror(QAbstractSocket::SocketError socError);
private:
    QByteArray send(QByteArray command);
    void coolant_temp(QByteArray coolantTemp);
    void engine_rpm(QByteArray engineRpm);
    void vehicle_speed(QByteArray vehiclSpeed);
    void air_fuel(QByteArray airFuel);
    void air_Temp(QByteArray airTemp);
    void throttle_position(QByteArray throttlePostion);
    void current_voltage(QByteArray currentVoltage);
    int get_values(QByteArray command, QByteArray message);
    QTcpSocket *tcp = nullptr;
    QList<QByteArray> run_commands;
    QList<QByteArray> start_commands;
    bool quit = true;
    int coolant = 0;
    int rpm = 0;
    int speed = 0;
    int tempature = 0;
    float voltage = 0;
    float throttle = 0;
    float airfuel = 0;
};
#endif // CLIENTV3_H
