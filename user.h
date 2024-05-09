#ifndef USER_H
#define USER_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>

enum  MapEle
{
    Nothing,        //0
    Wall,           //1
    Box,            //2
    Trap,           //3
    Fruit,          //4
    Monster,        //5
    CheckPoint,     //6
    Float,          //7
};

class User: public QLabel
{
    Q_OBJECT
public:
    User();
    void setUserPixLoad();
    void userMove();

    QTimer * user_timer = nullptr;
    QString curr_str;
    QPixmap pix_user;
    int currmap[12][24];
    int blood;
    int curr;
    int endframe;
    int height = 0;
    bool faceright = true;//左为0，右为1
    bool runleft = false;
    bool runright = false;
    bool fall = false;
    bool jump = false;
    bool attack = false;
    bool behit = false;

signals:
};

#endif // USER_H
