/*
 * Andrew Brashich
 * 2019 Capstone project
 * Create a modern dashboard using Qt
 *
*/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "networkthread.h"
#include <QDebug>
#include <QQmlContext>
int main(int argc, char *argv[])
{

    networkThread _network;

    //connect to the Elm 327 and start a seprate thread for tcp work
    if(_network.begin()){
        _network.initstart();
    }

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //Set the context property of the Networking so values can be called in qml

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Network",&_network);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
