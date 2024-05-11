#ifndef BULLET_H
#define BULLET_H

#include <QLabel>

class Bullet :public QLabel
{
    Q_OBJECT
public:
    Bullet(int x,int y, bool face);
    int mx;//中心位置
    int my;
    bool faceright;

signals:
};

#endif // BULLET_H
