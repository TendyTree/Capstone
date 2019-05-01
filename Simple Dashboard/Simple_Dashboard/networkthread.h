#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H
#include <QtCore>
#include <QThread>
#include <QDebug>
#include <QTcpSocket>
class networkThread : public QThread
{
    Q_OBJECT
    //Binds all the getter properties to a name which will be interacted in qml
    Q_PROPERTY(int coolant READ getcoolant NOTIFY coolantchange)
    Q_PROPERTY(int rpm READ getrpm NOTIFY rpmchange)
    Q_PROPERTY(int speed READ getspeed NOTIFY speedchange)
    Q_PROPERTY(int tempature READ gettempature NOTIFY tempaturechange)
    Q_PROPERTY(float airfuel READ getairfuel NOTIFY airfuelchange)
    Q_PROPERTY(float throttle READ getthrottle NOTIFY throttlechange)
    Q_PROPERTY(float voltage READ getvoltage NOTIFY voltagechange)

public:
    networkThread(QObject *parent = nullptr);
    bool begin();
    bool initstart();
    void run() override;
    void startp();
    int getcoolant();
    int getrpm();
    int getspeed();
    int gettempature();
    float getairfuel();
    float getthrottle();
    float getvoltage();


signals:
    void socketerror(QAbstractSocket::SocketError);

    void rpmchange();
    void speedchange();
    void tempaturechange();
    void airfuelchange();
    void throttlechange();
    void voltagechange();
    void coolantchange();
public slots:
    void goterror(QAbstractSocket::SocketError socError);
private:
    QMutex mutex;
    QMutex coolantmutex;
    QMutex rpmmutex;
    QMutex speedmutex;
    QMutex airfuelmutex;
    QMutex airtempmutex;
    QMutex throttlemutex;
    QMutex voltagemutex;
    QByteArray send(QByteArray command);
    void coolant_temp(QByteArray coolantTemp);
    void engine_rpm(QByteArray engineRpm);
    void vehicle_speed(QByteArray vehiclSpeed);
    void air_fuel(QByteArray airFuel);
    void air_Temp(QByteArray airTemp);
    void throttle_position(QByteArray throttlePostion);
    void current_voltage(QByteArray currentVoltage);
    int get_values(QByteArray command, QByteArray message);
    QTcpSocket* tcp = nullptr;
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
#endif // NETWORKTHREAD_H
