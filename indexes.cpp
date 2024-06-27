// indexes.cpp

#include "indexes.h"
#include <QDebug>
#include<algorithm>
#include <QPalette>
#include<QPushButton>
#include<QMessageBox>
#include<QRandomGenerator>
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
    resize(600, 500); // 调整窗口大小

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20); // 设置外边距

    // 添加选择排行依据的下拉框
    comboBoxRank = new QComboBox(this);
    comboBoxRank->addItem("按分数排序");
    comboBoxRank->addItem("按到东门距离排序");
    comboBoxRank->addItem("按到西门距离排序");
    comboBoxRank->addItem("按到南门距离排序");
    comboBoxRank->addItem("按到东南门距离排序");
    comboBoxRank->addItem("按到西南门距离排序");
    mainLayout->addWidget(comboBoxRank);

    // 添加选择类别的下拉框
    comboBoxCategory = new QComboBox(this);
    comboBoxCategory->addItem("奶茶咖啡");
    comboBoxCategory->addItem("快餐");
    comboBoxCategory->addItem("包子粥店");
    comboBoxCategory->addItem("米粉面馆");
    comboBoxCategory->addItem("地方菜系");
    comboBoxCategory->addItem("火锅烧烤");
    mainLayout->addWidget(comboBoxCategory);

    // 添加排行榜列表
    rankList = new QListWidget(this);
    rankList->setStyleSheet("QListWidget { background-color: #f0f0f0; border: 1px solid #ccc; }"
                            "QListWidget::item { padding: 10px; }"); // 设置样式
    mainLayout->addWidget(rankList);

    // 初始化数据
    initializeData();

    // 连接信号槽，根据下拉框选择的不同，更新排行榜显示
    connect(comboBoxRank, SIGNAL(currentIndexChanged(int)), this, SLOT(updateRank()));
    connect(comboBoxCategory, SIGNAL(currentIndexChanged(int)), this, SLOT(updateRank()));

    // 设置字体
    QFont font("Arial", 12); // 使用Arial字体，大小为12号
    comboBoxRank->setFont(font);
    comboBoxCategory->setFont(font);
    rankList->setFont(font);

    // 设置颜色
    QPalette palette;
    palette.setColor(QPalette::Text, QColor("#333333")); // 设置文本颜色
    setPalette(palette);

    QPushButton *randomButton = new QPushButton("不知道今天吃什么？", this);
    randomButton->setFont(QFont("Arial", 14));
    randomButton->setStyleSheet("QPushButton { padding: 10px; background-color: #8BC34A; color: white; border: none; border-radius: 5px; }"
                                "QPushButton:hover { background-color: #7CB342; }"
                                "QPushButton:pressed { background-color: #689F38; }");
    mainLayout->addWidget(randomButton);

    // 连接按钮点击事件到槽函数
    connect(randomButton, SIGNAL(clicked()), this, SLOT(chooseCategoryAndRandom()));


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

    qDebug() << "排名类型：" << rankType << "，类别：" << category; // Debug output

    rankList->clear();
    QStringList ranks = rankData[rankType][category];
    qDebug() << "排名数量：" << ranks.size(); // Debug output

    // Font setup
    QFont boldFont;
    boldFont.setBold(true);

    QFont regularFont;
    regularFont.setBold(false);

    // Adjust font sizes
    boldFont.setPointSize(14); // Larger font size for top three
    regularFont.setPointSize(12); // Regular font size for the rest

    // Display rankings
    for (int i = 0; i < ranks.size(); ++i) {
        QString rankItem = QString::number(i + 1) + "、" + ranks.at(i);

        // Create a QListWidgetItem
        QListWidgetItem *item = new QListWidgetItem(rankItem);

        // Set font based on rank position
        if (i < 3) {
            item->setFont(boldFont); // Bold and larger font for top three
        } else {
            item->setFont(regularFont); // Regular font for others
        }

        rankList->addItem(item);
    }
}
// 在 Indexes 类中添加新的槽函数 chooseCategoryAndRandom()
void Indexes::chooseCategoryAndRandom() {
    // 创建选择类别的对话框
    QDialog dialog(this);
    dialog.setWindowTitle("选择餐馆类别");
    dialog.setStyleSheet("background-color: #ffffff;"); // 设置对话框背景色
    dialog.setMinimumSize(300, 150); // 设置对话框的最小尺寸

    QVBoxLayout layout(&dialog);

    // 添加类别选择下拉框
    QComboBox comboBox(&dialog);
    comboBox.addItem("奶茶咖啡");
    comboBox.addItem("快餐");
    comboBox.addItem("包子粥店");
    comboBox.addItem("米粉面馆");
    comboBox.addItem("地方菜系");
    comboBox.addItem("火锅烧烤");
    comboBox.setFont(QFont("Arial", 14, QFont::Bold));
    comboBox.setStyleSheet("QComboBox { padding: 8px; }"); // 调整下拉框的内边距
    layout.addWidget(&comboBox);

    // 添加确认按钮
    QPushButton confirmButton("确认", &dialog);
    confirmButton.setFont(QFont("Arial", 12));
    confirmButton.setStyleSheet("QPushButton { padding: 10px; background-color: #4CAF50; color: white; border: none; }"
                                "QPushButton:hover { background-color: #45a049; }"); // 设置按钮的样式
    layout.addWidget(&confirmButton);

    // 连接确认按钮的点击事件
    connect(&confirmButton, &QPushButton::clicked, [&]() {
        QString selectedCategory = comboBox.currentText();
        dialog.close();

        // 获取选定类别的餐馆列表
        QStringList restaurantList = rankData["按分数排序"][selectedCategory];

        // 随机选择一个餐馆
        if (!restaurantList.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(restaurantList.size());
            QString randomRestaurant = restaurantList[randomIndex];

            // 随机选择餐馆后的消息框
            QMessageBox msgBox;
            msgBox.setWindowTitle("随机选择的餐馆");
            msgBox.setText("今天吃：" + randomRestaurant);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setStyleSheet("QMessageBox { background-color: #ffffff; border: 2px solid #aaa; }"
                                 "QMessageBox QLabel { color: #333; font-size: 14px; }"
                                 "QPushButton { background-color: #4CAF50; color: white; border: none; padding: 10px; }"
                                 "QPushButton:hover { background-color: #45a049; }");

            // 添加确认按钮
            QPushButton *okButton = msgBox.addButton("确认", QMessageBox::AcceptRole);
            okButton->setFont(QFont("Arial", 12));
            okButton->setStyleSheet("QPushButton { padding: 10px; }");

            // 添加显示详细信息按钮
            QPushButton *detailsButton = msgBox.addButton("显示详细信息", QMessageBox::ActionRole);
            detailsButton->setFont(QFont("Arial", 12));
            detailsButton->setStyleSheet("QPushButton { padding: 10px; }");
            // 连接显示详细信息按钮的点击事件
            connect(detailsButton, &QPushButton::clicked, [=]() {
                showDetailedInfo(randomRestaurant);
            });

            msgBox.exec();
        } else {
            QMessageBox::warning(this, "错误", "该类别下没有餐馆数据！");
        }
    });

    // 设置布局的外边距
    layout.setContentsMargins(20, 20, 20, 20);

    // 显示对话框
    dialog.exec();
}
void Indexes::showDetailedInfo(const QString &restaurantName) {
    LocationManager l;
    QMap<QString, QVariant> locationDetails = l.getLocationByName(restaurantName);

    QString description = locationDetails["description"].toString();
    QString category = locationDetails["category"].toString();
    QString rating = locationDetails["rating"].toString();
    QString nearestGate = findNearestGate(locationDetails);

    QString message = QString("详细信息：\n\n"
                              "名称：%1\n"
                              "描述：%2\n"
                              "类别：%3\n"
                              "评分：%4\n"
                              "离最近的门：%5")
                          .arg(restaurantName)
                          .arg(description)
                          .arg(category)
                          .arg(rating)
                          .arg(nearestGate);

    QMessageBox msgBox;
    msgBox.setWindowTitle("详细信息");
    msgBox.setText(message);
    msgBox.setStyleSheet("QLabel { font-weight: bold; }");  // 设置加粗

    msgBox.exec();
}

QString Indexes::findNearestGate(const QMap<QString, QVariant> &locationDetails) {
    double toEast = locationDetails["toeast"].toDouble();
    double toWest = locationDetails["towest"].toDouble();
    double toSouth = locationDetails["tosouth"].toDouble();
    double toSoutheast = locationDetails["tosoutheast"].toDouble();
    double toSouthwest = locationDetails["tosouthwest"].toDouble();

    QString nearestGate;
    double minDistance = std::min({toEast, toWest, toSouth, toSoutheast, toSouthwest});

    if (minDistance == toEast) {
        nearestGate = "东门";
    } else if (minDistance == toWest) {
        nearestGate = "西门";
    } else if (minDistance == toSouth) {
        nearestGate = "南门";
    } else if (minDistance == toSoutheast) {
        nearestGate = "东南门";
    } else if (minDistance == toSouthwest) {
        nearestGate = "西南门";
    }

    return nearestGate;
}








