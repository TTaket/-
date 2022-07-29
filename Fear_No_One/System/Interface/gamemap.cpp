#include "gamemap.h"
#include "ui_gamemap.h"
#include "Character.h"
#include "Arms.h"
#include "Map.h"
#include <QMessageBox>
#include <iostream>
#include <QDebug>

bool GameMap::m_actionListEnable          =0;
bool GameMap::m_armListEnable             =0;
bool GameMap::m_armInfoEnable             =0;
bool GameMap::m_tufeiListEnable           =0;
bool GameMap::m_attackReadyInfoEnable     =0;
bool GameMap::m_gethithpEnable            =0;
bool GameMap::m_echangePeopleListEnable   =0;
bool GameMap::m_echangeArmListEnable      =0;
bool GameMap::m_shangyaoEnable            =0;
bool GameMap::m_FunctionlistEnable        =0;

GameMap::GameMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameMap),
    m_peopleHpInfo(NULL),
    m_groundTypeInfo(NULL),
    m_actionList(NULL),
    m_armList(NULL),
    m_armInfo(NULL),
    m_tufeiList(NULL),
    m_attackReadyInfo(NULL),
    m_echangePeopleList(NULL),
    m_echangeArmList1(NULL),
    m_echangeArmList2(NULL),
    m_Functionlist(NULL),
    timer(nullptr),
    TimeId(0),
    m_shangyao(NULL)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
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
                     SIGNAL(SIG_armInfoShow(CArm*)),
                     this,
                     SLOT(slot_armInfoShow(CArm*)));
    QObject::connect(m_armList,
                     SIGNAL(SIG_armChoice(CArm*)),
                     this,
                     SLOT(slot_armChoice(CArm*)));

    m_armInfo = new ArmInfo(this);

    m_tufeiList = new TuFeiList(this);
    QObject::connect(m_tufeiList,
                     SIGNAL(SIG_attackReadyInfoShow(int,CArm*,int)),
                     this,
                     SLOT(slot_attackReadyInfoShow(int,CArm*,int)));

    m_attackReadyInfo = new AttackReadyInfo(this);
    m_gethithp = new gethit_hp(this);

    QObject::connect(m_attackReadyInfo,
                     SIGNAL(SIG_Fightinfo(Fightinfo*,CArm*,CArm*)),
                     m_gethithp,
                     SLOT(slot_Fightinfo(Fightinfo*,CArm*,CArm*)));



    m_echangePeopleList = new EchangePeopleList(this);
    QObject::connect(m_echangePeopleList,
                     SIGNAL(SIG_changePeopleArmShow(int,int)),
                     this,
                     SLOT(slot_changePeopleArmShow(int,int)));
    m_echangeArmList1 = new EchangeArmList(this);
    QObject::connect(m_echangeArmList1,
                     SIGNAL(SIG_changePeopleArmShow(int,int)),
                     this,
                     SLOT(slot_changePeopleArmShow(int,int)));
    m_echangeArmList2 = new EchangeArmList(this);
    QObject::connect(m_echangeArmList2,
                     SIGNAL(SIG_changePeopleArmShow(int,int)),
                     this,
                     SLOT(slot_changePeopleArmShow(int,int)));

    m_shangyao = new ShangYao(this);
    QObject::connect(m_shangyao,
                     SIGNAL(SIG_useShangYao(bool)),
                     this,
                     SLOT(slot_useShangYao(bool)));

    m_Functionlist = new Functionlist(this);
    QObject::connect(m_Functionlist,
                     SIGNAL(ST_RedWork()),
                     this,
                     SLOT(RedWork()));


    timer = new QTimer(this);
    QObject::connect(timer,
                     SIGNAL(timeout()),
                     this,
                     SLOT(slot_timeadd()));
    timer->start(250);//开始运行



    m_tool_info = new Tool_Info;

    //控件处理
    m_peopleHpInfo->setGeometry(700,0,200,80);
    m_groundTypeInfo->setGeometry(700,520,200,80);

    m_actionList->hide(); //hide表示子控件在父窗口消失，不占用父窗口空间
    m_actionListEnable = false;
    m_actionList->setGeometry(0,0,200,300);

    m_armList->hide();
    m_armListEnable = false;
    m_armList->setGeometry(0,0,320,240);

    m_armInfo->hide();
    m_armInfoEnable = false;
    m_armInfo->setGeometry(620,320,280,270);

    m_attackReadyInfo->hide();
    m_attackReadyInfoEnable = false;

    m_tufeiList->hide();
    m_tufeiListEnable = false;
    m_tufeiList->setGeometry(630,0,270,400);

    m_gethithp->hide();
    m_gethithpEnable = false;
    m_gethithp->setGeometry(50,200,800,200);


    m_echangePeopleList->hide();
    m_echangePeopleListEnable = false;
    m_echangePeopleList->setGeometry(630,0,270,400);

    m_echangeArmList1->hide();
    m_echangeArmList2->hide();
    m_echangeArmListEnable = false;
    m_echangeArmList1->setGeometry(0,0,m_echangeArmList1->width(), m_echangeArmList1->height());
    m_echangeArmList2->setGeometry(580,0,m_echangeArmList2->width(), m_echangeArmList2->height());

    m_shangyao->hide();
    m_shangyaoEnable = false;
    m_shangyao->setGeometry(320,0, m_shangyao->width(), m_shangyao->height());


    m_Functionlist->hide();
    m_FunctionlistEnable = false;
    m_Functionlist->setGeometry(750,0, m_Functionlist->width(), m_Functionlist->height());
    //鼠标捕获
    setMouseTracking(true);
    //开启时间片

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
    if(m_attackReadyInfo)
    {
        delete m_attackReadyInfo;
        m_attackReadyInfo = NULL;
    }
    if(m_tufeiList)
    {
        delete m_tufeiList;
        m_tufeiList = NULL;
    }
    if(m_gethithp)
    {
        delete m_gethithp;
        m_gethithp = NULL;
    }

    if(m_echangePeopleList)
    {
        delete m_echangePeopleList;
        m_echangePeopleList = NULL;
    }
    if(m_echangeArmList1)
    {
        delete m_echangeArmList1;
        m_echangeArmList1 = NULL;
    }
    if(m_echangeArmList2)
    {
        delete m_echangeArmList2;
        m_echangeArmList2 = NULL;
    }
    if(m_shangyao)
    {
        delete m_shangyao;
        m_shangyao = NULL;
    }
    if(m_Functionlist)
    {
        delete m_Functionlist;
        m_Functionlist = NULL;
    }
}

