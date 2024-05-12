#include "fruit.h"

Fruits::Fruits()
{
    this->setFixedSize(32,32);
    fruTimer = new QTimer(this);
    fruTimer->start(50);
    animationTimer = new QTimer(this);
    animationTimer->start(200);
    str = ":/craft/rsc/Items/fruit1.png";
    pix.load(str);
    this->setPixmap(pix);
    this->show();
    connect(this->fruTimer,&QTimer::timeout,this,&Fruits::getFruit);
    connect(this->animationTimer,&QTimer::timeout,this,&Fruits::fruitAnimation);
}
void Fruits::getFruit()
{
    if(u == nullptr)
        return;
    if(u->x()+16 >= this->x() && u->y()+16 >= this->y() && u->x()+16 <= this->x() + 32 && u->y()+16 <= this->y() +32 )
    {
        this->animationTimer->stop();
        this->fruTimer->stop();
        emit this->getScore();
        this->close();
    }
}
void Fruits::fruitAnimation()
{
    static int curr = 1;
    if(curr % 4 == 0)
        this->move(this->x(),this->y()+2);
    else if(curr % 4 == 1)
        this->move(this->x(),this->y()+2);
    else if(curr % 4 == 2)
        this->move(this->x(),this->y()-2);
    else if(curr % 4 == 3)
        this->move(this->x(),this->y()-2);
    if(curr++ == 4)
    {
        curr = 1;
    }
}
