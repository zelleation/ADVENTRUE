#include "choicebutton.h"
#include <qDebug>
#include <QPropertyAnimation>

ChoiceButton::ChoiceButton(QString normalImg,QString changedImg)
{
    this->normalImg = normalImg;
    this->changedImg = changedImg;
    this->check = true;
    QPixmap pix;
    bool check = pix.load(normalImg);
    if(!check)
    {
        qDebug()<<"load failed";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void ChoiceButton::move_down()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(270);//time
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));//startlocation
    animation->setEndValue(QRect(this->x(),this->y()+4,this->width(),this->height()));//endlocation
    animation->setEasingCurve(QEasingCurve::InOutBounce);//fx
    animation->start();
}
void ChoiceButton::move_right()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(270);//time
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));//startlocation
    animation->setEndValue(QRect(this->x()+4,this->y(),this->width(),this->height()));//endlocation
    animation->setEasingCurve(QEasingCurve::OutBounce);//fx
    animation->start();
}
void ChoiceButton::move_up()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(270);//time
    animation->setStartValue(QRect(this->x(),this->y()+4,this->width(),this->height()));//startlocation
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));//endlocation
    animation->setEasingCurve(QEasingCurve::OutBounce);//fx
    animation->start();
}
void ChoiceButton::move_left()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(270);//time
    animation->setStartValue(QRect(this->x()+4,this->y(),this->width(),this->height()));//startlocation
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));//endlocation
    animation->setEasingCurve(QEasingCurve::InOutBounce);//fx
    animation->start();
}
void ChoiceButton::changeImg()
{
    if(check)
    {
        QPixmap pix;
        bool is = pix.load(changedImg);
        if(!is)
        {
            qDebug()<<"load failed";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        check = false;

    }
    else
    {
        QPixmap pix;
        bool is = pix.load(normalImg);
        if(!is)
        {
            qDebug()<<"load failed";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        check = true;
    }
    return;
}
