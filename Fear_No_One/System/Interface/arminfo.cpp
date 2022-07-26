#include "arminfo.h"
#include "ui_arminfo.h"
#include <QPixmap>

ArmInfo::ArmInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmInfo)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::NoFocus);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/armInfo.png"));
}

ArmInfo::~ArmInfo()
{
    delete ui;
}

//设置武器信息
void ArmInfo::setArmInfo(CArm *arm)
{
    QPixmap img;
    QString str;
    //获取当前人物信息
    int id = CGameSystem::using_peoid;

    img = CGameSystem::Character_Info[id-1]->m_iconPos;
    img.scaled(this->width(), this->height());
    ui->lb_peopleIcon->setPixmap(img);
    ui->lb_peopleIcon->setScaledContents(true);

    ui->lb_attackValue->setText(str.setNum(arm->m_ATK,10));
    ui->lb_huibiValue->setText(str.setNum(arm->m_Shanbi,10));
    ui->lb_bishaValue->setText(str.setNum(0,10));
    ui->lb_mingzhongValue->setText(str.setNum(arm->m_Mingzhong,10));
}
