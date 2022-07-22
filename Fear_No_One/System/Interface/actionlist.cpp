#include "actionlist.h"
#include "ui_actionlist.h"
#include <QObject>
#include <QLabel>
#include <QDebug>

ActionList::ActionList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionList)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/actionlist.jpg"));
    ui->background->resize(this->width(),this->height());
    ui->lw_ActionItemList->setStyleSheet("background-color:transparent");
}

ActionList::~ActionList()
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
void ActionList::addItem(ActionListItem* item)
{
    m_ActionListItemVector.push_back(item);
}

void ActionList::deleteItemList()
{
    for(int i=0;i<m_ActionListItemVector.size();i++)
    {
        if(m_ActionListItemVector[i])
        {
            delete m_ActionListItemVector[i];
            m_ActionListItemVector[i] = NULL;
        }
    }

    m_ActionListItemVector.clear();
}

//更新列表
void ActionList::updateList()
{
    ui->lw_ActionItemList->hide();

    //更新数据
    for(int i=0;i<m_ActionListItemVector.size();i++)
    {
        //往“槽”中放入item
        ui->lw_ActionItemList->setItemWidget(m_qListWidgetVector[i], m_ActionListItemVector[i]);
    }

    ui->lw_ActionItemList->show();
}

void ActionList::createList()
{
    //清空表项
    int n = ui->lw_ActionItemList->count();
    for(int i=0;i<n;i++)
    {
        ui->lw_ActionItemList->takeItem(0); //是0不是i
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
    for(int i=0;i<m_ActionListItemVector.size();i++)
    {
        //添加“槽”
        QListWidgetItem* qItem = new QListWidgetItem;
        qItem->setSizeHint(QSize(0,60));
        ui->lw_ActionItemList->addItem(qItem);
        m_qListWidgetVector.push_back(qItem);

        //往“槽”中放入item
        ui->lw_ActionItemList->setItemWidget(qItem, m_ActionListItemVector[i]);
    }
}

//单击事件
void ActionList::on_lw_ActionItemList_itemClicked(QListWidgetItem *item)
{
    //在vector中找到这个item
    for(int i=0;i<m_ActionListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            m_ActionListItemVector[i]->setFingerShow(true);
        }
        else
        {
            m_ActionListItemVector[i]->setFingerShow(false);
        }
    }

    updateList();
}

//双击事件
void ActionList::on_lw_ActionItemList_itemDoubleClicked(QListWidgetItem *item)
{
    for(int i=0;i<m_ActionListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            QString name = m_ActionListItemVector[i]->getInfo();
            Q_EMIT SIG_action(name);
        }
    }
}
