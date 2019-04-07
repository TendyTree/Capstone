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
    QTcpSocket *tcp = nullptr;
    QList<QByteArray> run_commands;
    QList<QByteArray> start_commands;
    bool quit = true;
    float coolant = 0;
    int rpm = 0;
    int speed = 0;
    float voltage = 0;
    float tempature = 0;
    float acceleration = 0;
};
#endif // CLIENTV3_H
