#include "duiwu.h"
#include "ui_duiwu.h"

Duiwu::Duiwu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Duiwu)
{
    ui->setupUi(this);

    ui->lb_duiwu->setAlignment(Qt::AlignCenter);

    ui->tw_duiwu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_duiwu->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tw_duiwu->setColumnCount(10);
    ui->tw_duiwu->setRowCount(CGameSystem::Character_Info.size());

    QTableWidgetItem* blank = new QTableWidgetItem;
    blank->setText("");

    QTableWidgetItem* icon = new QTableWidgetItem;
    icon->setText("头像");
    ui->tw_duiwu->setHorizontalHeaderItem(0,icon);

    QTableWidgetItem* name = new QTableWidgetItem;
    name->setText("姓名");
    ui->tw_duiwu->setHorizontalHeaderItem(1,name);

    QTableWidgetItem* level = new QTableWidgetItem;
    level->setText("等级");
    ui->tw_duiwu->setHorizontalHeaderItem(2,level);

    QTableWidgetItem* hp = new QTableWidgetItem;
    hp->setText("血量");
    ui->tw_duiwu->setHorizontalHeaderItem(3,hp);

    QTableWidgetItem* liliang = new QTableWidgetItem;
    liliang->setText("力量");
    ui->tw_duiwu->setHorizontalHeaderItem(4,liliang);

    QTableWidgetItem* jishu = new QTableWidgetItem;
    jishu->setText("技术");
    ui->tw_duiwu->setHorizontalHeaderItem(5,jishu);

    QTableWidgetItem* xingyun = new QTableWidgetItem;
    xingyun->setText("幸运");
    ui->tw_duiwu->setHorizontalHeaderItem(6,xingyun);

    QTableWidgetItem* sudu = new QTableWidgetItem;
    sudu->setText("速度");
    ui->tw_duiwu->setHorizontalHeaderItem(7,sudu);

    QTableWidgetItem* kangjia = new QTableWidgetItem;
    kangjia->setText("抗甲");
    ui->tw_duiwu->setHorizontalHeaderItem(8,kangjia);

    QTableWidgetItem* mokang = new QTableWidgetItem;
    mokang->setText("魔抗");
    ui->tw_duiwu->setHorizontalHeaderItem(9,mokang);

    for(int i=0;i<10;i++)
    {
        ui->tw_duiwu->setVerticalHeaderItem(i,blank);
    }



}

Duiwu::~Duiwu()
{
    delete ui;
}

//设置队伍列表信息
void Duiwu::setInfo()
{
    //1.获取游戏所有角色信息
    Character* character;

    //头像
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QPixmap pixmap = character->m_iconPos;
        pixmap = pixmap.scaled(ui->tw_duiwu->height() / CGameSystem::Character_Info.size(),
                               ui->tw_duiwu->height() / CGameSystem::Character_Info.size(),
                               Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QLabel* label = new QLabel;
        label->setPixmap(pixmap);

        ui->tw_duiwu->setCellWidget(i, 0, label);
    }

    //名字
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QTableWidgetItem* name = new QTableWidgetItem;
        name->setText(QString::fromStdString(character->m_name));
        ui->tw_duiwu->setItem(i, 1, name);
    }

    //等级
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QTableWidgetItem* level = new QTableWidgetItem;
        level->setText(QString::number(character->m_Attributes.m_Level));
        ui->tw_duiwu->setItem(i, 2, level);
    }

    //血量
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QString str = QString("%1/%2").arg(character->m_Attributes.m_HpNow).arg(character->m_Attributes.m_HpMax);
        QTableWidgetItem* hp = new QTableWidgetItem;
        hp->setText(str);
        ui->tw_duiwu->setItem(i, 3, hp);
    }

    //攻击力
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QTableWidgetItem* gongjili = new QTableWidgetItem;
        gongjili->setText(QString::number(character->m_Attributes.Gongjili));
        ui->tw_duiwu->setItem(i, 4, gongjili);
    }

    //技巧
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QTableWidgetItem* jishu = new QTableWidgetItem;
        jishu->setText(QString::number(character->m_Attributes.Jiqiao));
        ui->tw_duiwu->setItem(i, 5, jishu);
    }

    //幸运
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QTableWidgetItem* xingyun = new QTableWidgetItem;
        xingyun->setText(QString::number(character->m_Attributes.Xingyun));
        ui->tw_duiwu->setItem(i, 6, xingyun);
    }

    //速度
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QTableWidgetItem* sudu = new QTableWidgetItem;
        sudu->setText(QString::number(character->m_Attributes.Sudu));
        ui->tw_duiwu->setItem(i, 7, sudu);
    }

    //抗甲
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QTableWidgetItem* kangjia = new QTableWidgetItem;
        kangjia->setText(QString::number(character->m_Attributes.Hujia));
        ui->tw_duiwu->setItem(i, 8, kangjia);
    }


    //魔抗
    for(int i = 0; i < CGameSystem::Character_Info.size(); i++)
    {
        character = CGameSystem::Character_Info[i];
        QTableWidgetItem* mokang = new QTableWidgetItem;
        mokang->setText(QString::number(character->m_Attributes.Mokang));
        ui->tw_duiwu->setItem(i, 9, mokang);
    }
}

void Duiwu::on_pb_close_clicked()
{
    this->hide();
}
