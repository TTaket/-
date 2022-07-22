#include "gamestart.h"
#include "ui_gamestart.h"


GameStart::GameStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameStart)
{
    ui->setupUi(this);
}

GameStart::~GameStart()
{
    delete ui;
}

//点击开始按钮，跳转到下一界面
void GameStart::on_pb_gameStart_clicked()
{
    Q_EMIT SIG_jumpWidget(2);
}


void GameStart::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //painter.begin(this);
    drawPixmap(&painter);
    //painter.end();
}


void GameStart::drawPixmap(QPainter *painter)
{
    //painter->save();
    QImage image;
    image.load("../Fear_No_One/Resource/Photo/Gamestart.png");
    painter->drawImage(0, 0, image);
    //painter->restore();
}
