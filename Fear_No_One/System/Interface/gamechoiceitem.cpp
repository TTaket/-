#include "gamechoiceitem.h"
#include "ui_gamechoiceitem.h"
#include <QDebug>

GameChoiceItem::GameChoiceItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoiceItem)
{
    ui->setupUi(this);
    ui->pb_gameChoice1Item->setStyleSheet("QPushButton{"
                                          "background:url(../Fear_No_One/Resource/Photo/board.png)"
                                          "}"
                                         );
}

GameChoiceItem::~GameChoiceItem()
{
    delete ui;
}

//设置选项信息
void GameChoiceItem::setInfo(QString name)
{
    ui->pb_gameChoice1Item->setText(name);
}

//重写鼠标移入事件
void GameChoiceItem::enterEvent(QEvent *e)
{
    //显示图标
    QPixmap fubiaoleft, fubiaoright;
    fubiaoleft.load("../Fear_No_One/Resource/Photo/fubiaoleft50.png");
    fubiaoright.load("../Fear_No_One/Resource/Photo/fubiaoright50.png");
    ui->lb_fubiaoLeft->setPixmap(fubiaoleft);
    ui->lb_fubiaoRight->setPixmap(fubiaoright);
    ui->lb_fubiaoLeft->setVisible(true);
    ui->lb_fubiaoRight->setVisible(true);
}

//重写鼠标移出事件
void GameChoiceItem::leaveEvent(QEvent *e)
{
   ui->lb_fubiaoLeft->setVisible(false);
   ui->lb_fubiaoRight->setVisible(false);
}


void GameChoiceItem::on_pb_gameChoice1Item_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString btnName = btn->text();

    if(!strcmp(btnName.toStdString().c_str(), "开始游戏"))
    {
        Q_EMIT SIG_pb_start();
    }
    else if(!strcmp(btnName.toStdString().c_str(), "继续游戏"))
    {
        Q_EMIT SIG_pb_continue();
    }
    else if(!strcmp(btnName.toStdString().c_str(), "复制记录"))
    {
        Q_EMIT SIG_pb_copy();
    }
    else if(!strcmp(btnName.toStdString().c_str(), "删除记录"))
    {
        Q_EMIT SIG_pb_delete();
    }
    else if(!strcmp(btnName.toStdString().c_str(), "返回"))
    {
        Q_EMIT SIG_pb_return();
    }
}
