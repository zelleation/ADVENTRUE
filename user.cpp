#include "user.h"

User::User()
{
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
    qDebug()<<jump<<'-'<<fall;
    if(height>108)
    {
        jump = false;
        fall = true;
    }
    if(jump && (currmap[this->y()/48 - 12][(this->x()+16)/48] != Wall))
    {
        this->move(this->x(),this->y()-12);
        height += 12;
        qDebug()<<"userjump";
    }
    if(fall && height>0)
    {
        if(currmap[(this->y()+32+12)/48][(this->x()+16)/48] != Wall)
            this->move(this->x(),this->y()+12);
        else
        {
            fall = false;
            this->move(this->x(),this->y()+12);
            height = 0;
        }
        //qDebug()<<"usefall";
    }
    if(runleft && (currmap[this->y()/48][(this->x()-4)/48] != Wall))
    {
        this->move(this->x()-4,this->y());
        //qDebug()<<"userrunleft";
    }
    if(runright && (currmap[this->y()/48][(this->x()+4+32)/48] != Wall))
    {
        this->move(this->x()+4,this->y());
        //qDebug()<<"userrunright";
    }

}
