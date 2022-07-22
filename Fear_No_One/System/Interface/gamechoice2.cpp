#include "gamechoice2.h"
#include "ui_gamechoice2.h"

GameChoice2::GameChoice2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoice2)
{
    ui->setupUi(this);
}

GameChoice2::~GameChoice2()
{
    delete ui;
}

void GameChoice2::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //painter.begin(this);
    drawPixmap(&painter);
    //painter.end();
};
void GameChoice2::drawPixmap(QPainter *painter){
    //painter->save();
    QImage image;
    image.load("../Fear_No_One/Resource/Photo/Gamechoice.png");
    painter->drawImage(0, 0, image);
    //painter->restore();
};

void GameChoice2::on_pb_returnLastPage_clicked()
{
    Q_EMIT SIG_jumpWidget(2);
}

//进入游戏
void GameChoice2::on_pb_choice2_1_clicked()
{
    Q_EMIT SIG_jumpWidget(4);
}
