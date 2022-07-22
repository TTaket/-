#include "armlistitem.h"
#include "ui_ArmListItem.h"

ArmListItem::ArmListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmListItem)
{
    ui->setupUi(this);
}

ArmListItem::~ArmListItem()
{
    delete ui;
}
//设置选项信息
void ArmListItem::setInfo(QString name, int iconId, int value)
{
    ui->lb_armName->setText(name);
    ui->lb_armIcon->setText(QString::number(iconId,10));
    ui->lb_armFinger->setText("");
    ui->lb_armValue->setText(QString::number(value,10));
}

//获取选项信息
QString ArmListItem::getInfo()
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

