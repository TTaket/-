#include "attackreadyinfo.h"
#include "ui_attackreadyinfo.h"

AttackReadyInfo::AttackReadyInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttackReadyInfo)
{
    ui->setupUi(this);
    ui->lb_biSha->setAlignment(Qt::AlignCenter);
    ui->lb_blueArmName->setAlignment(Qt::AlignCenter);
    ui->lb_blueBiShaValue->setAlignment(Qt::AlignCenter);
    ui->lb_blueHpValue->setAlignment(Qt::AlignCenter);
    ui->lb_blueMingZhongValue->setAlignment(Qt::AlignCenter);
    ui->lb_bluePeoName->setAlignment(Qt::AlignCenter);
    ui->lb_blueWeiLiValue->setAlignment(Qt::AlignCenter);
    ui->lb_Hp->setAlignment(Qt::AlignCenter);
    ui->lb_mingZhong->setAlignment(Qt::AlignCenter);
    ui->lb_redArmName->setAlignment(Qt::AlignCenter);
    ui->lb_redBiShaValue->setAlignment(Qt::AlignCenter);
    ui->lb_redHpValue->setAlignment(Qt::AlignCenter);
    ui->lb_redMingZhongValue->setAlignment(Qt::AlignCenter);
    ui->lb_redPeoName->setAlignment(Qt::AlignCenter);
    ui->lb_redWeiLiValue->setAlignment(Qt::AlignCenter);
    ui->lb_weiLi->setAlignment(Qt::AlignCenter);


}

AttackReadyInfo::~AttackReadyInfo()
{
    delete ui;
}

void AttackReadyInfo::setInfo(int blueId,CArm* Armnow, int redId)
{
    //1.获取人物信息
    m_blueId = blueId;
    m_redId = redId;
    Character* blueCharacter = CGameSystem::Character_Info[blueId-1];
    Character* redCharacter = CGameSystem::Character_Info[redId-1];

    //2.获取双方当前装备的武器
    //蓝方
//    CArm* blueArm;
//    //从武器链表中获取该武器信息
//    for(auto ite = blueCharacter->Armslist.begin(); ite != blueCharacter->Armslist.end(); ite++)
//    {
//        if(!strcmp((*ite)->m_name.c_str(), CGameSystem::using_armName.c_str()))
//        {
//            blueArm = *ite;
//        }
//    }
    blueArm = Armnow;
    //红方
    redArm = redCharacter->m_Zhuangbei;

    //设置双方装备信息
    //蓝方
    ui->lb_blueBiShaValue->setText(QString::number(0,10));
    ui->lb_blueArmName->setText(QString::fromStdString(blueArm->m_name));
    ui->lb_blueHpValue->setText(QString::number(blueCharacter->m_Attributes.m_HpNow));
    ui->lb_blueMingZhongValue->setText(QString::number(blueArm->m_Mingzhong));
    ui->lb_bluePeoName->setText(QString::fromStdString(blueCharacter->m_name));
    ui->lb_blueWeiLiValue->setText(QString::number(blueArm->m_ATK));
    //红方
    ui->lb_redBiShaValue->setText(QString::number(0,10));
    ui->lb_redArmName->setText(QString::fromStdString(redArm->m_name));
    ui->lb_redHpValue->setText(QString::number(redCharacter->m_Attributes.m_HpNow));
    ui->lb_redMingZhongValue->setText(QString::number(redArm->m_Mingzhong));
    ui->lb_redPeoName->setText(QString::fromStdString(redCharacter->m_name));
    ui->lb_redWeiLiValue->setText(QString::number(redArm->m_ATK));
}

//开始战斗 按钮
void AttackReadyInfo::on_lb_startZhandou_clicked()
{
    //跳转到战斗界面
    qDebug()<<QString("红方id：%1").arg(m_redId);
    qDebug()<<QString("蓝方id：%1").arg(m_blueId);
    Fightinfo* finfo = CGameSystem::GetHit(m_blueId,blueArm,m_redId);
    //关闭其他控件

    GameMap::m_actionListEnable = 0;
    GameMap::m_armListEnable = 0;
    GameMap::m_armInfoEnable = 0;
    GameMap::m_tufeiListEnable = 0;
    GameMap::m_attackReadyInfoEnable = 0;
    Q_EMIT SIG_Fightinfo(finfo,CGameSystem::using_arm ,redArm);
}
