#include "armlist.h"
#include "ui_ArmList.h"
#include <QDebug>

ArmList::ArmList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmList)
{
    ui->setupUi(this);
}

ArmList::~ArmList()
{
    delete ui;

    deleteItemList();

    QListWidgetItem* qItem = NULL;
    for(int i=0; i<m_qListWidgetVector.size();i++)
    {
        qItem = m_qListWidgetVector[i];
        if(qItem)
        {
            delete qItem;
            qItem = NULL;
        }
    }

    m_qListWidgetVector.clear();
}

//添加列表项
void ArmList::addItem(ArmListItem* item)
{
    m_armListItemVector.push_back(item);
}

void ArmList::deleteItemList()
{
    for(int i=0;i<m_armListItemVector.size();i++)
    {
        if(m_armListItemVector[i])
        {
            delete m_armListItemVector[i];
            m_armListItemVector[i] = NULL;
        }
    }

    m_armListItemVector.clear();
}

//更新列表
void ArmList::updateList()
{
    ui->lw_armList->hide();

    //更新数据
    qDebug()<<m_armListItemVector.size();
    for(int i=0;i<m_armListItemVector.size();i++)
    {
        //往“槽”中放入item
        ui->lw_armList->setItemWidget(m_qListWidgetVector[i], m_armListItemVector[i]);
    }

    ui->lw_armList->show();
}

void ArmList::createList()
{
    //清空表项
    int n = ui->lw_armList->count();
    for(int i=0;i<n;i++)
    {
        ui->lw_armList->takeItem(0); //是0不是i
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
    qDebug()<<m_armListItemVector.size();
    for(int i=0;i<m_armListItemVector.size();i++)
    {
        //添加“槽”
        QListWidgetItem* qItem = new QListWidgetItem;
        qItem->setSizeHint(QSize(0,60));
        ui->lw_armList->addItem(qItem);
        m_qListWidgetVector.push_back(qItem);

        //往“槽”中放入item
        ui->lw_armList->setItemWidget(qItem, m_armListItemVector[i]);
    }
}

//单击选择
void ArmList::on_lw_armList_itemClicked(QListWidgetItem *item)
{
    QString armName;

    //在vector中找到这个item
    qDebug()<<m_armListItemVector.size();
    for(int i=0;i<m_armListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            m_armListItemVector[i]->setFingerShow(true);
        }
        else
        {
            m_armListItemVector[i]->setFingerShow(false);
        }
    }

    updateList();

    Q_EMIT SIG_armInfoShow(armName);
}

//双击选择
void ArmList::on_lw_armList_itemDoubleClicked(QListWidgetItem *item)
{
    Q_EMIT SIG_armChoice();
}
