// indexes.cpp

#include "indexes.h"
#include <QDebug>
#include<algorithm>
#include<iostream>
#include "locationmanager.h"
bool comparebywest(const QString &a, const QString &b) {
    LocationManager l;
    return l.getLocationByName(a)["towest"].toDouble()<l.getLocationByName(b)["towest"].toDouble();
    //return a < b;  // 按字母顺序排序
}
bool comparebyeast(const QString &a, const QString &b) {
    LocationManager l;
    return l.getLocationByName(a)["toeast"].toDouble()<l.getLocationByName(b)["toeast"].toDouble();
    //return a < b;  // 按字母顺序排序
}
bool comparebysouth(const QString &a, const QString &b) {
    LocationManager l;
    return l.getLocationByName(a)["tosouth"].toDouble()<l.getLocationByName(b)["tosouth"].toDouble();
    //return a < b;  // 按字母顺序排序
}
bool comparebysouthwest(const QString &a, const QString &b) {
    LocationManager l;
    return l.getLocationByName(a)["tosouthwest"].toDouble()<l.getLocationByName(b)["tosouthwest"].toDouble();
    //return a < b;  // 按字母顺序排序
}
bool comparebysoutheast(const QString &a, const QString &b) {
    LocationManager l;
    return l.getLocationByName(a)["tosoutheast"].toDouble()<l.getLocationByName(b)["tosoutheast"].toDouble();
    //return a < b;  // 按字母顺序排序
}
bool comparebyrate(const QString &a, const QString &b) {
    LocationManager l;
    return l.getLocationByName(a)["rating"].toDouble()>l.getLocationByName(b)["rating"].toDouble();
    //return a < b;  // 按字母顺序排序
}
QStringList getSortedData(const QString &category, bool (*compareFunc)(const QString&, const QString&)) {
    LocationManager l;
    QStringList sortedList=l.getLocationsByCategory(category);
    std::sort(sortedList.begin(), sortedList.end(), compareFunc);

    return sortedList;
}
Indexes::Indexes(QWidget *parent) : QWidget(parent) {
    setWindowTitle("排行榜");
    resize(500, 400);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // 添加选择排行依据的下拉框
    comboBoxRank = new QComboBox(this);
    comboBoxRank->addItem("按分数排序");
    comboBoxRank->addItem("按到东门距离排序");
    comboBoxRank->addItem("按到西门距离排序");
    comboBoxRank->addItem("按到南门距离排序");
    comboBoxRank->addItem("按到东南门距离排序");
    comboBoxRank->addItem("按到西南门距离排序");
    layout->addWidget(comboBoxRank);

    // 添加选择类别的下拉框
    comboBoxCategory = new QComboBox(this);
    comboBoxCategory->addItem("奶茶咖啡");
    comboBoxCategory->addItem("快餐");
    comboBoxCategory->addItem("包子粥店");
    comboBoxCategory->addItem("米粉面馆");
    comboBoxCategory->addItem("地方菜系");
    comboBoxCategory->addItem("火锅烧烤");
    layout->addWidget(comboBoxCategory);

    // 添加排行榜列表
    rankList = new QListWidget(this);
    layout->addWidget(rankList);

    // 初始化数据
    initializeData();

    // 连接信号槽，根据下拉框选择的不同，更新排行榜显示
    connect(comboBoxRank, SIGNAL(currentIndexChanged(int)), this, SLOT(updateRank()));
    connect(comboBoxCategory, SIGNAL(currentIndexChanged(int)), this, SLOT(updateRank()));

    // 默认显示
    updateRank();
}

