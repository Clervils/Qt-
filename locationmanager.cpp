// LocationManager.cpp

#include "locationmanager.h"


LocationManager::LocationManager(QObject *parent) : QObject(parent)
{
    // 初始化地点信息
    addLocation("Point A", 39.9917, 116.3055, "This is Point A", "Restaurant", 4, 1);
    addLocation("Point B", 39.995, 116.31, "This is Point B", "Cafe", 5, 2);
    addLocation("Point C", 39.997862, 116.320524, "hahha", "ha", 5, 1);
    // 添加更多地点信息
}
//餐馆名，经纬度，餐馆描述，类别，评分
void LocationManager::addLocation(const QString &name, qreal latitude, qreal longitude, const QString &description, const QString &category, int rating, int num_of_rating)
{
    QVariantMap location;
    location["name"] = name;
    location["latitude"] = latitude;
    location["longitude"] = longitude;
    location["description"] = description;
    location["category"] = category;
    location["rating"] = rating;
    location["num_of_rating"] = num_of_rating;
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
void LocationManager::updateLocationRating(int rating, const QString &name)
{
    for (auto &location : m_locations) {
        if (location["name"].toString() == name) {
            location["rating"] = ((location["rating"].toInt())*(location["num_of_rating"].toInt()) + rating)/(location["num_of_rating"].toInt() + 1);
            location["num_of_rating"] = location["num_of_rating"].toInt() + 1;
            qDebug() << "更新" << name << "的评分为" << rating;
            break;
        }
    }
}

