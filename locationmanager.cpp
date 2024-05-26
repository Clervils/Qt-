// LocationManager.cpp

#include "LocationManager.h"


LocationManager::LocationManager(QObject *parent) : QObject(parent)
{
    // 初始化地点信息
    addLocation("Point A", 39.9917, 116.3055, "This is Point A", "Restaurant", 4);
    addLocation("Point B", 39.995, 116.31, "This is Point B", "Cafe", 5);
    // 添加更多地点信息
}
//餐馆名，经纬度，餐馆描述，类别，评分
void LocationManager::addLocation(const QString &name, qreal latitude, qreal longitude, const QString &description, const QString &category, int rating)
{
    QVariantMap location;
    location["name"] = name;
    location["latitude"] = latitude;
    location["longitude"] = longitude;
    location["description"] = description;
    location["category"] = category;
    location["rating"] = rating;
    m_locations.append(location);
}

QVariantList LocationManager::getAllLocations() const
{
    QVariantList list;
    for (const auto &location : m_locations) {
        list.append(location);
    }
    return list;
}

QVariantMap LocationManager::getLocationByName(const QString &name) const
{
    for (const auto &location : m_locations) {
        if (location["name"].toString() == name) {
            qDebug() << "Found location:" << location;
            return location;
        }
    }

    qDebug() << "Location not found for name:" << name;
    return QVariantMap();
}

