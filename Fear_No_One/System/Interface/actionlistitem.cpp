#include "actionlistitem.h"
#include "ui_actionlistitem.h"

ActionListItem::ActionListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionListItem)
{
    ui->setupUi(this);
}

ActionListItem::~ActionListItem()
{
    delete ui;
}

//设置选项信息
void ActionListItem::setInfo(QString name)
{
    ui->lb_itemName->setText(name);
    ui->lb_itemFinger->setText("");
}

//获取选项信息
QString ActionListItem::getInfo()
{
    return ui->lb_itemName->text();
}

//显示和隐藏手指
void ActionListItem::setFingerShow(bool enable)
{
    if(enable)
    {
        ui->lb_itemFinger->setText("Y");
    }
    else
    {
        ui->lb_itemFinger->setText("");
    }
}
