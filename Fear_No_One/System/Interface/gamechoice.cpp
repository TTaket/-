#include "gamechoice.h"
#include "ui_gamechoice.h"

GameChoice::GameChoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoice)
{
    ui->setupUi(this);

    ui->wd_continue->setInfo("继续游戏");
    ui->wd_copy->setInfo("复制记录");
    ui->wd_delete->setInfo("删除记录");
    ui->wd_return->setInfo("返回");
    ui->wd_start->setInfo("开始游戏");

    QObject::connect(ui->wd_continue,
                     SIGNAL(SIG_pb_continue()),
                     this,
                     SLOT(slot_pb_continue()));

    QObject::connect(ui->wd_copy,
                     SIGNAL(SIG_pb_copy()),
                     this,
                     SLOT(slot_pb_copy()));

    QObject::connect(ui->wd_delete,
                     SIGNAL(SIG_pb_delete()),
                     this,
                     SLOT(slot_pb_delete()));

    QObject::connect(ui->wd_return,
                     SIGNAL(SIG_pb_return()),
                     this,
                     SLOT(slot_pb_return()));

    QObject::connect(ui->wd_start,
                     SIGNAL(SIG_pb_start()),
                     this,
                     SLOT(slot_pb_start()));

}

GameChoice::~GameChoice()
{
    delete ui;
}
void GameChoice::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    drawPixmap(&painter);
};
void GameChoice::drawPixmap(QPainter *painter){
    painter->save();
    QImage image;
    image.load("../Fear_No_One/Resource/Photo/Gamechoice.png");
    painter->drawImage(0, 0, image);
    painter->restore();
}

//继续游戏
void GameChoice::slot_pb_continue()
{
   ;
}

//开始新的游戏
void GameChoice::slot_pb_start()
{
    Q_EMIT SIG_jumpWidget(3);
}

//返回上一页
void GameChoice::slot_pb_return()
{
    Q_EMIT SIG_jumpWidget(1);
}

//删除记录
void GameChoice::slot_pb_delete()
{
    ;
}

//复制记录
void GameChoice::slot_pb_copy()
{
    ;
};
