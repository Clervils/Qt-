// LocationManager.h

#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include <QObject>
#include <QVariant>

class LocationManager : public QObject
{
    Q_OBJECT
public:
    explicit LocationManager(QObject *parent = nullptr);

    // 添加地点
    Q_INVOKABLE void addLocation(const QString &name, qreal latitude, qreal longitude, const QString &description, const QString &category, int rating, int num_of_rating);

    // 获取所有地点信息
    Q_INVOKABLE QVariantList getAllLocations() const;

    // 根据名称获取地点信息
    Q_INVOKABLE QVariantMap getLocationByName(const QString &name) const;

public slots:
    // 更新地点评分
    void updateLocationRating(int rating, const QString &name);

signals:
    // 发射地点被点击信号
    void locationClicked(const QVariantMap &location);

private:
    QList<QVariantMap> m_locations; // 地点信息列表
};

#endif // LOCATIONMANAGER_H
