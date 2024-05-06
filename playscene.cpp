#include "playscene.h"
#include <QDebug>
#include "choicebutton.h"
#include <QPropertyAnimation>

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
    m_user->move(64*2,64*8);//角色初始化

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
    keysTimer = new QTimer(this);//键盘输入
    connect(this->keysTimer,&QTimer::timeout,this,&PlayScene::keysSlot);
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPainter userPainter(this);
    this->pix_background.load(":/background/rsc/Background/background_yellow.png");
    painter.drawPixmap(0,0,pix_background);

    for(int i = 0; i < 9 ; i++)
    {
        for (int j = 0; j < 18 ; j++)
        {
            QString craftPath;
            switch (leveldata->m_map[this->levelIndex][i][j]) {
            case Nothing:
                break;
            case Wall:
                craftPath = ":/craft/rsc/Background/WallGreen.png";
                break;
            case Box:
                craftPath = ":/craft/rsc/Background/Box.png";
                break;
            case Trap:
                craftPath = ":/trap/rsc/Traps/Stab.png";
                break;
            case Fruit:
                craftPath = "";
                break;
            case Monster:
                craftPath = "";
                break;
            case CheckPoint:
                craftPath = ":/checkpoint/rsc/Items/Checkpoints/Checkpoint/Checkpoint NoFlag.png";
                break;
            case Float:
                craftPath = ":/craft/rsc/Background/Float.png";
                break;
            default:
                break;
            }
            QPixmap mapPix;
            if(leveldata->m_map[this->levelIndex][i][j] == 0)
                continue;
            mapPix.load(craftPath);
            painter.drawPixmap(j*64,i*64,mapPix);
        }
    }

    userPainter.drawPixmap(m_user->pos(),m_user->pix_user);
}

void PlayScene::keyPressEvent(QKeyEvent *e)
{
    if(!e->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
    {
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
        //判断如果不是长按时自动触发的释放,就将key值从容器中删除
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
            if( this->m_user->height > 128)
            {
                this->m_user->jump = false;
                this->m_user->fall = true;
            }
            else
            {
                this->m_user->jump = true;
            }
            break;
        case Qt::Key_A:
            this->m_user->runleft = true;
            break;
        case Qt::Key_D:
            this->m_user->runright = true;
            break;
        default:
            break;
        }
    }
}

