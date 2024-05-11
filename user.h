#ifndef USER_H
#define USER_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QPoint>
#include "bullet.h"

enum  MapEle
{
    Nothing,        //0
    Wall,           //1
    Box,            //2
    Fruit,          //3
    Monster,        //4
    CheckPoint,     //5
    Float,          //6
    Trap1,          //7
    Trap2,          //8
};

class User: public QLabel
{
    Q_OBJECT
public:
    User();
    void setUserPixLoad();
    void userMove();
    void userFall();
    void userbehit();
    void userDie();
    void userAttack();
    void changeBlood();

    QTimer * user_timer = nullptr;
    QTimer * user_behit = nullptr;
    QString curr_str;
    QPixmap pix_user;
    Bullet * userbullet;
    int currmap[12][24];
    int curr;
    int endframe;
    int height = 0;
    int jumptime = 0;
    int blood = 3;
    bool faceright = true;//左为0，右为1
    bool runleft = false;
    bool runright = false;
    bool fall = false;
    bool jump = false;
    bool attack = false;
    bool behit = false;
    bool changeblood = false;

signals:
    void died();
};

#endif // USER_H
