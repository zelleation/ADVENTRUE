#include "playscene.h"
#include <QDebug>
#include "choicebutton.h"
#include <QFrame>
#include <QDialog>

PlayScene::PlayScene(int index)
{
    leveldata = new MapData(this);
    this->levelIndex = index;
    qDebug()<<"enter level "<<index;

    this->setFixedSize(64*18,64*9);
    this->setWindowTitle(QString("Level %1").arg(index));

    labelScore = new QLabel(this);
    labelScore->setText(QString("Score:%1").arg(score));
    labelScore->move(20,20);
    labelTime = new QLabel(this);
    labelTime->move(32*5,20);
    labelTime->setText(QString("Time: %1 : %2 ").arg(time/60).arg(time%60));
    timer = new QTimer(this);
    timer->start(1000);
    connect(this->timer,&QTimer::timeout,[=](){
        labelTime->setText(QString("Time: %1 : %2 ").arg(time/60).arg(time%60));
        time++;
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

        emit this->return_to_levels();
        qDebug()<<"emit this->return_to_levels();";
    });

    this->m_user = new User;
    m_user->setParent(this);
    m_user->move(48*2,48*9+16);//角色初始化
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 24; j++)
            this->m_user->currmap[i][j] = leveldata->m_map[levelIndex][i][j];

    }
    connect(this->m_user->user_timer,&QTimer::timeout,this->m_user,&User::setUserPixLoad);
    connect(this->m_user->user_timer,&QTimer::timeout,[=](){
        this->m_user->curr++;
        if(this->m_user->curr >= this->m_user->endframe)
        {
            this->m_user->curr = 1;
        }
        update();
    });
    connect(this->m_user->user_timer,&QTimer::timeout,this->m_user,&User::userMove);
    connect(this->m_user,&User::died,this,&PlayScene::loseGame);
    keysTimer = new QTimer(this);
    connect(this->keysTimer,&QTimer::timeout,this,&PlayScene::keysSlot);
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPainter userPainter(this);
    this->pix_background.load(":/background/rsc/Background/background_yellow.png");
    painter.drawPixmap(0,0,pix_background);

    for(int i = 0; i < 12 ; i++)
    {
        for (int j = 0; j < 24 ; j++)
        {
            QString craftPath;
            switch (m_user->currmap[i][j]) {
            case Nothing:
                break;
            case Wall:
                craftPath = ":/background/rsc/Background/wall.png";
                break;
            case Box:
                craftPath = ":/background/rsc/Background/box.png";
                break;
            case Trap1:
                craftPath = ":/trap/rsc/Traps/spiker.png";
                break;
            case Trap2:
                craftPath = "";
                break;
            case Fruit:
                craftPath = "";
                break;
            case Monster:
                craftPath = "";
                break;
            case CheckPoint:
                craftPath = "";
                break;
            case Float:
                craftPath = "";
                break;
            default:
                break;
            }
            QPixmap mapPix;
            if(leveldata->m_map[this->levelIndex][i][j] == 0)
                continue;
            mapPix.load(craftPath);
            painter.drawPixmap(j*48,i*48,mapPix);
        }
    }
    userPainter.drawPixmap(m_user->pos(),m_user->pix_user);
}
void PlayScene::keyPressEvent(QKeyEvent *e)
{
    if(!e->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
    {
        qDebug()<<"keypress"<<e->key();
        keys.append(e->key());
    }
    if(!keysTimer->isActive()) //如果定时器不在运行，就启动一下
        keysTimer->start(50);

    QWidget::keyPressEvent(e);
}
void PlayScene::keyReleaseEvent(QKeyEvent* e)
{
    if(!e->isAutoRepeat())
    {
        qDebug()<<"keyrelease"<<e->key();
        keys.removeAll(e->key());
        if(e->key()==Qt::Key_W && !e->isAutoRepeat())
        {
            this->m_user->jump = false;
            this->m_user->fall = true;
        }
        if(e->key()==Qt::Key_A && !e->isAutoRepeat())
        {
            this->m_user->runleft = false;
        }
        if(e->key()==Qt::Key_D && !e->isAutoRepeat())
        {
            this->m_user->runright = false;
        }
    }
    if(keys.isEmpty()) //容器空了，关闭定时器
        keysTimer->stop();
    QWidget::keyReleaseEvent(e);
}
void PlayScene::keysSlot()
{
    foreach (int key, keys)
    {
        switch (key)
        {
        case Qt::Key_W:
            if(this->m_user->jumptime < 12)
                this->m_user->jump = true;
            break;
        case Qt::Key_A:
            this->m_user->runleft = true;
            break;
        case Qt::Key_D:
            this->m_user->runright = true;
            break;
        case Qt::Key_Space:
            if(this->m_user->userbullet!=nullptr)
                this->m_user->attack = true;
            break;
        default:
            break;
        }
    }
    //qDebug()<<m_user->jump;
}
void PlayScene::loseGame()
{
    qDebug()<<"you lose";
    QMessageBox * losemsg = new QMessageBox(this);
    QFont f("Arial",30);
    losemsg->setFont(f);
    losemsg->setText("YOU LOSE!");
    losemsg->setIconPixmap(QPixmap(":/user/rsc/User/Idle1.png"));
    losemsg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool); // 无边框设置
    losemsg->setAttribute(Qt::WA_TranslucentBackground);// 背景透明设置
    losemsg->addButton(QMessageBox::Yes);
    losemsg->setButtonText(QDialogButtonBox::Yes,"Return");
    int ret = losemsg->exec();
    switch(ret)
    {
    case QMessageBox::Yes:
        delete this->m_user;
        emit this->return_to_levels();
        break;
    }
}
void PlayScene::winGmae()
{

}
