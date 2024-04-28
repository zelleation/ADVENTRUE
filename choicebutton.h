#ifndef CHOICEBUTTON_H
#define CHOICEBUTTON_H

#include <QPushButton>>

class ChoiceButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit ChoiceButton(QWidget *parent = nullptr);
    QString normalImg;
    QString changedImg;
    bool check;

    ChoiceButton(QString normalImg,QString changedImg="");

    void move_down();
    void move_right();
    void move_up();
    void move_left();

    void changeImg();


signals:
    void changeIcon();
};

#endif // CHOICEBUTTON_H