//时间片运行
void GameMap::slot_timeadd(){
    TimeId++;
    updateMap();
    QCoreApplication::processEvents();//保证完整的show
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



    int tmppeople_id  = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[Mouse_pos_relativelyX][Mouse_pos_relativelyY];

    if(tmppeople_id == 0){
        m_peopleHpInfo->people_id = 0;
    }else if(CGameSystem::Character_Info[tmppeople_id -1]->m_Islive){
        m_peopleHpInfo->people_id = tmppeople_id;
    }



    //显示控件peopleHpInfo 和 GroundTypeInfo
    if(!m_actionListEnable && !m_armListEnable && !m_armInfoEnable
            && !m_tufeiListEnable && !m_attackReadyInfoEnable && !m_gethithpEnable
            && !m_echangePeopleListEnable && !m_echangeArmListEnable && !m_FunctionlistEnable
            && !key_controlAble){//在进行别的操作的时候不弹出这个画面
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
    }else{
         m_peopleHpInfo->hide();
         m_groundTypeInfo->hide();
    }


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
                      if(CGameSystem::Character_Info[groundMap->m_Peopleid[i][j]-1]->m_Ismove){
                        image.load(CGameSystem::Character_Info[groundMap->m_Peopleid[i][j]-1]->m_MappicPos[CGameSystem::Character_Info[groundMap->m_Peopleid[i][j]-1]->m_Map_ZhuangTai][TimeId%3][1]);
                      }else{
                        image.load(CGameSystem::Character_Info[groundMap->m_Peopleid[i][j]-1]->m_MappicPos[CGameSystem::Character_Info[groundMap->m_Peopleid[i][j]-1]->m_Map_ZhuangTai][TimeId%3][0]);
                      }
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


    //ui控件的统一控制
    if(GameMap::m_actionListEnable){//行动链表
        m_actionList->show();
    }else{
        m_actionList->hide();
    }
    if(GameMap::m_armListEnable){//行动链表 -> 攻击的武器链表
        m_armList->show();
    }else{
        m_armList->hide();
    }
    if(GameMap::m_armInfoEnable){//行动链表 -> 攻击的人物头像
        if(!m_tufeiListEnable)//可以写内置逻辑
            m_armInfo->show();
    }else{
        m_armInfo->hide();
    }
    if(GameMap::m_tufeiListEnable){//行动链表 -> 选择完武器 ->土匪选择链表
        m_tufeiList->show();
    }else{
        m_tufeiList->hide();
    }
    if(GameMap::m_attackReadyInfoEnable){//行动链表 -> 选择完武器 ->土匪选择链表 -> 战斗信息链表
        m_attackReadyInfo->show();
    }else{
        m_attackReadyInfo->hide();
    }
    if(GameMap::m_gethithpEnable){//行动链表 -> 选择完武器 ->土匪选择链表 -> 战斗信息链表 -> 战斗过程
        m_gethithp->show();
    }else{
        m_gethithp->hide();
    }

    if(GameMap::m_echangePeopleListEnable){//行动链表  -> 交换的人物选择??
        m_echangePeopleList->show();
    }else{
        m_echangePeopleList->hide();
    }
    if(GameMap::m_echangeArmListEnable){//行动链表 -> 交换的人物选择??
        m_echangeArmList1->show();
        m_echangeArmList2->show();
    }else{
        m_echangeArmList1->hide();
        m_echangeArmList2->hide();
    }
    if(GameMap::m_shangyaoEnable){//伤药
        m_shangyao->show();
    }else{
        m_shangyao->hide();
    }
    if(GameMap::m_FunctionlistEnable){
        m_Functionlist->show();
    }else{
        m_Functionlist->hide();
    }




    painter->restore();
};







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
    if(!m_actionListEnable && !m_armListEnable && !m_armInfoEnable
            && !m_tufeiListEnable && !m_attackReadyInfoEnable && !m_gethithpEnable
            && !m_echangePeopleListEnable && !m_echangeArmListEnable&& !m_FunctionlistEnable
            && !key_controlAble){
        int Mouse_pos_relativelyX = CGameSystem::Mouse_X/60+1;
        int Mouse_pos_relativelyY = (CGameSystem::Sys_Window_Height - CGameSystem::Mouse_Y)/60+1;

        qDebug()<<"单击：鼠标X的相对位置" << Mouse_pos_relativelyX;
        qDebug()<<"单击：鼠标Y的相对位置" << Mouse_pos_relativelyY;

        int tmppeople_id  = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[Mouse_pos_relativelyX][Mouse_pos_relativelyY];
        if(!tmppeople_id || !CGameSystem::Character_Info[tmppeople_id -1]->m_Islive ||CGameSystem::Character_Info[tmppeople_id -1]->m_Attributes.m_Job == _DEF_Character_Job_TuFei  || !CGameSystem::Character_Info[tmppeople_id -1]->m_Ismove)  {//特例退出
            return;
        }
        CGameSystem::change_using_peoid(tmppeople_id); //获取当前选定的角色id

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
        key_controlAble = 1;//允许键盘控制/启动键盘控制角色
    }

}


