#ifndef FRUIT_H
#define FRUIT_H

#include <QLabel>
#include "user.h"
#include <QPixmap>

class Fruits : public QLabel
{
    Q_OBJECT
public:
    //explicit Fruits(QObject *parent = nullptr);
    Fruits();
    void getFruit();
    void fruitAnimation();

    User * u;
    QTimer * fruTimer;
    QTimer * animationTimer;
    QString str;
    QPixmap pix;
signals:
    void getScore();
};

#endif // FRUIT_H
