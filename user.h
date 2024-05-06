#ifndef USER_H
#define USER_H

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QVector>
#include <QKeyEvent>

class User: public QLabel
{
    Q_OBJECT
public:
    User();
    void setUserPixLoad();
    void userMove();

    QTimer * user_timer;
    QString curr_str;
    QPixmap pix_user;
    int blood;
    int speed;
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
