#include "user.h"

User::User()
{
    user_timer = new QTimer(this->parent());
    user_behit = new QTimer(this->parent());
    this->setPixmap(pix_user);
    this->setFixedSize(32,32);
    curr = 1;
    endframe = 11;
    user_timer->start(50);
    connect(this->user_timer,&QTimer::timeout,this,&User::userFall);
    connect(this->user_timer,&QTimer::timeout,this,&User::userbehit);
    connect(this->user_behit,&QTimer::timeout,this,&User::changeBlood);
}
void User::setUserPixLoad()
{
    if(changeblood)
    {
        if(faceright)
            curr_str = QString(":/user/rsc/User/Hit%1.png").arg(curr);
        else
            curr_str = QString(":/user/rsc/User/HitL%1.png").arg(curr);
        pix_user.load(curr_str);
        if(curr == endframe - 1)
            changeblood = false;
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
    //qDebug()<<jump;
    if(jumptime >= 12)
    {
        jump = false;
        fall = true;
    }
    if(jump)
    {
        jumptime++;
        if((currmap[this->y()/48][(this->x()+31)/48] != Wall)&&(currmap[this->y()/48][(this->x()+1)/48] != Wall))
        {
            this->move(this->x(),this->y()-12);
            qDebug()<<"userjump";
        }
    }
    if(runleft && (currmap[(this->y()+31)/48][(this->x()-4)/48] != Wall))
    {
        this->move(this->x()-4,this->y());
        //qDebug()<<"userrunleft";
    }
    if(runright && (currmap[(this->y()+31)/48][(this->x()+4+32)/48] != Wall))
    {
        this->move(this->x()+4,this->y());
        //qDebug()<<"userrunright";
    }

}
void User::userFall()
{
    if(!jump && currmap[(this->y()+32)/48][(this->x()+31)/48] != Wall&& currmap[(this->y()+32)/48][(this->x()+1)/48] != Wall)
    {
        fall = true;
        this->move(this->x(),this->y() + 12);
    }
    if(fall && (currmap[(this->y()+32)/48][(this->x()+31)/48] == Wall || currmap[(this->y()+32)/48][(this->x()+1)/48] == Wall) && (this->y()+32)%48 == 0)
    {
        fall = false;
        jumptime = 0;
    }
}
void User::userAttack()
{
    if(attack && this->userbullet == nullptr)
    {
        userbullet = new Bullet(this->x(),this->y(),faceright);
    }
    else if(!attack && this->userbullet != nullptr)
    {
        this->userbullet->deleteLater();
        this->userbullet = nullptr;
    }
    else if(attack && this->userbullet != nullptr)
    {
        if(userbullet->faceright)
            userbullet->move(userbullet->x()+16,userbullet->y());
        else
            userbullet->move(userbullet->x()-16,userbullet->y());
    }
    if(this->userbullet != nullptr)
    {
        if(userbullet->x()<0 || userbullet->x()+16>1152)
        {
            attack = false;
            this->userbullet->deleteLater();
            this->userbullet = nullptr;
        }
        else if(currmap[userbullet->mx][userbullet->my] == Monster)
        {
            attack = false;
            this->userbullet->deleteLater();
            this->userbullet = nullptr;
            currmap[userbullet->mx/48][userbullet->my/48] = Nothing;
        }
    }
}
void User::userbehit()
{
    qDebug()<<currmap[(this->y()+31)/48][(this->x()+32)/48]<<"  "<<blood<<"behit"<<behit;
    if(currmap[(this->y()+31)/48][(this->x()+32)/48] == Trap1 || currmap[(this->y()+31)/48][this->x()/48] == Trap1 )
    {
        if((this->y()+31)%48 > 40)
            behit = true;
    }
    else
    {
        behit = false;
    }
    if(currmap[(this->y()+32)/48][(this->x()+32)/48] == Trap2 || currmap[(this->y()+32)/48][this->x()/48] == Trap2 || currmap[this->y()/48][(this->x()+32)/48] == Trap2 || currmap[this->y()/48][this->x()/48] == Trap2 )
        behit = true;
    if(currmap[(this->y()+32)/48][(this->x()+32)/48] == Monster || currmap[(this->y()+32)/48][this->x()/48] == Monster || currmap[this->y()/48][(this->x()+32)/48] == Monster || currmap[this->y()/48][this->x()/48] == Monster )
        behit = true;


    if(behit && !this->user_behit->isActive())
    {
        this->user_behit->start(2000);
        changeBlood();
    }
    if(!behit && this->user_behit->isActive())
    {
        this->user_behit->stop();
        changeblood = false;
    }


    if(blood <= 0)
    {
        emit this->died();
        qDebug()<<"user died";
    }
}
void User::changeBlood()
{
    blood--;
    changeblood = true;
    endframe = 7;
    this->curr = 1;
}
