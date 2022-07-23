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
    //this->setCursor(Qt::BlankCursor);   //隐藏鼠标
    //this->setCursor(Qt::ArrowCursor);  //显示正常鼠标
    //阻止随便控制键盘
    key_controlAble = 0;
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
    drawPixmap(&painter);
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

    painter->setWindow(0, this->height(), this->width(), -(this->height()));


    //根据鼠标位置获得相对坐标
    int Mouse_pos_relativelyX = CGameSystem::Mouse_X/60+1;
    int Mouse_pos_relativelyY = (CGameSystem::Sys_Window_Height - CGameSystem::Mouse_Y)/60+1;


    //显示控件peopleHpInfo 和 GroundTypeInfo
    int tmppeople_id  = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[Mouse_pos_relativelyX][Mouse_pos_relativelyY];

    if(tmppeople_id == 0){
        m_peopleHpInfo->people_id = 0;
    }else if(CGameSystem::Character_Info[tmppeople_id -1]->m_Islive){
        m_peopleHpInfo->people_id = tmppeople_id;
    }


    m_groundTypeInfo->ground_id  = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[Mouse_pos_relativelyX][Mouse_pos_relativelyY];
    m_peopleHpInfo->setInfo();//更新数据
    m_groundTypeInfo->setInfo();//更新数据
    if(CGameSystem::Mouse_X >= CGameSystem::Sys_Window_width/2){
            m_peopleHpInfo->move(0,0);
            if(m_peopleHpInfo->people_id>0){
                m_peopleHpInfo->show();
            }
            m_groundTypeInfo->move(0,CGameSystem::Sys_Window_Height-m_peopleHpInfo->height());
            if(m_groundTypeInfo->ground_id>0){
                m_groundTypeInfo->show();
            }
    }else{
            m_peopleHpInfo->move(CGameSystem::Sys_Window_width-m_peopleHpInfo->width(),0);
            if(m_peopleHpInfo->people_id>0){
                m_peopleHpInfo->show();
            }
            m_groundTypeInfo->move(CGameSystem::Sys_Window_width-m_peopleHpInfo->width(),CGameSystem::Sys_Window_Height-m_peopleHpInfo->height());
            if(m_groundTypeInfo->ground_id>0){
                m_groundTypeInfo->show();
            }
    }


    //这里有问题，光标没有随着鼠标移动
    //贴光标
    //友军贴光标3
    //地面贴光标2
    //敌军贴光标1
    if(key_controlAble == 0){
        if(tmppeople_id == 0 || !(CGameSystem::Character_Info[tmppeople_id -1]->m_Islive)){//地面
            //qDebug()<<"地面";
            image.load("../Fear_No_One/Resource/Photo/gb(2).png");

        }else if(CGameSystem::Character_Info[tmppeople_id -1]->m_Attributes.m_Job == _DEF_Character_Job_TuFei){
            //qDebug()<<"土匪";
            image.load("../Fear_No_One/Resource/Photo/gb(1).png");
        }else{
            //qDebug()<<"友军";
            image.load("../Fear_No_One/Resource/Photo/gb(3).png");
        }
        //qDebug()<<"(Mouse_pos_relativelyX-1)*60 : "<< (Mouse_pos_relativelyX-1)*60;
        //qDebug()<<"(Mouse_pos_relativelyY-1)*60 : "<< (Mouse_pos_relativelyY-1)*60;
        painter->drawImage((Mouse_pos_relativelyX-1)*60, (Mouse_pos_relativelyY-1)*60, image);
    }else{
         image.load("../Fear_No_One/Resource/Photo/gb(4).png");
         painter->drawImage((CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX-1)*60, (CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY-1)*60, image);
    }

    //根据人物坐标贴图
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
                  if(groundMap->m_Peopleid[i][j] !=0 && CGameSystem::Character_Info[groundMap->m_Peopleid[i][j]-1]->m_Islive){
                      image.load(CGameSystem::Character_Info[groundMap->m_Peopleid[i][j]-1]->m_MappicPos[0][0]);
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
        //3.遍历二维数组进行地图贴图

        for(i=1;i<=groundMap->m_MapXmax;i++)
        {
            for(j=1;j<=groundMap->m_MapYmax;j++)
            {
                  if(groundMap->m_Color [i][j] !=0){
                      if(groundMap->m_Color [i][j] == _DEF_COLOR_GROUND_BLUE)
                        image.load("../Fear_No_One/Resource/Photo/Move_blue.png");
                      if(groundMap->m_Color [i][j] == _DEF_COLOR_GROUND_RED)
                        image.load("../Fear_No_One/Resource/Photo/Move_red.png");
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
//-----------------金光闪闪得李晶洋工作区域 ！！！！----------------------
//---------------------
//---------------------
//---------------------1.重写鼠标移动 不断刷新 地皮信息和人物信息（左右双位置）
//---------------------2.重写点击事件 获取人物id 获取点击位置的可移动链表
//---------------------3.绘制链表
//---------------------4.不断移动并且更新后台数据
//---------------------5.调出功能链表
//---------------------6.


//鼠标捕获
void GameMap::mouseMoveEvent(QMouseEvent *event)
{
    CGameSystem::Mouse_X = event->x();
    CGameSystem::Mouse_Y = event->y();
    qDebug()<<"鼠标X的位置" << CGameSystem::Mouse_X;
    qDebug()<<"鼠标Y的位置" << CGameSystem::Mouse_Y;
    //test1 获取成功

    updateMap();
}

//单点显示显示可行走范围

void GameMap::mousePressEvent(QMouseEvent *event){
    //根据鼠标位置获得相对坐标
    int Mouse_pos_relativelyX = CGameSystem::Mouse_X/60+1;
    int Mouse_pos_relativelyY = (CGameSystem::Sys_Window_Height - CGameSystem::Mouse_Y)/60+1;

    qDebug()<<"单击：鼠标X的相对位置" << Mouse_pos_relativelyX;
    qDebug()<<"单击：鼠标Y的相对位置" << Mouse_pos_relativelyY;

    int tmppeople_id  = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[Mouse_pos_relativelyX][Mouse_pos_relativelyY];
    if(!tmppeople_id || !CGameSystem::Character_Info[tmppeople_id -1]->m_Islive ||CGameSystem::Character_Info[tmppeople_id -1]->m_Attributes.m_Job == _DEF_Character_Job_TuFei )  {//特例退出
        return;
    }
    CGameSystem::change_using_peoid(tmppeople_id);
    //获取颜色
    std::list<MoveInfo*> up_color = CGameSystem::Able_UsedtoMove(tmppeople_id);
    qDebug()<< QString::fromStdString(CGameSystem::Character_Info[tmppeople_id-1]->m_name);
    //更新颜色并回收
    for(auto it = up_color.begin();it !=up_color.end();it++){
        qDebug()<<"x : " << (*it)->x << "-   y : " << (*it)->y << " 地图颜色更新";
        qDebug()<<"step : " << (*it)->step ;
        CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[(*it)->x][(*it)->y] = (*it)->color;
        delete (*it);
    }
    up_color.clear();
    updateMap();
    //移动事件
    Xreset = CGameSystem::Mouse_X/60+1;//设置复位值
    Yreset = (CGameSystem::Sys_Window_Height - CGameSystem::Mouse_Y)/60+1;//设置复位值
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);//先禁用鼠标
    key_controlAble = 1;//允许键盘控制/启动键盘控制


    }




//键盘的控制
void GameMap::keyPressEvent(QKeyEvent *event){
     if(!key_controlAble){
         return;
     }

     int op = event->key();
     qDebug()<<"收到键盘信号 : " << op;
     switch(op){
            case Qt::Key_W:
             qDebug("The key you Pressed is : ↑ \n");
             CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
             if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY <CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY+1] == _DEF_COLOR_GROUND_BLUE)
                 CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY++;
             CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
             updateMap();
             break;
          case Qt::Key_S:
             qDebug("The key you Pressed is : ↓ \n");
             CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
             if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY >0 && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY-1] == _DEF_COLOR_GROUND_BLUE)
                 CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY--;
             CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
             updateMap();
             break;
          case Qt::Key_A:
             qDebug("The key you Pressed is : ← \n");
             CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
             if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX >0  && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX-1][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] == _DEF_COLOR_GROUND_BLUE)
                 CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX--;
             CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
             updateMap();
             break;
          case Qt::Key_D:
             qDebug("The key you Pressed is : → \n");
             CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
             if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX <CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX+1][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] == _DEF_COLOR_GROUND_BLUE)
                 CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX++;
             CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
             updateMap();
             break;
          case Qt::Key_Enter:{
             qDebug("The key you Pressed is : Enter \n");
             //TODO: 调用行动函数;
             //清除色层
             memset(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color , 0 , sizeof CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color);
             updateMap();
             Xreset = 0,Yreset = 0;//清空移动重设;
             CGameSystem::change_using_peoid(0);
             this->setAttribute(Qt::WA_TransparentForMouseEvents, false);//回复鼠标;
             key_controlAble = 0;//结束控制
             break;
            }
         case Qt::Key_Escape://esc
            qDebug("The key you Pressed is : ESC \n");
            if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX != Xreset || CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY != Yreset){//非原点esc 就是 回到原点
                CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
                CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX = Xreset;
                CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY = Yreset;
                CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
                updateMap();
            }else{//在原点esc 就是 退出控制
                //清除色层
                memset(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color , 0 , sizeof CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color);
                updateMap();
                Xreset = 0,Yreset = 0;//清空移动重设;
                CGameSystem::change_using_peoid(0);
                this->setAttribute(Qt::WA_TransparentForMouseEvents, false);//回复鼠标;
                key_controlAble = 0;//结束控制
            }

            break;
        default:
            qDebug("键盘匹配失败");
            break;
         updateMap();
     }
}

//---------------------
//---------------------
//---------------------
//-------------------------------------------------------------------
//测试按钮
void GameMap::on_pb_test_clicked()
{
    m_actionList->hide();
    m_armList->hide();
    m_armInfo->hide();
    m_armChoice->hide();

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

    m_armChoice->show();
}


