#ifndef RATINGBUTTON_H
#define RATINGBUTTON_H

#include <QObject>

class Ratingbutton : public QObject{
    Q_OBJECT
public:
    explicit Ratingbutton(QObject *parent = nullptr);
    Q_INVOKABLE void showRating();
};

#endif // RATINGBUTTON_H

