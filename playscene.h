#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QPainter>
#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include "user.h"
#include "mapdata.h"
#include "fruit.h"
#include <QList>
#include <QMap>
#include <QVector>
#include <QKeyEvent>
#include <QMessageBox>

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
    void loseGame();
    void winGame();

    int levelIndex;
    long long score = 0;
    long long time = 0;
    int frunum = 0;
    QPixmap pix_background;
    QLabel * labelScore = nullptr;
    QLabel * labelTime = nullptr;
    QTimer * timer = nullptr;
    QList<int>keys;
    QTimer * keysTimer = nullptr;
    QString checkpointPath = ":/checkpoint/rsc/Items/Checkpoints/Checkpoint/Checkpoint NoFlag.png";
    User * m_user= nullptr;
    MapData * leveldata = nullptr;
    Fruits ** fru = nullptr;
    QString trapPath;
    QPixmap pix_blood;
    QTimer * bloodTimer;
    int currtrap;
signals:
    void return_to_levels();
    void return_to_homewindow();
    void next_level();
};

#endif // PLAYSCENE_H
