#include "groundtypeinfo.h"
#include "ui_groundtypeinfo.h"

GroundTypeInfo::GroundTypeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroundTypeInfo)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png"));
    ground_id = 0;
}
GroundTypeInfo::~GroundTypeInfo()
{
    delete ui;
}
void GroundTypeInfo::setInfo(){//更新信息
    if(ground_id==0){

    }else{
        ui->lb_groundType->setText(QString::fromStdString(CGameSystem::Ground_Info[ground_id-1]->m_name));
        ui->lb_able_moveval->setText(CGameSystem::Ground_Info[ground_id-1]->m_ablewalk?"可到达":"不可到达");//是否可移动到
        if(CGameSystem::Ground_Info[ground_id-1]->m_ablewalk){//地皮的移动难度
            ui->lb_moveval->setText(QString().number(CGameSystem::Ground_Info[ground_id-1]->m_Move));
        }else{
            ui->lb_moveval->setText("不可到达");
        }
    }
}
