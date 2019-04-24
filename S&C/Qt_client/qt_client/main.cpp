#include <QCoreApplication>
#include <client.h>
#include <clientv3.h>
#include <iostream>
#include <QDebug>
/* Andrew Brashich
 * Capstone Client Networking Protoyping
 *
 * Client was me testing and getting a hold of how the QTcpsocket work, along with connecting manually
 * to the event loop. It contains a lot of spaghetti code and is not efficient as it does not involve
 * threading, thus the event loop is not called in time to call the signals. This results in not all
 * data being read.
 *
 * Client V2 is a straight forward example of how the client will interact with the ELM 327 based
 * on the current documentation available. It won’t be as fancy with a recv slot as the ELM architecture
 * only sends data back to you once you request it and is easily handle. If the architecture
 * was different, it would make sense to have a recv slot. However this class will end up being part
 * of a multi-threaded application thus there is no need to. It will not contain any fancy function to
 * deal with data, that will be over in the final version.
 *
 * If I do have time for a V3 I will implement a recv slot as it could be useful in the final program.
 * This would add complexity but would also work, although the benefit may be limited
 *
 * In my github I will include the documentation of the ELM 327 and a flow chart with how data is
 * communicated.
 *
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ClientV3 _client;
    client mclient;
    mclient.Connect();
    mclient.sendmsg();

    /*
    qInfo() << "Hello and welcome to the TCP network connection. Please send something:";
    if(_client.start()){
        qInfo() << "next";
        if(_client.connected()){
            qInfo() << "next";
            _client.run();
        }else {
        qInfo() << "Broken start";
        }
    }else {
    qInfo() << "Broken connection";
    }
    return a.exec();
    */
}
