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
    QLabel * labelScore = nullptr;
    QLabel * labelTime = nullptr;
    QTimer * timer = nullptr;
    QList<int>keys;
    QTimer * keysTimer = nullptr;

    User * m_user= nullptr;
    MapData * leveldata = nullptr;
signals:
    void return_to_levels();
};

#endif // PLAYSCENE_H