void Indexes::initializeData() {
    // *在此处实现按照分类的分数和距离排名

    rankData["按分数排序"]["奶茶咖啡"] = getSortedData("奶茶咖啡",comparebyrate);
    rankData["按分数排序"]["快餐"] =getSortedData("快餐",comparebyrate);
    rankData["按分数排序"]["包子粥店"] = getSortedData("包子粥店",comparebyrate);
    rankData["按分数排序"]["米粉面馆"] = getSortedData("米粉面馆",comparebyrate);
    rankData["按分数排序"]["地方菜系"] = getSortedData("地方菜系",comparebyrate);
    rankData["按分数排序"]["火锅烧烤"] =getSortedData("火锅烧烤",comparebyrate);

    rankData["按到东门距离排序"]["奶茶咖啡"] = getSortedData("奶茶咖啡",comparebyeast);
    rankData["按到东门距离排序"]["快餐"] = getSortedData("快餐",comparebyeast);
    rankData["按到东门距离排序"]["包子粥店"] = getSortedData("包子粥店",comparebyeast);
    rankData["按到东门距离排序"]["米粉面馆"] = getSortedData("米粉面馆",comparebyeast);
    rankData["按到东门距离排序"]["地方菜系"] = getSortedData("地方菜系",comparebyeast);
    rankData["按到东门距离排序"]["火锅烧烤"] = getSortedData("火锅烧烤",comparebyeast);

    rankData["按到西门距离排序"]["奶茶咖啡"] = getSortedData("奶茶咖啡",comparebywest);
    rankData["按到西门距离排序"]["快餐"] = getSortedData("快餐",comparebywest);
    rankData["按到西门距离排序"]["包子粥店"] = getSortedData("包子粥店",comparebywest);
    rankData["按到西门距离排序"]["米粉面馆"] = getSortedData("米粉面馆",comparebywest);
    rankData["按到西门距离排序"]["地方菜系"] = getSortedData("地方菜系",comparebywest);
    rankData["按到西门距离排序"]["火锅烧烤"] = getSortedData("火锅烧烤",comparebywest);

    rankData["按到南门距离排序"]["奶茶咖啡"] = getSortedData("奶茶咖啡",comparebysouth);
    rankData["按到南门距离排序"]["快餐"] = getSortedData("快餐",comparebysouth);
    rankData["按到南门距离排序"]["包子粥店"] = getSortedData("包子粥店",comparebysouth);
    rankData["按到南门距离排序"]["米粉面馆"] = getSortedData("米粉面馆",comparebysouth);
    rankData["按到南门距离排序"]["地方菜系"] = getSortedData("地方菜系",comparebysouth);
    rankData["按到南门距离排序"]["火锅烧烤"] = getSortedData("火锅烧烤",comparebysouth);

    rankData["按到东南门距离排序"]["奶茶咖啡"] = getSortedData("奶茶咖啡",comparebysoutheast);
    rankData["按到东南门距离排序"]["快餐"] = getSortedData("快餐",comparebysoutheast);
    rankData["按到东南门距离排序"]["包子粥店"] = getSortedData("包子粥店",comparebysoutheast);
    rankData["按到东南门距离排序"]["米粉面馆"] = getSortedData("米粉面馆",comparebysoutheast);
    rankData["按到东南门距离排序"]["地方菜系"] = getSortedData("地方菜系",comparebysoutheast);
    rankData["按到东南门距离排序"]["火锅烧烤"] = getSortedData("火锅烧烤",comparebysoutheast);

    rankData["按到西南门距离排序"]["奶茶咖啡"] = getSortedData("奶茶咖啡",comparebysouthwest);
    rankData["按到西南门距离排序"]["快餐"] = getSortedData("快餐",comparebysouthwest);
    rankData["按到西南门距离排序"]["包子粥店"] = getSortedData("包子粥店",comparebysouthwest);
    rankData["按到西南门距离排序"]["米粉面馆"] = getSortedData("米粉面馆",comparebysouthwest);
    rankData["按到西南门距离排序"]["地方菜系"] = getSortedData("地方菜系",comparebysouthwest);
    rankData["按到西南门距离排序"]["火锅烧烤"] = getSortedData("火锅烧烤",comparebysouthwest);


    // 更多排名数据可以在这里添加
}

void Indexes::updateRank() {
    QString rankType = comboBoxRank->currentText();
    QString category = comboBoxCategory->currentText();

    qDebug() << "排名类型：" << rankType << "，类别：" << category; // 调试输出

    rankList->clear();
    QStringList ranks = rankData[rankType][category];
    qDebug() << "排名数量：" << ranks.size(); // 调试输出
    rankList->addItems(ranks);
}
