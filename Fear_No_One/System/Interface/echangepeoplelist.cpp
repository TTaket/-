#include "echangepeoplelist.h"
#include "ui_echangepeoplelist.h"

EchangePeopleList::EchangePeopleList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EchangePeopleList)
{
    ui->setupUi(this);

    ui->lb_changePeopleListTitle->setText("请选择交换目标");
    ui->lb_changePeopleListTitle->setAlignment(Qt::AlignCenter);
    ui->lb_changePeopleListTitleBackground->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png")
                                      .scaled(ui->lb_changePeopleListTitleBackground->width(),
                                              ui->lb_changePeopleListTitleBackground->height()));


}

EchangePeopleList::~EchangePeopleList()
{
    delete ui;
}

//添加列表项
void EchangePeopleList::addItem(EchangePeopleListItem* item)
{
    m_ChangePeopleListItemVector.push_back(item);
}

void EchangePeopleList::deleteItemList()
{
    for(int i=0;i<m_ChangePeopleListItemVector.size();i++)
    {
        if(m_ChangePeopleListItemVector[i])
        {
            delete m_ChangePeopleListItemVector[i];
            m_ChangePeopleListItemVector[i] = NULL;
        }
    }

    m_ChangePeopleListItemVector.clear();
}

//更新列表
void EchangePeopleList::updateList()
{
    ui->lw_changePeopleList->hide();

    //更新数据
    for(int i=0;i<m_ChangePeopleListItemVector.size();i++)
    {
        //往“槽”中放入item
        ui->lw_changePeopleList->setItemWidget(m_qListWidgetVector[i], m_ChangePeopleListItemVector[i]);
    }

    ui->lw_changePeopleList->show();
}

void EchangePeopleList::createList()
{
    //清空表项
    int n = ui->lw_changePeopleList->count();
    for(int i=0;i<n;i++)
    {
        ui->lw_changePeopleList->takeItem(0); //是0不是i
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
    for(int i=0;i<m_ChangePeopleListItemVector.size();i++)
    {
        //添加“槽”
        QListWidgetItem* qItem = new QListWidgetItem;
        qItem->setSizeHint(QSize(0,80));
        ui->lw_changePeopleList->addItem(qItem);
        m_qListWidgetVector.push_back(qItem);

        //往“槽”中放入item
        ui->lw_changePeopleList->setItemWidget(qItem, m_ChangePeopleListItemVector[i]);
    }
}

//单击事件
void EchangePeopleList::on_lw_changePeopleList_itemClicked(QListWidgetItem *item)
{
    //在vector中找到这个item
    for(int i=0;i<m_ChangePeopleListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            m_ChangePeopleListItemVector[i]->setFingerShow(true);
        }
        else
        {
            m_ChangePeopleListItemVector[i]->setFingerShow(false);
        }
    }

    updateList();
}

//双击事件
void EchangePeopleList::on_lw_changePeopleList_itemDoubleClicked(QListWidgetItem *item)
{
    //玩家选择要交换武器的友方后
    //1.1在vector中找到这个item
    for(int i=0;i<m_ChangePeopleListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            //取出友方id
            int blueId = m_ChangePeopleListItemVector[i]->getBlueId();
            qDebug()<<QString("选择了友方%1号").arg(blueId);

            CGameSystem::change_exchange_peoids(CGameSystem::using_peoid, blueId);

            //发送信号给gamemap，显示双方可以交换的武器
            Q_EMIT SIG_changePeopleArmShow(CGameSystem::using_peoid, blueId);
        }
    }
}
