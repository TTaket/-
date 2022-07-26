#include "tufeilistitem.h"
#include "ui_tufeilistitem.h"

TufeiListItem::TufeiListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TufeiListItem)
{
    ui->setupUi(this);

    ui->lb_tufeiFinger->setAlignment(Qt::AlignCenter);
    ui->lb_tufeiBackGround->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png")
                                      .scaled(ui->lb_tufeiBackGround->width(), ui->lb_tufeiBackGround->height()));
}

TufeiListItem::~TufeiListItem()
{
    delete ui;
}

void TufeiListItem::setFingerShow(bool enable)
{
    if(enable)
    {
        ui->lb_tufeiFinger->setText("Y");
    }
    else
    {
        ui->lb_tufeiFinger->setText("");
    }
}

//设置土匪信息
void TufeiListItem::setInfo(int id)
{
    //根据土匪id获取土匪信息
    m_id = id;
    Character *character = CGameSystem::Character_Info[id-1];
    //获取和显示土匪名字
    QString tufeiName = QString::fromStdString(character->m_name);
    ui->lb_tufeiName->setText(tufeiName);
    //获取和显示土匪当前hp和最大hp
    int curHp = character->m_Attributes.m_HpNow;
    int maxHp = character->m_Attributes.m_HpMax;
    ui->lb_tufeiHpValue->setText(QString("%1/%2").arg(curHp).arg(maxHp));
    //获取和显示土匪等级
    int level = character->m_Attributes.m_Level;
    //qDebug()<<level;//等级获取正确但是未显示解决办法 ui放到前边
    ui->lb_tufeiLevelVal->setText(QString::number(level, 10));
    //设置和显示土匪头像
    QPixmap pixmap = CGameSystem::Character_Info[id-1]->m_iconPos;
    pixmap.scaled(ui->lb_tufeiIcon->size(), Qt::KeepAspectRatio);
    ui->lb_tufeiIcon->setScaledContents(true);
    ui->lb_tufeiIcon->setPixmap(pixmap);
}

int TufeiListItem::getTufeiId()
{
    return m_id;
}

