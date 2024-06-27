//inference.cpp

#include "inference.h"
#include "indexes.h"
#include <QWidget>
#include <QApplication>

Inference::Inference(QObject *parent) : QObject(parent) {}

void Inference::showInference() {

    QApplication::setStyle("fusion"); // 使用Fusion风格

    Indexes *widget = new Indexes();
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setWindowTitle("索引");
    widget->setWindowIcon(QIcon(":/icons/icon.png")); // 设置窗口图标
    widget->resize(600, 500); // 调整窗口大小
    widget->show();
}
