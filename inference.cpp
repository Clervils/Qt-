//inference.cpp

#include "inference.h"
#include "indexes.h"
#include <QWidget>

Inference::Inference(QObject *parent) : QObject(parent) {}

void Inference::showInference() {

    Indexes *widget = new Indexes();
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setWindowTitle("索引");
    widget->resize(500, 400);
    widget->show();
}
