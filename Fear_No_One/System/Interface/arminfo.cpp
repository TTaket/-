#include "arminfo.h"
#include "ui_arminfo.h"
#include <QPixmap>

ArmInfo::ArmInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmInfo)
{
    ui->setupUi(this);
}

ArmInfo::~ArmInfo()
{
    delete ui;
}

//设置武器信息
void ArmInfo::setArmInfo(CArm *arm)
{
    int id = 1;
    QPixmap img;
    QString str;
    //获取当前人物信息
    Character *character = CGameSystem::Character_Info[id-1];
    std::string characterName = character->m_name;
    if(!strcmp(characterName.c_str(), "罗伊"))
    {
        img.load("../Fear_No_One/Resource/Character/Head/head01-luoyi.png");
    }
    ui->lb_attackValue->setText(str.setNum(arm->m_ATK,10));
    ui->lb_huibiValue->setText(str.setNum(arm->m_Shanbi,10));
    ui->lb_bishaValue->setText(str.setNum(0,10));
    ui->lb_mingzhongValue->setText(str.setNum(arm->m_Mingzhong,10));
    ui->lb_peopleIcon->setPixmap(img);
}
