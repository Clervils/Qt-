// rating.cpp

#include "rating.h"

RatingWidget::RatingWidget(QString name, QWidget *parent) : QWidget(parent)
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
    locname = name;

    currentRating = 0;
}

void RatingWidget::mousePressEvent(QMouseEvent *event)
{
    int starWidth = width() / 5;
    int rating = event->position().x() / starWidth + 1;

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
                starLabels[i]->setPixmap(starPixmap);
            } else {
                QPixmap starPixmap(":/ratingstar.jpg");
                starPixmap = starPixmap.scaled(40, 40, Qt::KeepAspectRatio);
                starLabels[i]->setPixmap(starPixmap);
            }
        }
        emit ratingChanged(currentRating);
    }
}

void RatingWidget::closeEvent(QCloseEvent *event)
{
    emit ratingClosed(currentRating, locname);
    QWidget::closeEvent(event);
}