//键盘的控制
void GameMap::keyPressEvent(QKeyEvent *event){
     int op = event->key();
     qDebug()<<"收到键盘信号 : " << op;
    /*
     * 地图上只有peoplephinfo和groundtypeinfo这两个控件显示时，
     * 这说明还没有对角色进行选定，
     * 这时可以通过方向键移动和回车键对人物进行控制
    */
    if(!m_actionListEnable && !m_armListEnable && !m_armInfoEnable
            && !m_tufeiListEnable && !m_attackReadyInfoEnable
            && !m_echangePeopleListEnable && !m_echangeArmListEnable&& !m_FunctionlistEnable
            && key_controlAble)
    {
        switch(op){
                   case Qt::Key_W:
                    qDebug("The key you Pressed is : ↑ \n");
                    CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Map_ZhuangTai = 1;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
                    if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY <CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY+1] == _DEF_COLOR_GROUND_BLUE)
                        CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY++;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
                    updateMap();
                    CGameSystem::m_gameSound->gamePeopleMovePlay(true); //人物移动音效
                    break;
                 case Qt::Key_S:
                    qDebug("The key you Pressed is : ↓ \n");
                    CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Map_ZhuangTai = 2;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
                    if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY >0 && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY-1] == _DEF_COLOR_GROUND_BLUE)
                        CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY--;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
                    updateMap();
                    CGameSystem::m_gameSound->gamePeopleMovePlay(true); //人物移动音效
                    break;
                 case Qt::Key_A:
                    qDebug("The key you Pressed is : ← \n");
                    CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Map_ZhuangTai = 3;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
                    if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX >0  && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX-1][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] == _DEF_COLOR_GROUND_BLUE)
                        CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX--;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
                    updateMap();
                    CGameSystem::m_gameSound->gamePeopleMovePlay(true); //人物移动音效
                    break;
                 case Qt::Key_D:
                    qDebug("The key you Pressed is : → \n");
                    CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Map_ZhuangTai = 4;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
                    if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX <CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX+1][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] == _DEF_COLOR_GROUND_BLUE)
                        CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX++;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
                    updateMap();
                    CGameSystem::m_gameSound->gamePeopleMovePlay(true); //人物移动音效
                    break;
                 //case Qt::Key_Enter:{//数字键盘回车键
                   case Qt::Key_Return:{//字母键盘回车键
                    qDebug("The key you Pressed is : Enter \n");
                    CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Map_ZhuangTai = 0;
                    //TODO: 调用行动函数;
                    //清除色层
                    memset(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color , 0 , sizeof CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color);
                    updateMap();
                    Xreset = 0,Yreset = 0;//清空移动重设;
                    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);//恢复鼠标;
                    key_controlAble = 0;//结束控制

                    actionListShow();//显示动作列表

                    break;
                   }
                case Qt::Key_Escape://esc
                   qDebug("The key you Pressed is : ESC \n");
                   if(CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX != Xreset || CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY != Yreset){//非原点esc 就是 回到原点
                       CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Map_ZhuangTai = 5;
                       CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = 0;
                       CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX = Xreset;
                       CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY = Yreset;
                       CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowX][CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_NowY] = CGameSystem::using_peoid;
                       updateMap();
                   }else{//在原点esc 就是 退出控制
                       //清除色层
                       CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Map_ZhuangTai = 0;
                       memset(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color , 0 , sizeof CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Color);
                       updateMap();
                       Xreset = 0,Yreset = 0;//清空移动重设;
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
    else
    {
        /*
         *当地图上除了peoplephinfo和groundtypeinfo这两个控之外，
         *还有其他ui控件，说明人物已经选择完毕，接下来控制ui控件，只有esc键有效
         * 通过esc控制ui控件的隐藏，实现“选项回退”功能
        */
        if(op == Qt::Key_Escape)
        {
            //控件显示和隐藏控制
            if(m_FunctionlistEnable){//function的回退
                m_FunctionlistEnable = false;
            }
            if(m_actionListEnable) //动作 回退
            {
                m_actionListEnable = false;
                OverAction();//每种操作后都禁止选中
            }

            if(m_armListEnable && m_armInfoEnable) //动作攻击->武器列表，武器信息 的回退
            {
                m_armListEnable = false;
                m_armInfoEnable = false;
                m_actionListEnable = true;
            }

            if(m_tufeiListEnable) //武器列表，武器信息->土匪列表 的回退
            {
                m_tufeiListEnable = false;
                m_armListEnable = true;
                m_armInfoEnable = true;
            }

            if(m_attackReadyInfoEnable) //土匪列表->战斗信息 的回退
            {
                m_attackReadyInfoEnable = false;
                m_tufeiListEnable = true;
            }

            if(m_shangyaoEnable)//动作物品->伤药 的回退
            {
                m_shangyaoEnable = false;
                m_actionListEnable = true;
            }

            if(m_echangePeopleListEnable) //动作交换->交换人物列表  的回退
            {
                m_echangePeopleListEnable = false;
                m_actionListEnable = true;
            }

            if(m_echangeArmListEnable) // 交换人物列表->交换武器列表 的回退
            {
                m_echangeArmListEnable = false;
                m_echangePeopleListEnable = true;
            }

            updateMap();
        }
     }
}

