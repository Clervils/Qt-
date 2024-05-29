//rating.h

#ifndef RATINGWIDGET_H
#define RATINGWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QEvent>

class RatingWidget : public QWidget
{
    Q_OBJECT
public:
    int currentRating;
    QString locname;
    explicit RatingWidget(QString name = "", QWidget *parent = nullptr);

signals:
    void ratingChanged(int rating);
    void ratingClosed(int rating, const QString &name);

protected:
    void closeEvent(QCloseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QHBoxLayout *layout;
    QList<QLabel*> starLabels;


    void updateRating(int rating);
};

#endif // RATINGWIDGET_H
