#include "tufeilist.h"
#include "ui_tufeilist.h"
#include <QDebug>

TuFeiList::TuFeiList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TuFeiList)
{
    ui->setupUi(this);

    ui->lb_tufeiListTitle->setText("请选择攻击目标");
    ui->lb_tufeiListTitle->setAlignment(Qt::AlignCenter);
    ui->lb_tufeiListTitleBackground->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png")
                                      .scaled(ui->lb_tufeiListTitleBackground->width(),
                                              ui->lb_tufeiListTitleBackground->height()));

    ui->lb_tufeiListBackground->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/actionlist.jpg")
                                          .scaled(ui->lb_tufeiListBackground->width(),
                                                  ui->lb_tufeiListBackground->height()));

    ui->lw_tufeiList->setStyleSheet("background-color:transparent");
}

TuFeiList::~TuFeiList()
{
    delete ui;
}

//添加列表项
void TuFeiList::addItem(TufeiListItem* item)
{
    m_TufeiListItemVector.push_back(item);
}

void TuFeiList::deleteItemList()
{
    for(int i=0;i<m_TufeiListItemVector.size();i++)
    {
        if(m_TufeiListItemVector[i])
        {
            delete m_TufeiListItemVector[i];
            m_TufeiListItemVector[i] = NULL;
        }
    }

    m_TufeiListItemVector.clear();
}

//更新列表
void TuFeiList::updateList()
{
    ui->lw_tufeiList->hide();

    //更新数据
    for(int i=0;i<m_TufeiListItemVector.size();i++)
    {
        //往“槽”中放入item
        ui->lw_tufeiList->setItemWidget(m_qListWidgetVector[i], m_TufeiListItemVector[i]);
    }

    ui->lw_tufeiList->show();
}

void TuFeiList::createList()
{
    //清空表项
    int n = ui->lw_tufeiList->count();
    for(int i=0;i<n;i++)
    {
        ui->lw_tufeiList->takeItem(0); //是0不是i
    }
    //删除“旧槽”
    for(int i=0;i<m_qListWidgetVector.size();i++)
    {
        if(m_qListWidgetVector[i])
        {
            delete m_qListWidgetVector[i];
            m_qListWidgetVector[i] = NULL;
        }
    }
    m_qListWidgetVector.clear();

    //添加“新槽”
    for(int i=0;i<m_TufeiListItemVector.size();i++)
    {
        //添加“槽”
        QListWidgetItem* qItem = new QListWidgetItem;
        qItem->setSizeHint(QSize(0,80));
        ui->lw_tufeiList->addItem(qItem);
        m_qListWidgetVector.push_back(qItem);

        //往“槽”中放入item
        ui->lw_tufeiList->setItemWidget(qItem, m_TufeiListItemVector[i]);
    }
}

//单击事件
void TuFeiList::on_lw_tufeiList_itemClicked(QListWidgetItem *item)
{
    //在vector中找到这个item
    for(int i=0;i<m_TufeiListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            m_TufeiListItemVector[i]->setFingerShow(true);
        }
        else
        {
            m_TufeiListItemVector[i]->setFingerShow(false);
        }
    }

    updateList();
}

//双击事件
void TuFeiList::on_lw_tufeiList_itemDoubleClicked(QListWidgetItem *item)
{
    //玩家选择要攻击的土匪后

    //1.攻击前显示双方攻击信息
    //1.1在vector中找到这个item
    for(int i=0;i<m_TufeiListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            //取出土匪id
            int tufeiId = m_TufeiListItemVector[i]->getTufeiId();
            qDebug()<<QString("选择了土匪%1号").arg(tufeiId);
//            //根据土匪id获取人物信息
//            Character *character = CGameSystem::Character_Info[tufeiId-1];
            //发送信号给gamemap，战斗前显示双方信息
            Q_EMIT SIG_attackReadyInfoShow(CGameSystem::using_peoid,CGameSystem::using_arm,tufeiId);
        }
    }
}
