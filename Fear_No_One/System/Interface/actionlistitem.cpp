#include "actionlistitem.h"
#include "ui_actionlistitem.h"

ActionListItem::ActionListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionListItem)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/actionlistitem.png"));
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
//        QPixmap img;
//        img.load()
        ui->lb_itemFinger->setText("Y");
    }
    else
    {
        //ui->lb_itemFinger->setVisible(false);
        ui->lb_itemFinger->setText("");
    }
}
