// ratingbutton.cpp

#include "ratingbutton.h"
#include <QDebug>

Ratingbutton::Ratingbutton(QObject *parent) : QObject(parent), ratingnum(0) {}

void Ratingbutton::showRating(const QString &name)
{
    locname = name;
    RatingWidget *ratingwidget = new RatingWidget(name);
    ratingwidget->setAttribute(Qt::WA_DeleteOnClose);
    ratingwidget->setWindowTitle("评分");
    ratingwidget->setStyleSheet("background-color: white;");
    ratingwidget->resize(300, 150);
    ratingwidget->show();

    connect(ratingwidget, &RatingWidget::ratingChanged, this, &Ratingbutton::handleRatingChanged);
    connect(ratingwidget, &RatingWidget::ratingClosed, this, &Ratingbutton::handleRatingClosed); // 连接信号到槽
}

void Ratingbutton::handleRatingChanged(int rating)
{
    ratingnum = rating;
    qDebug() << "Rating updated to:" << ratingnum;
}

void Ratingbutton::handleRatingClosed(int rating, const QString &name)
{
    ratingnum = rating;
    emit ratingUpdated(rating, name); // 发射信号
    qDebug() << "Rating closed with rating:" << ratingnum << " for location:" << name;
}