//---------------------
//---------------------
//---------------------
//-------------------------------------------------------------------
void GameMap::actionListShow()
{
    m_actionListEnable = false;
    m_armListEnable = false;
    m_armInfoEnable = false;
    m_attackReadyInfoEnable = false;
    m_tufeiListEnable = false;
    m_echangeArmListEnable = false;
    m_echangePeopleListEnable = false;

    m_actionList->deleteItemList();

    //根据人物id获取行动列表
    int id = CGameSystem::using_peoid;
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
    ActionListItem* item = new ActionListItem;
    item->setInfo("待机");
    m_actionList->addItem(item);

    m_actionList->createList();
    m_actionListEnable = true;

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
        m_actionListEnable = false;
        m_armListEnable = false;

        m_armList->deleteItemList();

        //显示武器列表
        //1.获取人物信息
        int id = CGameSystem::using_peoid;
        Character *character = CGameSystem::Character_Info[id-1];
        //2.获取可使用的武器
        std::list<CArm*> UsedtoATK = character->Able_UsedtoATK();
        //2.从武器链表中获取武器信息
        for(auto ite = UsedtoATK.begin(); ite != UsedtoATK.end(); ite++)
        {
                ArmListItem* armItem = new ArmListItem;
                armItem->pArm = (*ite);//把指针存到ArmListItem里面;
                armItem->setInfo();
                m_armList->addItem(armItem);
        }
        //2.显示
        m_armList->createList();
        m_armListEnable = true;
        OverAction();//每种操作后都禁止选中
    }
    else if(!strcmp(actionName.toStdString().c_str(), "治疗"))
    {
        OverAction();//每种操作后都禁止选中
    }
    else if(!strcmp(actionName.toStdString().c_str(), "物品"))
    {
        //隐藏行动列表
        m_actionListEnable = false;
        m_armListEnable = false;

        m_armList->deleteItemList();

        //显示武器列表
        //1.获取人物信息
        int id = CGameSystem::using_peoid;
        Character *character = CGameSystem::Character_Info[id-1];
        //2.获取可使用的武器
        std::list<CArm*> UsedtoATK = character->Able_UsedtoThing();
        //2.从武器链表中获取武器信息
        for(auto ite = UsedtoATK.begin(); ite != UsedtoATK.end(); ite++)
        {
            ArmListItem* armItem = new ArmListItem;
            armItem->pArm = (*ite);//把指针存到ArmListItem里面;
            armItem->setInfo();
            m_armList->addItem(armItem);
        }
        //2.显示
        m_armList->createList();
        m_armListEnable = true;
        OverAction();//每种操作后都禁止选中
    }
    else if(!strcmp(actionName.toStdString().c_str(), "交互"))
    {
//        //获取当前人物信息
//        //1.获取人物信息
//        int peoid = CGameSystem::using_peoid;
//        Character *character = CGameSystem::Character_Info[peoid-1];
//        //获取当前人物x，y坐标
//        int x = character->m_NowX;
//        int y = character->m_NowY;
//        //获取关卡id
//        int guangkaid = CGameSystem::Checkpoint-1;

//        int id = CGameSystem::Able_UsedtoGroundFun(guangkaid,x,y);
//        CGameSystem::side_story_used(id);
        OverAction();//每种操作后都禁止选中
    }
    else if(!strcmp(actionName.toStdString().c_str(), "交换"))
    {
        //隐藏行动列表
        m_actionListEnable = false;
        m_echangePeopleListEnable = false;
        m_echangeArmListEnable = false;

        //1.获取可以与当前角色交换武器的人物id列表
        int id = CGameSystem::using_peoid;
        std::list<int> UsedtoExchange = CGameSystem::Able_UsedtoExchange(id);
        m_echangePeopleList->deleteItemList();
        //将可交换的友军信息显示出来，供玩家选择
        for(auto ite = UsedtoExchange.begin(); ite != UsedtoExchange.end(); ite++)
        {
            //获取友方的id
            int blueId = *ite;
            //根据友方的id设置相关信息
            EchangePeopleListItem* echangePeopleItem = new EchangePeopleListItem;
            echangePeopleItem->setInfo(blueId);
            m_echangePeopleList->addItem(echangePeopleItem);
        }
        m_echangePeopleList->createList();
        m_echangePeopleListEnable = true;
        OverAction();//每种操作后都禁止选中

    }
    else if(!strcmp(actionName.toStdString().c_str(), "待机"))
    {
        m_actionListEnable = false;
        OverAction();//每种操作后都禁止选中
    }
}

