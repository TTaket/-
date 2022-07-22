#include "peoplehpinfo.h"
#include "ui_peoplehpinfo.h"

PeopleHpInfo::PeopleHpInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeopleHpInfo)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png"));
    people_id = 0;

}

PeopleHpInfo::~PeopleHpInfo()
{
    delete ui;
}

void PeopleHpInfo::setInfo(){//设置信息
        if(people_id == 0){
            ui->lb_hpIcon->clear();
            ui->lb_hpValue->setText("NULL");
            ui->lb_hpName->setText("No Peo");
            ui->lb_levelval->setText("NULL");
        }
        else{
        QPixmap pixmap = CGameSystem::Character_Info[people_id-1]->m_iconPos;
        pixmap.scaled(ui->lb_hpIcon->size(), Qt::KeepAspectRatio);
        ui->lb_hpIcon->setScaledContents(true);
        ui->lb_hpIcon->setPixmap(pixmap);
        ui->lb_hpName->setText(QString::fromStdString( CGameSystem::Character_Info[people_id-1]->m_name));
        ui->lb_hpValue->setText(QString("%1/%2").arg(CGameSystem::Character_Info[people_id-1]->m_Attributes.m_HpNow).arg(CGameSystem::Character_Info[people_id-1]->m_Attributes.m_HpMax));
        ui->lb_levelval->setText(QString::number(CGameSystem::Character_Info[people_id-1]->m_Attributes.m_Level));
        }
}
