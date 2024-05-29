// ratingbutton.h

#ifndef RATINGBUTTON_H
#define RATINGBUTTON_H

#include <QObject>
#include <QVariantMap>
#include "rating.h"

class Ratingbutton : public QObject {
    Q_OBJECT
public:
    int ratingnum;
    explicit Ratingbutton(QObject *parent = nullptr);
    Q_INVOKABLE void showRating(const QString &name);

signals:
    void ratingUpdated(int rating, const QString &name); // 发射位置名称

public slots:
    void handleRatingChanged(int rating);
    void handleRatingClosed(int rating, const QString &name); // 处理关闭事件

private:
    QString locname; // 存储位置名称
};

#endif // RATINGBUTTON_H
