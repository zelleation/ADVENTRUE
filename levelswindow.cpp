#include "levelswindow.h"
#include "choicebutton.h"
#include <QPainter>
#include <QTimer>

LevelsWindow::LevelsWindow(QWidget *parent)
    : QMainWindow{parent}
{

    this->setWindowIcon(QPixmap(":/user/rsc/User/Idle1.png"));
    this->setFixedSize(64*18,64*9);
    this->setWindowTitle("choose level");

    ChoiceButton * soundBtn = new ChoiceButton(":/icon/rsc/Menu/Buttons/Volume.png",":/icon/rsc/Menu/Buttons/No_volume.png");
    soundBtn->setParent(this);
    soundBtn->move(64*17+16,64*8+32);
    connect(soundBtn,&ChoiceButton::clicked,[=](){
        qDebug()<<"soundBtn clicked";
        soundBtn->changeImg();

    });

    ChoiceButton * settingsBtn = new ChoiceButton(":/icon/rsc/Menu/Buttons/Settings.png");
    settingsBtn->setParent(this);
    settingsBtn->move(64*15+16,64*8+32);
    connect(settingsBtn,&ChoiceButton::clicked,[=](){
        qDebug()<<"settingsBtn clicked";

        settingsBtn->move_down();
        settingsBtn->move_up();

    });

    ChoiceButton * returnBtn = new ChoiceButton(":/icon/rsc/Menu/Buttons/Restart.png");
    returnBtn->setParent(this);
    returnBtn->move(64*16+16,64*8+32);
    connect(returnBtn,&ChoiceButton::clicked,[=](){
        qDebug()<<"returnBtn clicked";

        returnBtn->move_down();
        returnBtn->move_up();

        emit this->return_to_homewindow();
        qDebug()<<"emit this->return_to_homewindow();";
    });

    for(int i = 0; i < 12 ; i++)
    {
        ChoiceButton * level = new ChoiceButton(QString(":/level/rsc/Menu/Levels/%1.png").arg(i+1));
        level->setParent(this);
        level->move((i%6+6)*64,(i/6+4)*64);

        connect(level,&ChoiceButton::clicked,[=](){
            qDebug()<<QString("level%1 cliked").arg(i+1);

            level->move_down();
            level->move_up();
            playLevel = new PlayScene(i+1);

            QTimer::singleShot(360,this,[=](){
                this->hide();
                this->playLevel->show();
            });

            connect(playLevel,&PlayScene::return_to_levels,this,[=](){
                QTimer::singleShot(360,this,[=](){
                    playLevel->close();
                    if(this->playLevel != nullptr)playLevel->deleteLater();
                    this->show();
                });
            });
        });
    }
}

void LevelsWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/background/rsc/Background/background_yellow.png");
    painter.drawPixmap(0,0,pix);
    QPixmap pix_text;
    pix_text.load(":/text/rsc/text/title.png");
    painter.drawPixmap(64*4,64*1,pix_text);
}
