#include "changepeoplelistitem.h"
#include "ui_changepeoplelistitem.h"

ChangePeopleListItem::ChangePeopleListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePeopleListItem)
{
    ui->setupUi(this);
    ui->lb_blueFinger->setAlignment(Qt::AlignCenter);
    ui->lb_blueBackGround->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png")
                                      .scaled(ui->lb_blueBackGround->width(), ui->lb_blueBackGround->height()));
}

ChangePeopleListItem::~ChangePeopleListItem()
{
    delete ui;
}


void ChangePeopleListItem::setInfo(int id)
{
    //根据友方id获取友方信息
    m_id = id;
    Character *character = CGameSystem::Character_Info[id-1];
    //获取和显示友方名字
    QString blueName = QString::fromStdString(character->m_name);
    ui->lb_blueName->setText(blueName);
    //获取和显示友方当前hp和最大hp
    int curHp = character->m_Attributes.m_HpNow;
    int maxHp = character->m_Attributes.m_HpMax;
    ui->lb_blueHpValue->setText(QString("%1/%2").arg(curHp).arg(maxHp));
    //获取和显示友方等级
    int level = character->m_Attributes.m_Level;
    //qDebug()<<level;//等级获取正确但是未显示解决办法 ui放到前边
    ui->lb_blueLevelVal->setText(QString::number(level, 10));
    //设置和显示友方头像
    QPixmap pixmap = CGameSystem::Character_Info[id-1]->m_iconPos;
    pixmap.scaled(ui->lb_blueIcon->size(), Qt::KeepAspectRatio);
    ui->lb_blueIcon->setScaledContents(true);
    ui->lb_blueIcon->setPixmap(pixmap);
}

int ChangePeopleListItem::getBlueId()
{
    return m_id;
}

void ChangePeopleListItem::setFingerShow(bool enable)
{
    if(enable)
    {
        ui->lb_blueFinger->setText("Y");
    }
    else
    {
        ui->lb_blueFinger->setText("");
    }
}

