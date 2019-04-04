#ifndef CLIENT_H
#define CLIENT_H
#include <QtCore>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = nullptr);
    void Connect();


signals:

public slots:
    void recvmsg();
    void sendmsg();

private:
    QTcpSocket *tcp = nullptr;


};


#endif // CLIENT_H
