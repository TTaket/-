#include "gamechoice.h"
#include "ui_gamechoice.h"

GameChoice::GameChoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoice)
{
    ui->setupUi(this);
}

GameChoice::~GameChoice()
{
    delete ui;
}
void GameChoice::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //painter.begin(this);
    drawPixmap(&painter);
    //painter.end();
};
void GameChoice::drawPixmap(QPainter *painter){
    //painter->save();
    QImage image;
    image.load("../Fear_No_One/Resource/Photo/Gamechoice.png");
    painter->drawImage(0, 0, image);
    //painter->restore();
};

//开始新的游戏
void GameChoice::on_pb_startNew_clicked()
{
    Q_EMIT SIG_jumpWidget(3);
}

//返回上一页
void GameChoice::on_pb_returnLastPage_clicked()
{
    Q_EMIT SIG_jumpWidget(1);
}
