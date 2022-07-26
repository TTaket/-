#include "armlistitem.h"
#include "ui_ArmListItem.h"

ArmListItem::ArmListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmListItem)
{
    ui->setupUi(this);
    pArm =nullptr;

}

ArmListItem::~ArmListItem()
{
    pArm =nullptr;
    delete ui;
}
//设置选项信息
void ArmListItem::setInfo()//改为直接由指针 调用
{
    if(!pArm){
        qDebug()<<"<ArmListItem::setInfo() err";
        return;
    }
    ui->lb_armName->setText(QString::fromStdString(pArm->m_name));
    ui->lb_armIcon->setText(QString::number(pArm->m_Id,10));//Iconid != id;
    ui->lb_armFinger->setText("");
    ui->lb_armValue->setText(QString::number(pArm->m_Lastusetime,10));
}

//获取武器名字
QString ArmListItem::getArmName()
{
    return ui->lb_armName->text();
}

//显示和隐藏手指
void ArmListItem::setFingerShow(bool enable)
{
    if(enable)
    {
        ui->lb_armFinger->setText("Y");
    }
    else
    {
        ui->lb_armFinger->setText("");
    }
}

