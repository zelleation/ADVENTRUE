#include "homewindow.h"
#include "ui_homewindow.h"
#include "choicebutton.h"
#include <QTimer>
#include <QLabel>

HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    this->setFixedSize(64*18,64*9);
    this->setWindowIcon(QIcon(":/user/rsc/User/Idle1.png"));

    this->timer = new QTimer(this);
    this->timer2 = new QTimer(this);
    timer->start(50);
    for(int i = 1; i <= 11 ; i++)
    {
        QString str = QString(":/user/rsc/User/Run%1.png").arg(i);
        this->pix_runner.load(str);
    }
    for(int i = 1; i <= 12 ; i++)
    {
        QString str = QString(":/user/rsc/User/Idle%1.png").arg(i);
        this->pix_runner.load(str);
    }
    curr = 1;
    loca = 1;
    connect(this->timer,&QTimer::timeout,[=](){
        QString str = QString(":/user/rsc/User/Run%1.png").arg(curr++);
        this->pix_runner.load(str);
        loca++;
        if(curr>=12)
        {
            this->curr = 1;
        }
        if(loca >= 144)
        {
            timer->stop();
            delete timer;
            emit change();
        }
        emit changePix();
    });
    connect(this,&HomeWindow::changePix,[=](){
        update();
    });
    connect(this,&HomeWindow::change,[=](){
        timer2->start(50);
    });
    connect(this->timer2,&QTimer::timeout,[=](){
        QString str = QString(":/user/rsc/User/Idle%1.png").arg(curr++);
        this->pix_runner.load(str);
        if(curr>=11)
        {
            this->curr = 1;
        }
        emit changePix2();
    });
    connect(this,&HomeWindow::changePix2,[=](){
        update();
    });

    levelsWindow = new LevelsWindow;
    connect(levelsWindow,&LevelsWindow::return_to_homewindow,this,[=](){

        QTimer::singleShot(360,this,[=](){
            levelsWindow->hide();
            this->show();
        });

    });
    ChoiceButton * startBtn = new ChoiceButton(":/icon/rsc/Menu/Buttons/Play.png");
    startBtn->setParent(this);
    startBtn->move(64*8,64*7);
    connect(startBtn,&ChoiceButton::clicked,[=](){
        qDebug()<<"startBtn clicked";
        startBtn->move_down();
        startBtn->move_up();

        QTimer::singleShot(360,this,[=](){
            this->hide();
            levelsWindow->playLevel = new PlayScene(1);
            levelsWindow->show();
            levelsWindow->hide();
            levelsWindow->playLevel->show();
        });

    });

    ChoiceButton * levelsBtn = new ChoiceButton(":/icon/rsc/Menu/Buttons/Levels.png");
    levelsBtn->setParent(this);
    levelsBtn->move(64*9,64*7);
    connect(levelsBtn,&ChoiceButton::clicked,[=](){
        qDebug()<<"levelsBtn clicked";
        levelsBtn->move_down();
        levelsBtn->move_up();

        QTimer::singleShot(360,this,[=](){
            this->hide();
            levelsWindow->show();
        });

    });

    ChoiceButton * achievementBtn = new ChoiceButton(":/icon/rsc/Menu/Buttons/Achievements.png");
    achievementBtn->setParent(this);
    achievementBtn->move(64*10,64*7);
    connect(achievementBtn,&ChoiceButton::clicked,[=](){
        qDebug()<<"achievementBtn clicked";
        achievementBtn->move_down();
        achievementBtn->move_up();

    });

    ChoiceButton * soundBtn = new ChoiceButton(":/icon/rsc/Menu/Buttons/Volume.png",":/icon/rsc/Menu/Buttons/No_volume.png");
    soundBtn->setParent(this);
    soundBtn->move(64*17+16,64*8+32);
    connect(soundBtn,&ChoiceButton::clicked,[=](){
        qDebug()<<"soundBtn clicked";
        soundBtn->changeImg();
    });


    ChoiceButton * settingsBtn = new ChoiceButton(":/icon/rsc/Menu/Buttons/Settings.png");
    settingsBtn->setParent(this);
    settingsBtn->move(64*16+16,64*8+32);
    connect(settingsBtn,&ChoiceButton::clicked,[=](){
        qDebug()<<"settingsBtn clicked";

        settingsBtn->move_down();
        settingsBtn->move_up();
    });
}

void HomeWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/background/rsc/Background/background_yellow.png");
    painter.drawPixmap(0,0,pix);
    QPixmap pix_text;
    pix_text.load(":/text/rsc/text/title.png");
    painter.drawPixmap(64*4,64*1,pix_text);
    QPixmap pix_img;
    pix_img.load(":/background/rsc/Background/HomeAnimation.png");
    painter.drawPixmap(64*4,64*3,pix_img);

    painter.drawPixmap(265+loca*4,64*5+7,pix_runner);
    //qDebug()<<265+loca*4;

}

HomeWindow::~HomeWindow()
{
    delete ui;
}
