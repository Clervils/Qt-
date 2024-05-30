// LocationManager.cpp

#include "locationmanager.h"
#include<cmath>

const double EARTH_RADIUS_KM = 6371.0;

// 将角度转换为弧度
inline double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// 计算两点间的 Haversine 距离
double haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = degreesToRadians(lat2 - lat1);
    double dLon = degreesToRadians(lon2 - lon1);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(degreesToRadians(lat1)) * cos(degreesToRadians(lat2)) *
                   sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}

LocationManager::LocationManager(QObject *parent) : QObject(parent)
{
    // 初始化地点信息
    addLocation("Point A", 39.9917, 116.3055, "This is Point A", "Restaurant", 4, 1);
    addLocation("Point B", 39.995, 116.31, "This is Point B", "Cafe", 5, 2);
    addLocation("Point C", 39.997862, 116.320524, "hahha", "ha", 5, 1);
    addLocation("子固路拌粉 中关村五号店",39.988742,116.31992,"中关村米粉米线人气榜第三名","米粉面馆",5,1);
    addLocation("云佳瑶云南过桥米线",39.982785,116.317141,"中关村米粉米线人气榜第一名","米粉面馆",4.7,1);
    addLocation("花小小新疆炒米粉",39.997892,116.330636,"中关村米粉米线人气榜第五名","米粉面馆",4.8,1);
    addLocation("和府捞面",39.984361,116.322492,"本人爱吃","米粉面馆",4.7,1);
    addLocation("遇见小面",39.984098,116.321836,"不在重庆，遇见小面~","米粉面馆",4.9,1);
    addLocation("吉野家",39.988928,116.313634,"点评高分店铺","快餐",4.5,1);
    addLocation("麦当劳",39.98864,116.320018,"点评高分店铺","快餐",4.6,1);
    addLocation("肯德基",39.987907,116.320633,"疯狂星期四 肯教","快餐",4.8,1);
    addLocation("德克士",39.992251,116.31704,"北京大学店","快餐",4.7,1);
    addLocation("华莱士",39.991972,116.318333,"北京大学店","快餐",4.6,1);
    addLocation("喜茶",39.984402,116.322092,"新中关 · 飞檐店","奶茶咖啡",4.8,1);
    addLocation("沪上阿姨鲜果茶",39.9921,116.323136,"评分很高","奶茶咖啡",4.9,1);
    addLocation("霸王茶姬",39.984355,116.32229,"中关村奶茶榜第二名","奶茶咖啡",4.9,1);
    addLocation("茶百道",39.98958,116.323669,"中关村奶茶热销榜第五名","奶茶咖啡",4.9,1);
    addLocation("瑞幸咖啡",39.990546,116.319749,"9.9","奶茶咖啡",4.0,1);
    addLocation("太太好粥",39.989946,116.334342,"海淀区粥店热销榜第三名","包子粥店",4.8,1);
    addLocation("嘉和一品粥",39.997862,116.330524,"五道口粥店人气榜第三名","包子粥店",4.8,1);
    addLocation("一品生煎",39.992457,116.323122,"海淀区包子生煎人气榜第二名","包子粥店",4.8,1);
    addLocation("曼玲粥店",39.983065,116.324597,"暂时没有哦","包子粥店",4.9,1);
    addLocation("神仙粥方潮汕砂锅粥",39.992045,116.316963,"中关村粤菜好评榜第三名","包子粥店",4.3,1);
    addLocation("小吊梨汤",39.99044,116.33321,"中关村北京菜打卡人气榜第一名","地方菜系",4.7,1);
    addLocation("粤小年·顺德菜",39.988634,116.319762,"中关村粤菜好评榜第一名","地方菜系",4.6,1);
    addLocation("锦府盐帮·李宅",39.985264,116.320885,"海淀区川菜环境榜第一名","地方菜系",4.8,1);
    addLocation("汇贤府·李氏鲁菜",39.976791,116.321839,"暂时没有哦","地方菜系",4.3,1);
    addLocation("港丽餐厅",39.98525,116.320653,"海淀区粤菜热门榜 第五名","地方菜系",4.2,1);
    addLocation("海底捞火锅",39.979867,116.300833,"苏州桥火锅排行榜 第一名","火锅烧烤",4.7,1);
    addLocation("呷哺呷哺",39.984255,116.322646,"暂时没有哦","火锅烧烤",4.1,1);
    addLocation("火炉火自助餐",39.984307,116.321328,"中关村自助餐好评榜第二名","火锅烧烤",4.0,1);
    addLocation("翅客烧烤",39.991883,116.316974,"暂时没有哦","火锅烧烤",3.9,1);
    addLocation("巴奴毛肚火锅",39.9842,116.322371,"中关村火锅打卡人气榜第四名","火锅烧烤",4.6,1);
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
    location["towest"]=haversineDistance(latitude, longitude, 39.99265519209038, 116.29849828684394);
    location["toeast"]=haversineDistance(latitude, longitude, 39.99077617354559, 116.30950388042686);
    location["tosouth"]=haversineDistance(latitude, longitude, 39.98516361992511, 116.30556125566841);
    location["tosoutheast"]=haversineDistance(latitude, longitude, 39.98880918384113, 116.30556125566841);
    location["tosouthwest"]=haversineDistance(latitude, longitude, 39.98646328742977, 116.29941325333175);
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
            double currentRating = location["rating"].toDouble();
            int numOfRatings = location["num_of_rating"].toInt();

            // 计算新的评分
            double newTotalRating = currentRating * numOfRatings + rating;
            int newNumOfRatings = numOfRatings + 1;
            double newAverageRating = newTotalRating / newNumOfRatings;

            // 保留一位小数
            newAverageRating = round(newAverageRating * 10) / 10.0;

            // 更新位置的评分和评分次数
            location["rating"] = newAverageRating;
            location["num_of_rating"] = newNumOfRatings;

            qDebug() << "更新" << name << "的评分为" << newAverageRating;
            break;
        }
    }
}
QStringList LocationManager::getLocationsByCategory(const QString &category) const
{
    QStringList locationNames;
    for (const auto &location : m_locations) {
        if (location["category"].toString() == category) {
            locationNames.append(location["name"].toString());
        }
    }
    return locationNames;
}

