#include "bullet.h"

Bullet::Bullet(int x,int y, bool face)
{
    this->move(x,y);
    this->setFixedSize(16,16);
    this->mx = this->x()+8;
    this->my = this->y()+8;
    this->faceright = face;
    QPixmap pix;
    pix.load(":/user/rsc/User/UserAttack.png");
    this->setPixmap(pix);
    this->show();
}
