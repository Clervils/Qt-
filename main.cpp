// main.cpp

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "LocationManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 创建 LocationManager 实例
    LocationManager locationManager;

    // 注册 LocationManager 类为 QML 类型
    qmlRegisterSingletonInstance("com.example", 1, 0, "LocationManager", &locationManager);

    // 加载主 QML 文件
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("locationManager", &locationManager);
    engine.load(QUrl(QStringLiteral("qrc:/MainWindow.qml")));

    return app.exec();
}
