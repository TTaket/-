#include "gamechoice2item.h"
#include "ui_gamechoice2item.h"

GameChoice2Item::GameChoice2Item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoice2Item)
{
    ui->setupUi(this);

    ui->pb_gameChoiceItem_2->setStyleSheet("QPushButton{"
                                          "background:url(../Fear_No_One/Resource/Photo/board.png)"
                                          "}"
                                         );
}

GameChoice2Item::~GameChoice2Item()
{
    delete ui;
}

//设置选项信息
void GameChoice2Item::setInfo(QString name)
{
    ui->pb_gameChoiceItem_2->setText(name);
}

//重写鼠标移入事件
void GameChoice2Item::enterEvent(QEvent *e)
{
    //显示图标
    QPixmap fubiaoleft, fubiaoright;
    fubiaoleft.load("../Fear_No_One/Resource/Photo/fubiaoleft.png");
    fubiaoright.load("../Fear_No_One/Resource/Photo/fubiaoright.png");
    ui->lb_fubiao_left->setPixmap(fubiaoleft);
    ui->lb_fubiao_right->setPixmap(fubiaoright);
    ui->lb_fubiao_left->setVisible(true);
    ui->lb_fubiao_right->setVisible(true);
}

//重写鼠标移出事件
void GameChoice2Item::leaveEvent(QEvent *e)
{
    ui->lb_fubiao_left->setVisible(false);
    ui->lb_fubiao_right->setVisible(false);
}

void GameChoice2Item::on_pb_gameChoiceItem_2_clicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString btnName = btn->text();

    if(!strcmp(btnName.toStdString().c_str(), "存档1"))
    {
        Q_EMIT SIG_pb_save1();
    }
    else if(!strcmp(btnName.toStdString().c_str(), "存档2"))
    {
        Q_EMIT SIG_pb_save2();
    }
    else if(!strcmp(btnName.toStdString().c_str(), "存档3"))
    {
        Q_EMIT SIG_pb_save3();
    }
    else if(!strcmp(btnName.toStdString().c_str(), "返回上一页"))
    {
        Q_EMIT SIG_pb_return();
    }
}
