#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWidget>
#include <QWindow>
#include <QQuickWindow>
#include "inference.h"
#include "locationmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 创建 LocationManager 实例
    LocationManager locationManager;
    // 创建Inference实例
    Inference myInference;

    // 注册 LocationManager、 Inference类为 QML 类型
    qmlRegisterSingletonInstance("com.example", 1, 0, "LocationManager", &locationManager);
    qmlRegisterSingletonInstance("inference.example", 1, 0, "Inference", &myInference);

    // 加载主 QML 文件
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("locationManager", &locationManager);
    engine.rootContext()->setContextProperty("myInference", &myInference);
    engine.load(QUrl(QStringLiteral("qrc:/MainWindow.qml")));

    return app.exec();
}
