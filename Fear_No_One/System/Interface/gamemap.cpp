#include "gamemap.h"
#include "ui_gamemap.h"
#include "Character.h"
#include "Arms.h"
#include "Map.h"
#include <QDebug>

GameMap::GameMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameMap),
    m_peopleHpInfo(NULL),
    m_groundTypeInfo(NULL),
    m_actionList(NULL),
    m_armList(NULL),
    m_armInfo(NULL),
    m_armChoice(NULL)
{
    ui->setupUi(this);


    //创建控件
    m_peopleHpInfo = new PeopleHpInfo(this); //括号里指定父窗口
    m_groundTypeInfo = new GroundTypeInfo(this);
    m_actionList = new ActionList(this);
    QObject::connect(m_actionList,
                     SIGNAL(SIG_updateList()),
                     this,
                     SLOT(slot_updateList()));
    QObject::connect(m_actionList,
                     SIGNAL(SIG_action(QString)),
                     this,
                     SLOT(slot_action(QString)));



    m_armList = new ArmList(this);
    QObject::connect(m_armList,
                     SIGNAL(SIG_armInfoShow(QString)),
                     this,
                     SLOT(slot_armInfoShow(QString)));
    QObject::connect(m_armList,
                     SIGNAL(SIG_armChoice()),
                     this,
                     SLOT(slot_armChoice()));

    m_armInfo = new ArmInfo(this);

    m_armChoice = new ArmChoice(this);

    //控件处理
    m_peopleHpInfo->setGeometry(700,0,200,80);
    m_groundTypeInfo->setGeometry(700,520,200,80);

    m_actionList->deleteItemList();
    m_actionList->hide(); //hide表示子控件在父窗口消失，不占用父窗口空间
    m_actionList->setGeometry(0,0,200,300);

    m_armList->deleteItemList();
    m_armList->hide();
    m_armList->setGeometry(0,0,320,240);

    m_armInfo->hide();
    m_armInfo->setGeometry(350,240,280,270);

    m_armChoice->hide();
    m_armChoice->setGeometry(350,0,200,160);
    m_armChoice->deleteItemList();
    ActionListItem* item1 = new ActionListItem;
    item1->setInfo("装备");
    m_armChoice->addItem(item1);
    ActionListItem* item2 = new ActionListItem;
    item2->setInfo("交换");
    m_armChoice->addItem(item2);
    ActionListItem* item3 = new ActionListItem;
    item3->setInfo("舍去");
    m_armChoice->addItem(item3);
    m_armChoice->createList();

    //显示控件
    m_peopleHpInfo->show();
    m_groundTypeInfo->show();

    //鼠标捕获
    setMouseTracking(true);
}

GameMap::~GameMap()
{
    delete ui;
    if(m_peopleHpInfo)
    {
        delete m_peopleHpInfo;
        m_peopleHpInfo = NULL;
    }
    if(m_groundTypeInfo)
    {
        delete m_groundTypeInfo;
        m_groundTypeInfo = NULL;
    }
    if(m_actionList)
    {
        delete m_actionList;
        m_actionList = NULL;
    }
    if(m_armList)
    {
        delete m_armList;
        m_armList = NULL;
    }
    if(m_armInfo)
    {
        delete m_armInfo;
        m_armInfo = NULL;
    }
    if(m_armChoice)
    {
        delete m_armChoice;
        m_armChoice = NULL;
    }
}

//更新地图
void GameMap::updateMap()
{
    update(); //发送绘图事件，更新绘图
}


//绘制地图
void GameMap::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    //painter.begin(this);
    drawPixmap(&painter);
    //painter.end();
};
void GameMap::drawPixmap(QPainter *painter){
    painter->save();

    QImage image;
    switch (CGameSystem::Checkpoint) {
        case 1:
            image.load("../Fear_No_One/Resource/Map/Map_Resource-01.png");
            break;
        case 2:
            image.load("../Fear_No_One/Resource/Map/Map_Resource-02.png");
            break;
        case 3:
            image.load("../Fear_No_One/Resource/Map/Map_Resource-03.png");
            break;
    default:
        qDebug()<<"error : 绘图";
        break;
    }
    painter->drawImage(0, 0, image);

    //根据人物坐标贴图
    painter->setWindow(0, this->height(), this->width(), -(this->height()));
    //1.获取地图二维数组
    CGround_Map* groundMap = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1];

    if(groundMap)
    {
        //2.遍历二维数组进行贴图
        int i,j;
        int x,y;
        int scaled_width, scaled_height;

        for(i=1;i<=groundMap->m_MapXmax;i++)
        {
            for(j=1;j<=groundMap->m_MapYmax;j++)
            {
                if(groundMap->m_Peopleid[i][j] == 1) //罗伊
                {
                    //qDebug()<<"罗伊";
                    image.load("../Fear_No_One/Resource/Character/Map_basic/zhujue/03.png");
                    scaled_width = this->width()/groundMap->m_MapXmax;
                    scaled_height = this->height()/groundMap->m_MapYmax;
                    image = image.mirrored(true, true);
                    image.scaled(scaled_width, scaled_height);
                    x = this->width() / groundMap->m_MapXmax * (i-1) ;
                    y = this->height() / groundMap->m_MapYmax * (j-1);
                    painter->drawImage(x, y, image);
                }
                else if(groundMap->m_Peopleid[i][j] == 2) //李清
                {
                    //qDebug()<<"李清";
                    image.load("../Fear_No_One/Resource/Character/Map_basic/qingqi/03.png");
                    scaled_width = this->width()/groundMap->m_MapXmax;
                    scaled_height = this->height()/groundMap->m_MapYmax;
                    image = image.mirrored(true, true);
                    image.scaled(scaled_width, scaled_height);
                    x = this->width() / groundMap->m_MapXmax * (i-1) ;
                    y = this->height() / groundMap->m_MapYmax * (j-1);
                    painter->drawImage(x, y, image);
                }
                else if(groundMap->m_Peopleid[i][j] == 3) //皮古
                {
                    //qDebug()<<"皮古";
                    image.load("../Fear_No_One/Resource/Character/Map_basic/zhongqi/03.png");
                    scaled_width = this->width()/groundMap->m_MapXmax;
                    scaled_height = this->height()/groundMap->m_MapYmax;
                    image = image.mirrored(true, true);
                    image.scaled(scaled_width, scaled_height);
                    x = this->width() / groundMap->m_MapXmax * (i-1) ;
                    y = this->height() / groundMap->m_MapYmax * (j-1);
                    painter->drawImage(x, y, image);
                }
            }
        }
    }

    painter->restore();
};
//鼠标捕获
void GameMap::mouseMoveEvent(QMouseEvent *event)
{
    //QPoint po = QMouseEvent::pos();
}


