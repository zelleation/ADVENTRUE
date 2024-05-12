#ifndef USER_H
#define USER_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QPoint>

enum  MapEle
{
    Nothing,        //0
    Wall,           //1
    Box,            //2
    Fruit,          //3
    CheckPoint,     //4
    Float,          //5
    Trap1,          //6
    Trap2,          //7
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
    void winGame();

    QTimer * user_timer = nullptr;
    QTimer * user_behit = nullptr;
    QString curr_str;
    QString checkpointpath = ":/checkpoint/rsc/Items/Checkpoints/Checkpoint/Checkpoint NoFlag.png";
    QPixmap pix_user;
    int currmap[12][24];
    int curr;
    int currcheckpoint = 0;
    int endframe;
    int height = 0;
    int jumptime = 0;
    int blood = 3;
    bool faceright = true;//左为0，右为1
    bool runleft = false;
    bool runright = false;
    bool fall = false;
    bool jump = false;
    bool behit = false;
    bool changeblood = false;

signals:
    void died();
    void win();
};

#endif // USER_H
