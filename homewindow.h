#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include "levelswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class HomeWindow;
}
QT_END_NAMESPACE

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

    void paintEvent(QPaintEvent *);

    LevelsWindow * levelsWindow=nullptr;

    QTimer* timer;
    QTimer* timer2;
    QPixmap pix_runner;
    int curr;
    int loca;
signals:
    void changePix();
    void change();
    void changePix2();

private:
    Ui::HomeWindow *ui;
};
#endif // HOMEWINDOW_H
