#include "echangearmlist.h"
#include "ui_echangearmlist.h"

EchangeArmList::EchangeArmList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EchangeArmList)
{
    ui->setupUi(this);
}

EchangeArmList::~EchangeArmList()
{
    delete ui;
}

void EchangeArmList::setInfo(int id)
{
    //根据id获取人物信息
    m_id= id;
    Character *character = CGameSystem::Character_Info[id-1];

    //名字
    ui->lb_blueName->setText(QString::fromStdString(character->m_name));
    //头像
    QPixmap pixmap = CGameSystem::Character_Info[id-1]->m_iconPos;
    pixmap.scaled(ui->lb_blueIcon->size(), Qt::KeepAspectRatio);
    ui->lb_blueIcon->setScaledContents(true);
    ui->lb_blueIcon->setPixmap(pixmap);

    //构造武器列表
    //获取可使用的武器
    std::list<CArm*> armList = character->Armslist;
    //2.从武器链表中获取武器信息
    for(auto ite = armList.begin(); ite != armList.end(); ite++)
    {
            ArmListItem* armItem = new ArmListItem;
            armItem->pArm = (*ite);//把指针存到ArmListItem里面;
            armItem->m_peoid = id;
            armItem->setInfo();
            addItem(armItem);
    }
    createList();
}

//添加列表项
void EchangeArmList::addItem(ArmListItem* item)
{
    m_armListItemVector.push_back(item);
}

void EchangeArmList::deleteItemList()
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
void EchangeArmList::updateList()
{
    ui->lw_blueArmList->hide();

    //更新数据
    qDebug()<<m_armListItemVector.size();
    for(int i=0;i<m_armListItemVector.size();i++)
    {
        //往“槽”中放入item
        ui->lw_blueArmList->setItemWidget(m_qListWidgetVector[i], m_armListItemVector[i]);
    }

    ui->lw_blueArmList->show();
}

void EchangeArmList::createList()
{
    //清空表项
    int n = ui->lw_blueArmList->count();
    for(int i=0;i<n;i++)
    {
        ui->lw_blueArmList->takeItem(0); //是0不是i
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
        ui->lw_blueArmList->addItem(qItem);
        m_qListWidgetVector.push_back(qItem);

        //往“槽”中放入item
        ui->lw_blueArmList->setItemWidget(qItem, m_armListItemVector[i]);
    }
}

//单击事件
void EchangeArmList::on_lw_blueArmList_itemClicked(QListWidgetItem *item)
{
    CArm * ArmNow = nullptr;

    //在vector中找到这个item
    for(int i=0;i<m_armListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            m_armListItemVector[i]->setFingerShow(true);
            ArmNow = m_armListItemVector[i]->pArm;
        }
        else
        {
            m_armListItemVector[i]->setFingerShow(false);
        }
    }

    updateList();
}

//双击事件
void EchangeArmList::on_lw_blueArmList_itemDoubleClicked(QListWidgetItem *item)
{
    CArm * ArmNow = nullptr;
    int peoidNow;
    //在vector中找到这个item
    for(int i=0;i<m_armListItemVector.size();i++)
    {
        if(item == m_qListWidgetVector[i])
        {
            ArmNow = m_armListItemVector[i]->pArm;
            peoidNow = m_armListItemVector[i]->m_peoid;
        }
    }
    qDebug()<<"选择的武器："<< QString::fromStdString(ArmNow->m_name);

    //当前id是人物1的id，则和人物2交换武器
    if(peoidNow == CGameSystem::exchangePeoid1)
    {
        qDebug()<<"aaaaaaaaaaaaaa";
        CGameSystem::Arm_exchange(peoidNow, ArmNow, CGameSystem::exchangePeoid2);
        Q_EMIT SIG_changePeopleArmShow(peoidNow, CGameSystem::exchangePeoid2);
    }
    else if(peoidNow == CGameSystem::exchangePeoid2)//当前id是人物2的id，则和人物1交换武器
    {
        qDebug()<<"bbbbbbbbbbb";
        CGameSystem::Arm_exchange(peoidNow, ArmNow, CGameSystem::exchangePeoid1);
        Q_EMIT SIG_changePeopleArmShow(CGameSystem::exchangePeoid1, peoidNow);
    }
}
