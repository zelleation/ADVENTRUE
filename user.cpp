#include "user.h"

User::User(int levelIndex)
{
    qDebug()<<"User::User()";
    //this->setAttribute(Qt::WA_DeleteOnClose);
    user_timer = new QTimer(this->parent());
    user_behit = new QTimer(this->parent());
    levelmap = new MapData(this);
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 24; j++)
        {
            this->currmap[i][j] = levelmap->m_map[levelIndex][i][j];
        }
    }
    this->setPixmap(pix_user);
    this->setFixedSize(32,32);
    curr = 1;
    endframe = 11;
    user_timer->start(50);
    connect(this->user_timer,&QTimer::timeout,this,&User::userFall);
    connect(this->user_timer,&QTimer::timeout,this,&User::userbehit);
    connect(this->user_behit,&QTimer::timeout,this,&User::changeBlood);
    connect(this->user_timer,&QTimer::timeout,this,&User::winGame);
}
void User::setUserPixLoad()
{
    qDebug()<<"void User::setUserPixLoad()";
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
    qDebug()<<"void User::userMove()";
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
    qDebug()<<"void User::userFall()";
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

void User::userbehit()
{
    qDebug()<<"void User::userbehit()";
    if(blood <= 0 || this->x() > 1184 || this->y() > 608)
    {
        blood = 0;
        qDebug()<<"user died";
        emit this->died();
    }
    if(currmap[(this->y()+30)/48][(this->x()+16)/48] == Trap1 )
    {
        if((this->y()+30)%48 > 40)
        {
            behit = true;
            qDebug()<<"Trap1"<< currmap[(this->y()+30)/48][(this->x()+30)/48];
        }
    }
    else
    {
        behit = false;
    }
    if(currmap[(this->y()+20)/48][(this->x()+20)/48] == Trap2 || currmap[(this->y()+20)/48][(this->x()+12)/48] == Trap2 || currmap[(this->y()+12)/48][(this->x()+20)/48] == Trap2 || currmap[(this->y()+12)/48][(this->x()+12)/48] == Trap2 )
    {
        behit = true;
        qDebug()<<"Trap2";
        qDebug()<<currmap[this->y()][this->x()];
    }


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

}
void User::changeBlood()
{
    qDebug()<<"void User::changeBlood()";
    blood--;
    changeblood = true;
    endframe = 7;
    this->curr = 1;
}
void User::winGame()
{
    qDebug()<<"void User::winGame()";
    if(currmap[(this->y()+31)/48][(this->x()+32)/48] == CheckPoint || this->currcheckpoint > 0)
    {
        qDebug()<<"start win animation"<<currcheckpoint;
        currcheckpoint++;
        checkpointpath = QString(":/checkpoint/rsc/Items/Checkpoints/Checkpoint/checkpoint%1.png").arg(currcheckpoint);
    }
    if(this->currcheckpoint >= 26)
    {
        qDebug()<<"win";
        emit this->win();
    }
}