//武器信息显示槽函数
void GameMap::slot_armInfoShow(CArm *Armnow)
{
    //获取当前人物信息
    int id = CGameSystem::using_peoid;
    Character *character = CGameSystem::Character_Info[id-1];
    //显示武器信息
    m_armInfo->setArmInfo(Armnow);
    m_armInfoEnable = true;
}

//选择武器
void GameMap::slot_armChoice(CArm *Armnow)
{
    qDebug()<<"slot: "<<QString::fromStdString(Armnow->m_name );
    CGameSystem::change_using_arm(Armnow);

    //伤药
    if(Armnow->m_Id == _DEF_CArm_BASE + 5){
         m_shangyaoEnable = true;
    }
    else
    {
//        //获取当前人物信息
        int id = CGameSystem::using_peoid;
//        Character *character = CGameSystem::Character_Info[id-1];

        //获取可以攻击的敌方链表
        std::list<int> UsedtoATKPeoid = Armnow->Able_UsedtoATKPeoid(id, Armnow);
        m_tufeiList->deleteItemList();
        //将可攻击范围内的敌方信息显示出来，供玩家选择
        for(auto ite = UsedtoATKPeoid.begin(); ite != UsedtoATKPeoid.end(); ite++)
        {
            //获取tufei的id
            int tufeiId = *ite;
            //根据tufei的id设置相关信息
            TufeiListItem* tufeiItem = new TufeiListItem;
            tufeiItem->setInfo(tufeiId);
            m_tufeiList->addItem(tufeiItem);
        }

        m_tufeiList->createList();
        m_tufeiListEnable = true;
    }
}

//玩家选择要攻击的土匪后，战斗前，显示双方信息
void GameMap::slot_attackReadyInfoShow(int blueId,CArm* arm, int redId)//第二个参数 或者可以考率 CGAME..Using Arm
{
    m_attackReadyInfo->setInfo(blueId,arm, redId);
    m_attackReadyInfoEnable = true;
}

//伤药使用槽函数
void GameMap::slot_useShangYao(bool yes)
{
    Tool_Info* toolInfo = new Tool_Info;
    if(yes)
    {
        //hp增加
        toolInfo->showinfo("使用成功，Hp恢复1点");
    }

    m_shangyaoEnable = false;
}




//双方角色可交换的武器信息显示槽函数
void GameMap::slot_changePeopleArmShow(int peoid1, int peoid2)
{
    m_actionListEnable = false;
    m_echangePeopleListEnable = false;

    m_echangeArmList1->deleteItemList();
    m_echangeArmList2->deleteItemList();

    m_echangeArmList1->setInfo(peoid1);
    m_echangeArmList2->setInfo(peoid2);
    m_echangeArmListEnable = true;
}

void GameMap::on_pb_ShowFunction_clicked()
{
    m_FunctionlistEnable = true;
}
//待机
void GameMap::OverAction(){
    CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Ismove = 0;
    qDebug()<<CGameSystem::Character_Info[CGameSystem::using_peoid-1]->m_Id -_DEF_Character_BASE;
}


