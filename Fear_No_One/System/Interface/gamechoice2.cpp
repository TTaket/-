#include "gamechoice2.h"
#include "ui_gamechoice2.h"
#include <QDebug>

GameChoice2::GameChoice2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoice2)
{
    ui->setupUi(this);

    CGameSystem::Savemanage_Du();
    qDebug()<<"save01check = "<<CGameSystem::save01check;
    qDebug()<<"save02check = "<<CGameSystem::save02check;
    qDebug()<<"save03check = "<<CGameSystem::save03check;

    ui->wd_chooseSave_1->setInfo(QString("存档1 : 第%1关").arg(CGameSystem::save01check));
    ui->wd_chooseSave_2->setInfo(QString("存档2 : 第%1关").arg(CGameSystem::save02check));
    ui->wd_chooseSave_3->setInfo(QString("存档3 : 第%1关").arg(CGameSystem::save03check));
    ui->wd_return->setInfo("返回上一页");

    QObject::connect(ui->wd_chooseSave_1,
                     SIGNAL(SIG_pb_save1()),
                     this,
                     SLOT(slot_pb_save1()));

    QObject::connect(ui->wd_chooseSave_2,
                     SIGNAL(SIG_pb_save2()),
                     this,
                     SLOT(slot_pb_save2()));

    QObject::connect(ui->wd_chooseSave_3,
                     SIGNAL(SIG_pb_save3()),
                     this,
                     SLOT(slot_pb_save3()));

    QObject::connect(ui->wd_return,
                     SIGNAL(SIG_pb_return()),
                     this,
                     SLOT(slot_pb_return()));

}

GameChoice2::~GameChoice2()
{
    delete ui;
}

void GameChoice2::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    drawPixmap(&painter);
};
void GameChoice2::drawPixmap(QPainter *painter){
    painter->save();
    QImage image;
    image.load("../Fear_No_One/Resource/Photo/Gamechoice.png");
    painter->drawImage(0, 0, image);
    painter->restore();
}

//选择存档1
void GameChoice2::slot_pb_save1()
{
    CGameSystem::m_gameSound->gameMousePressChoiceSoundPlay(true);
    CGameSystem::m_gameSound->gameStartSoudPlay(false);
    CGameSystem::DuSave(1);
    CGameSystem::Make_The_Scene(CGameSystem::Checkpoint);
    Q_EMIT SIG_jumpWidget(4);
    //播放背景音乐
    CGameSystem::m_gameSound->gameMapBgmPlay(true);
};


//选择存档2
void GameChoice2::slot_pb_save2()
{
    CGameSystem::m_gameSound->gameMousePressChoiceSoundPlay(true);
    CGameSystem::m_gameSound->gameStartSoudPlay(false);
    //CGameSystem::DuSave(1);
    CGameSystem::Make_The_Scene(CGameSystem::Checkpoint);
    Q_EMIT SIG_jumpWidget(4);
};

//选择存档3
void GameChoice2::slot_pb_save3()
{
    CGameSystem::m_gameSound->gameMousePressChoiceSoundPlay(true);
    CGameSystem::m_gameSound->gameStartSoudPlay(false);
    //CGameSystem::DuSave(1);
    CGameSystem::Make_The_Scene(CGameSystem::Checkpoint);
    Q_EMIT SIG_jumpWidget(4);
}

//返回上一页
void GameChoice2::slot_pb_return()
{
    CGameSystem::m_gameSound->gameMousePressChoiceSoundPlay(true);
    Q_EMIT SIG_jumpWidget(2);
};


