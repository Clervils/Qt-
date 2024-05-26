//inference.h

#ifndef INFERENCE_H
#define INFERENCE_H

#include <QObject>

class Inference : public QObject {
    Q_OBJECT
public:
    explicit Inference(QObject *parent = nullptr);
    Q_INVOKABLE void showInference();

};


#endif // INFERENCE_H
