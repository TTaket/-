#include "gamechoice2.h"
#include "ui_gamechoice2.h"

GameChoice2::GameChoice2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoice2)
{
    ui->setupUi(this);

    ui->wd_chooseSave_1->setInfo("存档1");
    ui->wd_chooseSave_2->setInfo("存档2");
    ui->wd_chooseSave_3->setInfo("存档3");
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
    Q_EMIT SIG_jumpWidget(4);
    CGameSystem::Make_The_Scene(CGameSystem::Checkpoint);
};

//选择存档2
void GameChoice2::slot_pb_save2()
{
    //Q_EMIT SIG_save_02();
    CGameSystem::Make_The_Scene(CGameSystem::Checkpoint);
};

//选择存档3
void GameChoice2::slot_pb_save3()
{
    CGameSystem::Make_The_Scene(CGameSystem::Checkpoint);
}

//返回上一页
void GameChoice2::slot_pb_return()
{
    Q_EMIT SIG_jumpWidget(2);
};


