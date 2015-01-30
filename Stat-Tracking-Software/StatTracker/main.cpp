#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>
#include <feardata.h>
#include <feardatanode.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FearData data;

    // Register the FearDataNode class (version 1.0) with QML
    qmlRegisterType<FearData>("DataStorage", 1, 0, "FearData");
    qmlRegisterType<FearDataNode>("DataStorage", 1, 0, "FearDataNode");

    // This engine is what runs our QML code
    QQmlApplicationEngine engine;

    // Give QML access to the "data" variable
    engine.rootContext()->setContextProperty("TestData", &data);

    // Load up the user interface
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
