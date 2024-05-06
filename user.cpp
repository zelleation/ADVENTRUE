#include "user.h"

User::User()
{
    speed = 4;
    blood = 10;
    user_timer = new QTimer;
    this->setPixmap(pix_user);
    this->setFixedSize(32,32);
    curr = 1;
    endframe = 11;
    user_timer->start(50);
}
void User::setUserPixLoad()
{
    if(behit)
    {
        endframe = 7;
        if(faceright)
            curr_str = QString(":/user/rsc/User/Hit%1.png").arg(curr);
        else
            curr_str = QString(":/user/rsc/User/HitL%1.png").arg(curr);
        pix_user.load(curr_str);
    }
    else if(fall)
    {
        endframe = 1;
        if(faceright)
            curr_str = QString(":/user/rsc/User/Fall.png");
        else
            curr_str = QString(":/user/rsc/User/FallL.png");
        pix_user.load(curr_str);
    }
    else if(jump)
    {
        endframe = 1;
        if(faceright)
            curr_str = QString(":/user/rsc/User/Jump.png");
        else
            curr_str = QString(":/user/rsc/User/JumpL.png");
        pix_user.load(curr_str);
    }
    else if(runleft)
    {
        endframe = 12;
        curr_str = QString(":/user/rsc/User/RunL%1.png").arg(curr);
        faceright = false;
        pix_user.load(curr_str);
    }
    else if(runright)
    {
        endframe = 12;
        curr_str = QString(":/user/rsc/User/Run%1.png").arg(curr);
        faceright = true;
        pix_user.load(curr_str);
    }
    else//站着不动
    {
        if(faceright)
        {
            endframe = 11;
            curr_str = QString(":/user/rsc/User/Idle%1.png").arg(curr);
            pix_user.load(curr_str);
        }
        else
        {
            endframe = 11;
            curr_str = QString(":/user/rsc/User/IdleL%1.png").arg(curr);
            pix_user.load(curr_str);
        }
    }
}
void User::userMove()
{
    if(height>128)
    {
        jump = false;
        fall = true;
    }
    if(jump)
    {
        this->move(this->x(),this->y()-12);
        height += 12;
    }
    if(fall)
    {
        this->move(this->x(),this->y()+12);
    }
    if(runleft)
    {
        this->move(this->x()-4,this->y());
    }
    if(runright)
    {
        this->move(this->x()+4,this->y());
    }
}
