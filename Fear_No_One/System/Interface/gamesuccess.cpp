#include "gamesuccess.h"
#include "ui_gamesuccess.h"

GameSuccess::GameSuccess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameSuccess)
{
    ui->setupUi(this);

    ui->lb_background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/gamewin.jpg")
                               .scaled(ui->lb_background->width(), ui->lb_background->height()));
}

GameSuccess::~GameSuccess()
{
    delete ui;
}

void GameSuccess::on_pb_returnGameStart_clicked()
{
    CGameSystem::m_gameSound->gameOverSoundPlay(false);
    CGameSystem::OverGame();
    CGameSystem::InitGame();
    CGameSystem::m_gameSound->gameStartBgmPlay(true);
    Q_EMIT SIG_jumpWidget(1);
}
