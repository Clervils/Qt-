#ifndef RATINGWIDGET_H
#define RATINGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class RatingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RatingWidget(QWidget *parent = nullptr);

signals:
    void ratingChanged(int rating);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QHBoxLayout *layout;
    QList<QLabel*> starLabels;
    int currentRating;

    void updateRating(int rating);
};

#endif // RATINGWIDGET_H
