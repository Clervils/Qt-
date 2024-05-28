#include "rating.h"

RatingWidget::RatingWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    for (int i = 0; i < 5; ++i) {
        QLabel *starLabel = new QLabel(this);
        QPixmap starPixmap(":/ratingstar.jpg");
        starPixmap = starPixmap.scaled(40, 40, Qt::KeepAspectRatio);
        starLabel->setPixmap(starPixmap);
        starLabel->setFixedSize(40, 40);
        layout->addWidget(starLabel);
        starLabels.append(starLabel);
    }


    currentRating = 0;


}

void RatingWidget::mousePressEvent(QMouseEvent *event)
{
    int starWidth = width() / 5;
    int rating = event->position().x() / starWidth + 1; // 计算当前鼠标点击位置所代表的评分

    updateRating(rating);
}

void RatingWidget::updateRating(int rating)
{
    if (rating != currentRating) {
        currentRating = rating;

        for (int i = 0; i < starLabels.size(); ++i) {
            if (i < rating) {
                QPixmap starPixmap(":/ratingstar2.jpg");
                starPixmap = starPixmap.scaled(40, 40, Qt::KeepAspectRatio);
                starLabels[i]->setPixmap(starPixmap); // 设置已选中状态的星星
            } else {
                QPixmap starPixmap(":/ratingstar.jpg");
                starPixmap = starPixmap.scaled(40, 40, Qt::KeepAspectRatio);
                starLabels[i]->setPixmap(starPixmap);
                starLabels[i]->setPixmap(QPixmap(starPixmap)); // 设置未选中状态的星星
            }
        }

        //补充与数据库的交互
    }
}
