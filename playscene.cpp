#include "playscene.h"
#include <QDebug>
#include "choicebutton.h"
#include <QFrame>
#include <QDialog>

PlayScene::PlayScene(int index)
{
    qDebug()<<"PlayScene::PlayScene(int index)";
    this->levelIndex = index;
    qDebug()<<"enter level "<<index;

    this->setFixedSize(64*18,64*9);
    this->setWindowTitle(QString("Level %1").arg(index));

    labelScore = new QLabel(this);
    labelScore->setStyleSheet("font-family:Microsoft YaHei;font-size: 14px;color:#778899;");
    labelScore->setText(QString("Score:%1").arg(score));
    labelScore->move(20,20);
    labelTime = new QLabel(this);
    labelTime->move(32*5,20);
    labelTime->setStyleSheet("font-family:Microsoft YaHei;font-size: 14px;color:#778899;");
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

    this->m_user = new User(levelIndex);
    m_user->setParent(this);
    m_user->move(48*2,48*9+16);//角色初始化

    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 24; j++)
        {
            if(this->m_user->currmap[i][j] == Fruit)
            {
                frunum++;
            }
        }
    }

    fru = new Fruits*[frunum];
    int pos = 0;
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 24; j++)
        {
            if(this->m_user->currmap[i][j] == Fruit)
            {
                fru[pos] = new Fruits();
                fru[pos]->u = m_user;
                fru[pos]->setParent(this);
                fru[pos]->move(j*48+8,i*48+8);
                connect(fru[pos],&Fruits::getScore,[&](){
                    this->score+=100;
                    labelScore->setText(QString("Score:%1").arg(score));
                });
                pos++;
            }
        }
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
    connect(this->m_user,&User::win,this,&PlayScene::winGame);
    keysTimer = new QTimer(this);
    connect(this->keysTimer,&QTimer::timeout,this,&PlayScene::keysSlot);

    this->pix_blood.load(":/craft/rsc/Items/blood.png");
}

void PlayScene::paintEvent(QPaintEvent *)
{
    qDebug()<<"void PlayScene::paintEvent(QPaintEvent *)";
    if(m_user == nullptr)
        return;
    QPainter painter(this);
    QPainter userPainter(this);
    this->pix_background.load(":/background/rsc/Background/background_yellow.png");
    painter.drawPixmap(0,0,pix_background);
    checkpointPath = m_user->checkpointpath;
    trapPath = QString(":/trap/rsc/Traps/trap%1.png").arg(currtrap++);
    if(currtrap == 9)
    {
        currtrap = 1;
    }

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
                craftPath = trapPath;
                break;
            case CheckPoint:
                craftPath = checkpointPath;
                break;
            default:
                break;
            }
            QPixmap mapPix;
            if(m_user->currmap[i][j] == 0)
                continue;
            mapPix.load(craftPath);
            painter.drawPixmap(j*48,i*48,mapPix);
        }
    }
    userPainter.drawPixmap(m_user->pos(),m_user->pix_user);
    for(int i = m_user->blood ; i > 0 ; i--)
    {
        painter.drawPixmap(48*22-i*48,24,pix_blood);
    }
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
    qDebug()<<"void PlayScene::keysSlot()";
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
        default:
            break;
        }
    }

}
void PlayScene::loseGame()
{
    qDebug()<<"void PlayScene::loseGame()";
    if(m_user == nullptr)
        return;
    QMessageBox * losemsg = new QMessageBox(this);
    QFont f("Arial",20);
    losemsg->setFont(f);
    losemsg->setText("YOU LOSE!");
    losemsg->setIconPixmap(QPixmap(":/user/rsc/User/Idle1.png"));
    losemsg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool); // 无边框设置
    losemsg->setAttribute(Qt::WA_TranslucentBackground);// 背景透明设置
    QPushButton * back = losemsg->addButton(QMessageBox::Yes);
    back->setStyleSheet("background-color:white;width:55px;height:25px");
    back->setText("BACK");
    back->move(480,512);
    losemsg->exec();
    losemsg->close();
    while(frunum--)
    {
        fru[frunum]->u = nullptr;
    }
    m_user->close();
    m_user = nullptr;
    qDebug()<<"return to levels(back)";
    emit this->return_to_levels();
        //disconnect(this->m_user,&User::died,this,&PlayScene::loseGame);

}
void PlayScene::winGame()
{
    qDebug()<<"void PlayScene::winGame()";
    if(m_user == nullptr)
        return;
    QMessageBox * winmsg = new QMessageBox(this);
    QFont f("Arial",20);
    winmsg->setFont(f);
    winmsg->setText("YOU WIN!");
    winmsg->setIconPixmap(QPixmap(":/user/rsc/User/Idle1.png"));
    winmsg->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool); // 无边框设置
    winmsg->setAttribute(Qt::WA_TranslucentBackground);// 背景透明设置
    QPushButton * back = winmsg->addButton(QMessageBox::Yes);
    back->setStyleSheet("background-color:white;width:55px;height:25px");
    back->setText("NEXT");
    back->move(480,512);
    winmsg->exec();
    winmsg->close();
    while(frunum--)
    {
        fru[frunum]->u = nullptr;
    }
    emit this->next_level();
}
