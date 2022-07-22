#include "armchoice.h"
#include "ui_armchoice.h"

ArmChoice::ArmChoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArmChoice)
{
    ui->setupUi(this);
}

ArmChoice::~ArmChoice()
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
void ArmChoice::addItem(ActionListItem* item)
{
    m_ActionListItemVector.push_back(item);
}

void ArmChoice::deleteItemList()
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
void ArmChoice::updateList()
{
    ui->lw_armChoice->hide();

    //更新数据
    for(int i=0;i<m_ActionListItemVector.size();i++)
    {
        //往“槽”中放入item
        ui->lw_armChoice->setItemWidget(m_qListWidgetVector[i], m_ActionListItemVector[i]);
    }

    ui->lw_armChoice->show();
}

void ArmChoice::createList()
{
    //清空表项
    int n = ui->lw_armChoice->count();
    for(int i=0;i<n;i++)
    {
        ui->lw_armChoice->takeItem(0); //是0不是i
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
        ui->lw_armChoice->addItem(qItem);
        m_qListWidgetVector.push_back(qItem);

        //往“槽”中放入item
        ui->lw_armChoice->setItemWidget(qItem, m_ActionListItemVector[i]);
    }
}

//单击事件
void ArmChoice::on_lw_armChoice_itemClicked(QListWidgetItem *item)
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
void ArmChoice::on_lw_armChoice_itemDoubleClicked(QListWidgetItem *item)
{
    for(int i=0;i<m_ActionListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            QString name = m_ActionListItemVector[i]->getInfo();

            if(!strcmp(name.toStdString().c_str(),"装备"))
            {
                ;
            }
            else if(!strcmp(name.toStdString().c_str(),"交换"))
            {
                ;
            }
            else if(!strcmp(name.toStdString().c_str(),"舍去"))
            {
                ;
            }
            else
            {
                ;
            }
        }
    }
}
