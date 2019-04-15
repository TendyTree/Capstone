#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "networkthread.h"
#include <QDebug>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    qInfo() << "hello";
    networkThread _network;
    if(_network.begin()){
        _network.initstart();

    }

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Network",&_network);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
