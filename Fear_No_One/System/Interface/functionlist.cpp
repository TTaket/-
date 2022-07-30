#include "functionlist.h"
#include "ui_functionlist.h"

Functionlist::Functionlist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Functionlist)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png").scaled(ui->background->width(), ui->background->height()));
    m_duiwu = new Duiwu;
}

Functionlist::~Functionlist()
{
    delete ui;
    if(m_duiwu){
        delete m_duiwu;
        m_duiwu = nullptr;
    }
}

void Functionlist::on_pb_sound_clicked()
{
    //静音
    GameMap::m_FunctionlistEnable = 0;
    Q_EMIT SIG_oundOpenCloseChoice();
}

void Functionlist::on_pb_duiwu_clicked()
{
    GameMap::m_FunctionlistEnable = 0;
    m_duiwu->setInfo();
    m_duiwu->show();

}

void Functionlist::on_pb_red_clicked()
{
    GameMap::m_FunctionlistEnable = 0;
    //红色方移动
    Q_EMIT ST_RedWork();

}

void Functionlist::on_pb_overgame_clicked()
{
    GameMap::m_FunctionlistEnable = 0;
    Q_EMIT SIG_jumpToGameStart();//返回主菜单
}
