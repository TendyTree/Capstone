#ifndef CLIENTV2_H
#define CLIENTV2_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

class ClientV2 : public QObject
{
    Q_OBJECT
public:
    explicit ClientV2(QObject *parent = nullptr);
    void start();
signals:
    void socketerror(QAbstractSocket::SocketError);

public slots:
    void connected();
    void goterror(QAbstractSocket::SocketError socError);
private:
    QTcpSocket *tcp = nullptr;
    QList<QByteArray> run_commands;
    QList<QByteArray> start_commands;
};

#endif // CLIENTV2_H
