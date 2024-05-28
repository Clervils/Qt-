#include "ratingbutton.h"
#include "rating.h"
#include <QWidget>

Ratingbutton::Ratingbutton(QObject *parent) : QObject(parent) {}
void Ratingbutton::showRating()
{
    RatingWidget *ratingwidget = new RatingWidget();
    ratingwidget->setAttribute(Qt::WA_DeleteOnClose);
    ratingwidget->setWindowTitle("评分");
    ratingwidget->setStyleSheet("background-color: white;");
    ratingwidget->resize(100, 50);
    ratingwidget->show();
}
