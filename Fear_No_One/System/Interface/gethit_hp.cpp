#include "gethit_hp.h"
#include "ui_gethit_hp.h"


gethit_hp::gethit_hp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gethit_hp)
{

    ui->setupUi(this);
    ui->te_fightinfo->setStyleSheet("background-color: rgb(255, 255, 255,60);");


    QTimer *CurrentTime = new QTimer(this);
    CurrentTime->start(1000);
    tinfo = new Tool_Info;
    m_gethit_exp = new gethit_exp;



}

gethit_hp::~gethit_hp()
{
    delete ui;
    if(m_gethit_exp){
        delete m_gethit_exp;
        m_gethit_exp = nullptr;
    }
    if(tinfo){
        delete tinfo;
        tinfo = nullptr;
    }
    if(finfo){
        delete finfo;
        finfo = nullptr;
    }
}


void gethit_hp::setInfo(Fightinfo* Finfo,CArm*arm1,CArm*arm2){
    finfo = Finfo;
    blueid = Finfo->id1;
    redid = Finfo->id2;
    Arm1 = arm1;
    Arm2 = arm2;
    ground_id = Finfo->Groundid;

}

void gethit_hp::Init_ui(){
    Character* peo1 = CGameSystem::Character_Info[blueid-1];
    Character* peo2 = CGameSystem::Character_Info[redid-1];
    //arm 为参数

    ui->Pro_Hp1->setRange(0,finfo->hp1_max);
    ui->Pro_Hp1->setValue(finfo->hp1_now);

    ui->Pro_Hp2->setRange(0,finfo->hp2_max);
    ui->Pro_Hp2->setValue(finfo->hp2_now);
    ui->lb_hpinfo1->setText(QString("%1/%2").arg(finfo->hp1_now).arg(finfo->hp1_max));
    ui->lb_hpinfo2->setText(QString("%1/%2").arg(finfo->hp2_now).arg(finfo->hp2_max));

    ui->lb_icon1->setPixmap(QPixmap(peo1->m_iconPos).scaled(ui->lb_icon1->width(), ui->lb_icon1->height()));
    ui->lb_icon2->setPixmap(QPixmap(peo2->m_iconPos).scaled(ui->lb_icon2->width(), ui->lb_icon2->height()));
    ui->lb_name1->setText(QString::fromStdString(peo1->m_name));
    ui->lb_name2->setText(QString::fromStdString(peo2->m_name));
    ui->lb_arm1->setText(QString::fromStdString(Arm1->m_name));
    ui->lb_arm2->setText(QString::fromStdString(Arm2->m_name));



    switch (ground_id) {
        case 1:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(1)).scaled(ui->background->width(), ui->background->height()));
            break;
        case 2:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(2)).scaled(ui->background->width(), ui->background->height()));
            break;
        case 3:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(3)).scaled(ui->background->width(), ui->background->height()));
            break;
        case 4:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(4)).scaled(ui->background->width(), ui->background->height()));
            break;
        case 5:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(5)).scaled(ui->background->width(), ui->background->height()));
            break;
        case 6:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(6)).scaled(ui->background->width(), ui->background->height()));
            break;
        case 7:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(7)).scaled(ui->background->width(), ui->background->height()));
            break;
        case 8:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(8)).scaled(ui->background->width(), ui->background->height()));
            break;
        case 9:
            ui->background->setPixmap(QPixmap(_DEF_FightGround_load(9)).scaled(ui->background->width(), ui->background->height()));
            break;
    }

    GameMap::m_gethithpEnable = 1;
}


void gethit_hp::st_Fight(){
    this->hide();
    ui->te_fightinfo->clear();
    this->show();
    ui->te_fightinfo->show();
    QCoreApplication::processEvents();//保证完整的show
    int tmpnowhp = finfo->hp2_now;
    int willhp = 0;
    for(int i=1;i<=finfo->ATKtime;i++){
        QThread::msleep(500);
        if(i == 1){
            ui->te_fightinfo->append(QString("进行第一次攻击"));
            QCoreApplication::processEvents();
            QThread::msleep(1500);
            if(finfo->is_miss1){
                ui->te_fightinfo->append(QString("没有命中"));
                QCoreApplication::processEvents();

                continue;
            }
            willhp = tmpnowhp - finfo->Hit1;
            if(willhp <= 0){
                willhp = 0;
            }
            while(tmpnowhp>willhp){
                ui->Pro_Hp2->setValue(--tmpnowhp);
                ui->lb_hpinfo2->setText(QString("%1/%2").arg(tmpnowhp).arg(finfo->hp2_max));
                QThread::msleep(30);
            }
            QCoreApplication::processEvents();
            if(finfo->is_boji1){
                ui->te_fightinfo->append(QString("打出了暴击伤害 %1 点").arg(finfo->Hit1));
                QCoreApplication::processEvents();
            }else{
                ui->te_fightinfo->append(QString("打出了普通进攻 %1 点").arg(finfo->Hit1));
                QCoreApplication::processEvents();
            }

        }else{
            ui->te_fightinfo->append(QString("进行第二次攻击"));
            QCoreApplication::processEvents();
            QThread::msleep(1500);
            if(finfo->is_miss2){
                ui->te_fightinfo->append(QString("没有命中"));
                QCoreApplication::processEvents();

                continue;
            }
            willhp = tmpnowhp - finfo->Hit2;
            if(willhp <= 0){
                willhp = 0;
            }
            while(tmpnowhp>willhp){
                ui->Pro_Hp2->setValue(--tmpnowhp);
                ui->lb_hpinfo2->setText(QString("%1/%2").arg(tmpnowhp).arg(finfo->hp2_max));
                QThread::msleep(30);
            }

            if(finfo->is_boji2){
                ui->te_fightinfo->append(QString("打出了暴击伤害 %1 点").arg(finfo->Hit2));
                QCoreApplication::processEvents();
            }else{
                ui->te_fightinfo->append(QString("打出了普通进攻 %1 点").arg(finfo->Hit2));
                QCoreApplication::processEvents();
            }
        }

        if(tmpnowhp<=0){
            ui->te_fightinfo->append(QString("敌人阵亡"));
            QCoreApplication::processEvents();

            break;
        }
    }
    Sleep(500);
    ui->te_fightinfo->append(QString("战斗结束"));
    QCoreApplication::processEvents();
    ui->te_fightinfo->update();
    Sleep(1500);//稍暂停

    GameMap::m_gethithpEnable = 0;

    if(finfo->is_die){
        CGameSystem::Character_Info[finfo->id2-1]->m_Islive = 0;//设为死亡;
    }

    if(finfo->Add_Money>0 && CGameSystem::Character_Info[finfo->id1-1]->m_Attributes.m_Job != _DEF_Character_Job_TuFei){
        tinfo->showinfo(QString("你获得了%1 个金币").arg(finfo->Add_Money*500));
    }
    if(finfo->Add_shouliandu>0&& CGameSystem::Character_Info[finfo->id1-1]->m_Attributes.m_Job != _DEF_Character_Job_TuFei){
        tinfo->showinfo(QString("您的熟练度提升"));
    }
    //(int id ,int level1 , int Exp1 ,int addExp);
    if(CGameSystem::Character_Info[blueid-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei)
        m_gethit_exp->show_ui(finfo->id1,finfo->Base_level,finfo->Base_Exp,finfo->Add_Exp);
}


void gethit_hp::slot_Fightinfo(Fightinfo* Finfo,CArm* arm1 ,CArm* arm2){
    GameMap::m_gethithpEnable = 0;
    setInfo(Finfo,arm1,arm2);
    Init_ui();
    st_Fight();
}
