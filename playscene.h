#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QPainter>
#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include "user.h"
#include "mapdata.h"
#include <QList>
#include <QMap>
#include <QVector>

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

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int index);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void keysSlot();

    int levelIndex;
    long long score = 0;
    long long time = 0;

    QPixmap pix_background;
    QLabel * labelScore;
    QLabel * labelTime;
    QTimer * timer;
    QList<int> keys;
    QTimer * keysTimer;

    User * m_user= nullptr;
    MapData * leveldata;
signals:
    void return_to_levels();
};

#endif // PLAYSCENE_H
