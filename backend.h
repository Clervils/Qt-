// backend.h
#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

    Q_INVOKABLE QString getRestaurantInfo(int index) const;
    // 添加更多函数来处理后端逻辑

signals:

};

#endif // BACKEND_H