//-----------------------------自动移动
int GameMap::RedWork_AIATKPeo(int peoid,int round){//能攻击到的最好目标；
    std::list<int>ans;
        int x =  CGameSystem::Character_Info[peoid-1]->m_NowX;
        int y =  CGameSystem::Character_Info[peoid-1]->m_NowY;
        int juli = 1;
        int aim = 0;
        if(x-juli>0 && (aim=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x-juli][y])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive &&CGameSystem::Character_Info[aim-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei)
                ans.push_back(aim);
            aim = 0;
        }
        if(y-juli>0 && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x][y-juli])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive &&CGameSystem::Character_Info[aim-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei)
                ans.push_back(aim);
            aim = 0;
        }
        if(x+juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x+juli][y])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive &&CGameSystem::Character_Info[aim-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei)
                ans.push_back(aim);
            aim = 0;

        }
        if(y+juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x][y+juli])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive &&CGameSystem::Character_Info[aim-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei)
                ans.push_back(aim);
            aim = 0;
        }
    int tmpnowhp = 0x3f3f3f3f;
    int res = 0;
    for(auto it = ans.begin();it!=ans.end();it++){//TODO：可优化内部优先级 领主》弓箭》剑士》骑士
        if(CGameSystem::Character_Info[(*it)-1]->m_Attributes.m_HpNow < tmpnowhp ){
            res = (*it);
            tmpnowhp = CGameSystem::Character_Info[(*it)-1]->m_Attributes.m_HpNow;
        }
    }
    return res;
};
void GameMap::RedWork_AIMovetoPeo(int id){//智能移动
    std::map<int,int>disfind;//人物 - juli;
    //计算当前单位到所有单位的距离 并且排序;
    std::priority_queue<MoveInfo*>q;
    int Maxmapx =CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax;
    int Maxmapy =CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax;
    int fangxiang[_DEF_MAP_MAX][_DEF_MAP_MAX]={};//标记怎么到达的这个点；
    int step[_DEF_MAP_MAX][_DEF_MAP_MAX]={};//这个点的步数;




    auto findway = [&](int aimid,int moveval)->std::list<int>{
        //获得起始时候的坐标位置
        std::list<int>res;
        int posx = CGameSystem::Character_Info[aimid-1]->m_NowX;
        int posy = CGameSystem::Character_Info[aimid-1]->m_NowY;
        while(fangxiang[posx][posy] != _DEF_AIMove_Fangxiang_start /*&& posx>0 && posy>0 && posx<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax && posy <=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax */){

            if(fangxiang[posx][posy] == _DEF_AIMove_Fangxiang_up) {
                qDebug()<<"从x:"<<posx<<" y:"<<posy<<"-----走到x:"<<posx<<" y:"<<posy-1;
                posy--;

                    if(step[posx][posy]<=moveval){
                        res.push_front(_DEF_AIMove_Fangxiang_up);
                    }
                    continue;
            }
            else if(fangxiang[posx][posy] == _DEF_AIMove_Fangxiang_left) {
                qDebug()<<"从x:"<<posx<<" y:"<<posy<<"-----走到x:"<<posx+1<<" y:"<<posy;
                posx++;

                    if(step[posx][posy]<=moveval){
                        res.push_front(_DEF_AIMove_Fangxiang_left);
                    }
                    continue;
            }
            else if(fangxiang[posx][posy] == _DEF_AIMove_Fangxiang_down) {
                qDebug()<<"从x:"<<posx<<" y:"<<posy<<"-----走到x:"<<posx<<" y:"<<posy+1;
                posy++;

                    if(step[posx][posy]<=moveval){
                        res.push_front(_DEF_AIMove_Fangxiang_down);
                    }
                    continue;
            }
            else if(fangxiang[posx][posy] == _DEF_AIMove_Fangxiang_right) {
                qDebug()<<"从x:"<<posx<<" y:"<<posy<<"-----走到x:"<<posx-1<<" y:"<<posy;
                posx--;

                    if(step[posx][posy]<=moveval){
                        res.push_front(_DEF_AIMove_Fangxiang_right);
                    }
                    continue;
            }
            else{
                    qDebug()<<"AI findway err";
                    break;
            }


        }
        return res;
    };//返回行走方式的链表
    auto goway = [&](std::list<int> movewaylist,int id)->void{
        for(auto it = movewaylist.begin();it!=movewaylist.end();it++){
            switch ((*it)) {
                case _DEF_AIMove_Fangxiang_up:
                    if(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY+1]){
                        CGameSystem::Character_Info[id-1]->m_Map_ZhuangTai = 0;
                        return;
                    }
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = 0;
                    CGameSystem::Character_Info[id-1]->m_NowY+=1;
                    CGameSystem::Character_Info[id-1]->m_Map_ZhuangTai=1;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = id;
                    break;
                case _DEF_AIMove_Fangxiang_left:
                    if(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX-1][CGameSystem::Character_Info[id-1]->m_NowY]){
                        return;
                    }
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = 0;
                    CGameSystem::Character_Info[id-1]->m_NowX-=1;
                    CGameSystem::Character_Info[id-1]->m_Map_ZhuangTai =3;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = id;

                    //动画
                    break;
                case _DEF_AIMove_Fangxiang_down:
                    if(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY-1]){
                        return;
                    }
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = 0;
                    CGameSystem::Character_Info[id-1]->m_NowY-=1;
                    CGameSystem::Character_Info[id-1]->m_Map_ZhuangTai = 2;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = id;

                    //动画
                    break;
                case _DEF_AIMove_Fangxiang_right:
                    if(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX+1][CGameSystem::Character_Info[id-1]->m_NowY]){
                        return;
                    }
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = 0;
                    CGameSystem::Character_Info[id-1]->m_NowX+=1;
                    CGameSystem::Character_Info[id-1]->m_Map_ZhuangTai = 4;
                    CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = id;

                    //动画
                    break;
                default:
                    qDebug()<<"AI move err";
                    break;
            }
            updateMap();
            QCoreApplication::processEvents();
            QThread::msleep(200);

        }
        CGameSystem::Character_Info[id-1]->m_Map_ZhuangTai = 0;
    };//行走




    //bfs开始
    for(int i=1;i<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax;i++){
        for(int j = 1;j<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax;j++){
            step[i][j] =0x3f3f3f3f;
        }
    }
    MoveInfo *stpos = new MoveInfo{CGameSystem::Character_Info[id-1]->m_NowX ,CGameSystem::Character_Info[id-1]->m_NowY,_DEF_COLOR_GROUND_BLUE,0};
    fangxiang[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = _DEF_AIMove_Fangxiang_start;
    q.push(stpos);
    step[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = 0x3f3f3f3f;
    while(!q.empty()){
        int xnow = q.top()->x;
        int ynow = q.top()->y;
        int stepnow = q.top()->step;
        q.pop();
        //左
        if(xnow-1>0){
            if((stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow-1][ynow]-1]->m_Move < step[xnow-1][ynow]) || !fangxiang[xnow-1][ynow]){

                if(CGameSystem::CGround_Map_Info[CGameSystem::CGameSystem::Checkpoint-1]->m_Peopleid[xnow-1][ynow]!=0 && CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow-1][ynow]-1]->m_Islive){//有人
                    if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow-1][ynow]-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei){
                        disfind[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow-1][ynow]] = stepnow;//放到能到达位置信息里
                        fangxiang[xnow-1][ynow] = _DEF_AIMove_Fangxiang_left;
                    }
                }else{
                    if(CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow-1][ynow]-1]->m_ablewalk){//可通过
                        MoveInfo *pos1 = new MoveInfo{xnow-1 ,ynow, _DEF_COLOR_GROUND_BLUE,stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow-1][ynow]-1]->m_Move};
                        step[xnow-1][ynow] = stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow-1][ynow]-1]->m_Move;//维护步数
                        fangxiang[xnow-1][ynow] = _DEF_AIMove_Fangxiang_left;
                        q.push(pos1);
                    }
                }
            }
        }
        //下
        if(ynow-1>0){
            if((stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow][ynow-1]-1]->m_Move < step[xnow][ynow-1]) || !fangxiang[xnow][ynow-1]){
                if(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow-1]!=0 && CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow-1]-1]->m_Islive){//有人
                    if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow-1]-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei){
                        disfind[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow-1]] = stepnow;//放到能到达位置信息里
                        fangxiang[xnow][ynow-1] = _DEF_AIMove_Fangxiang_down;
                    }
                }else{
                    if(CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow][ynow-1]-1]->m_ablewalk){//不可通过
                        MoveInfo *pos2 = new MoveInfo{xnow ,ynow-1, _DEF_COLOR_GROUND_BLUE,stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow][ynow-1]-1]->m_Move};
                        step[xnow][ynow-1] = stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow][ynow-1]-1]->m_Move;//维护步数
                        fangxiang[xnow][ynow-1] = _DEF_AIMove_Fangxiang_down;
                        q.push(pos2);
                    }
                }
            }
        }

        //右
        if(xnow+1<=Maxmapx){
            if((stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow+1][ynow]-1]->m_Move < step[xnow+1][ynow]) || !fangxiang[xnow+1][ynow]){

                if(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow+1][ynow]!=0 && CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow+1][ynow]-1]->m_Islive){//有人
                    if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow+1][ynow]-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei){
                        disfind[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow+1][ynow]] = stepnow;//放到能到达位置信息里
                        fangxiang[xnow+1][ynow] = _DEF_AIMove_Fangxiang_right;
                    }
                }else{
                    if(CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow+1][ynow]-1]->m_ablewalk){//不可通过
                        MoveInfo *pos3 = new MoveInfo{xnow+1 ,ynow, _DEF_COLOR_GROUND_BLUE,stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow+1][ynow]-1]->m_Move};
                        step[xnow+1][ynow] = stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow+1][ynow]-1]->m_Move;//维护步数
                        fangxiang[xnow+1][ynow] = _DEF_AIMove_Fangxiang_right;
                        q.push(pos3);
                    }
                }
            }
        }
        //上
        if(ynow+1<=Maxmapy && !fangxiang[xnow][ynow+1]){
            if((stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow][ynow+1]-1]->m_Move < step[xnow][ynow+1]) || !fangxiang[xnow][ynow+1]){
                if(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow+1]!=0 && CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow+1]-1]->m_Islive){//有人
                    if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow+1]-1]->m_Attributes.m_Job!=_DEF_Character_Job_TuFei){
                        disfind[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow+1]] = stepnow;//放到能到达位置信息里
                        fangxiang[xnow][ynow+1] = _DEF_AIMove_Fangxiang_up;
                    }
                }else{
                    if(CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow][ynow+1]-1]->m_ablewalk){//不可通过
                        MoveInfo *pos4 = new MoveInfo{xnow ,ynow+1, _DEF_COLOR_GROUND_BLUE,stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow][ynow+1]-1]->m_Move};
                        step[xnow][ynow+1] = stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[xnow][ynow+1]-1]->m_Move;//维护步数
                        fangxiang[xnow][ynow+1] = _DEF_AIMove_Fangxiang_up;
                        q.push(pos4);
                    }
                }
            }
        }
    }//bfs找到所有人的位置;
    //sort(disfind.begin(),disfind.end());   // map自动排序
    //调试
    QString str = QString("土匪 %1 ： 找到了%2 个存活人物").arg(id).arg(disfind.size());
    qDebug()<<str;

    int MoveAbility = CGameSystem::Character_Info[id-1]->m_Attributes.Sudu/4+2;
    //考虑移动力 处理出来攻击的人
    std::list<int>able_atk;//
    for(auto it = disfind.begin();it!=disfind.end();it++){
        if(it->second <= MoveAbility){
            able_atk.push_back(it->first);
        }else{
            continue;
        }
    }
    if(!able_atk.empty()){//如果有在攻击范围内的 直接移动到附近（A*寻路）
        int minhp = 0x3f3f3f3f;
        int minhpid = -1;
        //寻找最小生命值的单位；
        for(auto it = able_atk.begin();it!=able_atk.end();it++){
           if(minhp > CGameSystem::Character_Info[(*it)-1]->m_Attributes.m_HpNow){
               minhp = CGameSystem::Character_Info[(*it)-1]->m_Attributes.m_HpNow;
               minhpid = (*it);
           }
        }
        //最短的方式走过去

        qDebug()<< id <<"开始寻路" <<"  目标为"<< minhpid;
        std::list<int>movewaylist = findway(minhpid,MoveAbility);
        qDebug()<< id <<"寻路结束";
        //TODO：走过去；
        goway(movewaylist,id);
    }else{//如果没有在范围内但是在几倍范围内的 最近的 最短路径移动过去 ；
        int doubledisaim = 0;//
        if(disfind.begin()->second <= 5*MoveAbility){ //5倍
            doubledisaim = disfind.begin()->first;
        }
        if(doubledisaim){
            std::list<int>movewaylist = findway(doubledisaim,MoveAbility);
            goway(movewaylist,id);
        }
        //无法移动
    }

};