//测试按钮
void GameMap::on_pb_test_clicked()
{
    m_actionList->hide();
    m_armList->hide();

    m_actionList->deleteItemList();

    //根据人物id获取行动列表
    //int id = CGameSystem::using_peoid;
    int id=1;
    std::list<int> actionList = CGameSystem::Action(id);
    qDebug()<<"cur peoid="<<id;

    //遍历行动列表显示在ui上
    for(auto ite = actionList.begin(); ite!= actionList.end(); ite++)
    {
        ActionListItem* item = new ActionListItem;

        if(*ite == _DEF_Action_ATK)
        {
            item->setInfo("攻击");
        }
        else if(*ite == _DEF_Action_Treat)
        {
            item->setInfo("治疗");
        }
        else if(*ite == _DEF_Action_Thing)
        {
            item->setInfo("物品");
        }
        else if(*ite == _DEF_Action_GroundFun)
        {
            item->setInfo("交互");
        }
        else if(*ite == _DEF_Action_Exchange)
        {
            item->setInfo("交换");
        }
        m_actionList->addItem(item);
    }

    m_actionList->createList();
    m_actionList->show();

}

//更新列表
void GameMap::slot_updateList()
{
    m_actionList->updateList();
}

//动作信号处理
void GameMap::slot_action(QString actionName)
{
    if(!strcmp(actionName.toStdString().c_str(), "攻击"))
    {
        //隐藏行动列表
        m_actionList->hide();
        m_armList->hide();

        m_armList->deleteItemList();

        //显示武器列表
        //1.获取人物信息
        int id = 1;
        Character *character = CGameSystem::Character_Info[id-1];
        //std::list<CArm*>::iterator ite;
        //2.从武器链表中获取武器信息
        for(auto ite = character->Armslist.begin(); ite != character->Armslist.end(); ite++)
        {
            ArmListItem* armItem = new ArmListItem;
            armItem->setInfo(QString::fromStdString((*ite)->m_name),(*ite)->m_Id, (*ite)->m_Lastusetime);
            m_armList->addItem(armItem);
        }
        //2.显示
        m_armList->createList();
        m_armList->show();

    }
    else if(!strcmp(actionName.toStdString().c_str(), "治疗"))
    {
        ;
    }
    else if(!strcmp(actionName.toStdString().c_str(), "物品"))
    {
        //隐藏行动列表
        m_actionList->hide();
        m_armList->hide();

        m_armList->deleteItemList();

        //显示武器列表
        //1.获取人物信息
        int id = 1;
        Character *character = CGameSystem::Character_Info[id-1];
        //std::list<CArm*>::iterator ite;
        //2.从武器链表中获取武器信息
        for(auto ite = character->Armslist.begin(); ite != character->Armslist.end(); ite++)
        {
            ArmListItem* armItem = new ArmListItem;
            armItem->setInfo(QString::fromStdString((*ite)->m_name),(*ite)->m_Id, (*ite)->m_Lastusetime);
            m_armList->addItem(armItem);
        }
        //2.显示
        m_armList->createList();
        m_armList->show();
    }
    else if(!strcmp(actionName.toStdString().c_str(), "交互"))
    {
        ;
    }
    else if(!strcmp(actionName.toStdString().c_str(), "交换"))
    {
        ;
    }
}

//武器信息显示槽函数
void GameMap::slot_armInfoShow(QString armName)
{
    qDebug()<<"aabb";
    qDebug()<<armName;
    //获取当前人物信息
    int id=1;
    Character *character = CGameSystem::Character_Info[id-1];
    //2.从武器链表中获取武器信息
    for(auto ite = character->Armslist.begin(); ite != character->Armslist.end(); ite++)
    {
        if(!strcmp((*ite)->m_name.c_str(), armName.toStdString().c_str()))
        {
            //显示武器信息
            m_armInfo->setArmInfo(*ite);
            m_armInfo->show();
        }
    }
}

//武器选择信息（装备，交换，舍去）信号槽函数
void GameMap::slot_armChoice()
{
    m_armChoice->show();
}


