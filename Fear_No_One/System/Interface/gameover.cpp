#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    ui->lb_gameOver->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/GameOver.png")
                               .scaled(ui->lb_gameOver->width(), ui->lb_gameOver->height()));
}

GameOver::~GameOver()
{
    delete ui;
}

//重新开始游戏
void GameOver::on_pb_returnGameStart_clicked()
{
    CGameSystem::m_gameSound->gameOverSoundPlay(false);
    CGameSystem::OverGame();
    CGameSystem::InitGame();
    CGameSystem::m_gameSound->gameStartBgmPlay(true);;
    Q_EMIT SIG_jumpWidget(1);
}
