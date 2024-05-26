// indexes.h

#ifndef INDEXES_H
#define INDEXES_H

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QMap>
#include <QStringList>

class Indexes : public QWidget {
    Q_OBJECT
public:
    explicit Indexes(QWidget *parent = nullptr);

public slots:
    void updateRank();

private:
    void initializeData();

    QComboBox *comboBoxRank;
    QComboBox *comboBoxCategory;
    QListWidget *rankList;
    QMap<QString, QMap<QString, QStringList>> rankData;
};

#endif // INDEXES_H
