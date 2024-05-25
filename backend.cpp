// backend.cpp
#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{

}

QString Backend::getRestaurantInfo(int index) const
{
    // 在实际项目中，你可以在这里处理从后端服务器获取餐馆信息的逻辑
    // 这里只是一个简单的示例，返回固定的餐馆信息字符串
    if (index == 0) {
        return "餐馆A：评分4.5，距离500m";
    } else if (index == 1) {
        return "餐馆B：评分4.2，距离700m";
    }
    else return "no";
    // 添加更多逻辑处理更多餐馆信息
}