void GameMap::RedWork(){
    CGameSystem::WoFangXingDong = 0;
    m_tool_info->showinfo("敌方回合");

    for(auto it = CGameSystem::Character_Info.begin();it!=CGameSystem::Character_Info.end();it++){
        if((*it)->m_Islive && (*it)->m_Attributes.m_Job != _DEF_Character_Job_TuFei){
            (*it)->m_Ismove = 0;
        }
    }
    CGameSystem::WoFangXingDong = 0;
    for(auto it = CGameSystem::Character_Info.begin();it!=CGameSystem::Character_Info.end();it++){
        if((*it)->m_Islive && (*it)->m_Attributes.m_Job == _DEF_Character_Job_TuFei){
            (*it)->m_Ismove = 1;
        }
    }
    //闪出标志;
    //切换背景音乐;
    for(auto it = CGameSystem::Character_Info.begin();it!=CGameSystem::Character_Info.end();it++){
        if((*it)->m_Islive && (*it)->m_Attributes.m_Job == _DEF_Character_Job_TuFei){
            if(CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Groundid[(*it)->m_NowX][(*it)->m_NowY] != 8){//如果王座
                    RedWork_AIMovetoPeo((*it)->m_Id-_DEF_Character_BASE);//自动移动;
                }

            int aim = 0;
            if(aim = RedWork_AIATKPeo((*it)->m_Id-_DEF_Character_BASE,1)){//如果有可以打到的人 攻击；
                Fightinfo* finfo = CGameSystem::GetHit((*it)->m_Id-_DEF_Character_BASE , (*it)->m_Zhuangbei , aim);
                m_gethithp->slot_Fightinfo(finfo,(*it)->m_Zhuangbei,CGameSystem::Character_Info[aim-1]->m_Zhuangbei);
            }
        }
    }
    //停止
    BlueWork();
};
void GameMap::BlueWork(){
    CGameSystem::WoFangXingDong = 1;
    //闪出标志;
     m_tool_info->showinfo("我方回合");
    //切换背景音乐;
    //1.设置所有人可以移动
    for(auto it = CGameSystem::Character_Info.begin();it!=CGameSystem::Character_Info.end();it++){
        if((*it)->m_Islive && (*it)->m_Attributes.m_Job != _DEF_Character_Job_TuFei){
            (*it)->m_Ismove = 1;
        }
    }
    //只通过信号改变;
};

