// indexes.cpp

#include "indexes.h"
#include <QDebug>

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

    QStringList category1ScoreRank = {"A", "B", "C", "D", "E"};
    QStringList category2ScoreRank = {"BB", "CC", "AA", "DD", "EE"};
    QStringList category3ScoreRank = {"AAA", "CCC", "DDD", "EEE", "FFF"};
    QStringList category4ScoreRank = {"AAA", "CCC", "DDD", "EEE", "FFF"};
    QStringList category5ScoreRank = {"AAA", "CCC", "DDD", "EEE", "FFF"};
    QStringList category6ScoreRank = {"AAA", "CCC", "DDD", "EEE", "FFF"};
    rankData["按分数排序"]["奶茶咖啡"] = category1ScoreRank;
    rankData["按分数排序"]["快餐"] = category2ScoreRank;
    rankData["按分数排序"]["包子粥店"] = category3ScoreRank;
    rankData["按分数排序"]["米粉面馆"] = category4ScoreRank;
    rankData["按分数排序"]["地方菜系"] = category5ScoreRank;
    rankData["按分数排序"]["火锅烧烤"] = category6ScoreRank;

    QStringList category11DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category12DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category13DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category14DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category15DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category16DistanceRank = {"A", "C", "B", "D", "E"};
    rankData["按到东门距离排序"]["奶茶咖啡"] = category11DistanceRank;
    rankData["按到东门距离排序"]["快餐"] = category12DistanceRank;
    rankData["按到东门距离排序"]["包子粥店"] = category13DistanceRank;
    rankData["按到东门距离排序"]["米粉面馆"] = category14DistanceRank;
    rankData["按到东门距离排序"]["地方菜系"] = category15DistanceRank;
    rankData["按到东门距离排序"]["火锅烧烤"] = category16DistanceRank;

    QStringList category21DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category22DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category23DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category24DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category25DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category26DistanceRank = {"A", "C", "B", "D", "E"};
    rankData["按到西门距离排序"]["奶茶咖啡"] = category21DistanceRank;
    rankData["按到西门距离排序"]["快餐"] = category22DistanceRank;
    rankData["按到西门距离排序"]["包子粥店"] = category23DistanceRank;
    rankData["按到西门距离排序"]["米粉面馆"] = category24DistanceRank;
    rankData["按到西门距离排序"]["地方菜系"] = category25DistanceRank;
    rankData["按到西门距离排序"]["火锅烧烤"] = category26DistanceRank;

    QStringList category31DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category32DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category33DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category34DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category35DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category36DistanceRank = {"A", "C", "B", "D", "E"};
    rankData["按到南门距离排序"]["奶茶咖啡"] = category31DistanceRank;
    rankData["按到南门距离排序"]["快餐"] = category32DistanceRank;
    rankData["按到南门距离排序"]["包子粥店"] = category33DistanceRank;
    rankData["按到南门距离排序"]["米粉面馆"] = category34DistanceRank;
    rankData["按到南门距离排序"]["地方菜系"] = category35DistanceRank;
    rankData["按到南门距离排序"]["火锅烧烤"] = category36DistanceRank;

    QStringList category41DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category42DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category43DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category44DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category45DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category46DistanceRank = {"A", "C", "B", "D", "E"};
    rankData["按到东南门距离排序"]["奶茶咖啡"] = category41DistanceRank;
    rankData["按到东南门距离排序"]["快餐"] = category42DistanceRank;
    rankData["按到东南门距离排序"]["包子粥店"] = category43DistanceRank;
    rankData["按到东南门距离排序"]["米粉面馆"] = category44DistanceRank;
    rankData["按到东南门距离排序"]["地方菜系"] = category45DistanceRank;
    rankData["按到东南门距离排序"]["火锅烧烤"] = category46DistanceRank;

    QStringList category51DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category52DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category53DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category54DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category55DistanceRank = {"A", "C", "B", "D", "E"};
    QStringList category56DistanceRank = {"A", "C", "B", "D", "E"};
    rankData["按到西南门距离排序"]["奶茶咖啡"] = category51DistanceRank;
    rankData["按到西南门距离排序"]["快餐"] = category52DistanceRank;
    rankData["按到西南门距离排序"]["包子粥店"] = category53DistanceRank;
    rankData["按到西南门距离排序"]["米粉面馆"] = category54DistanceRank;
    rankData["按到西南门距离排序"]["地方菜系"] = category55DistanceRank;
    rankData["按到西南门距离排序"]["火锅烧烤"] = category56DistanceRank;


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
