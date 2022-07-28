#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QList>
#include <QTimer>
#include <QVector>
#include <QThread>
#include "peoplehpinfo.h"
#include "groundtypeinfo.h"
#include "actionlist.h"
#include "armlist.h"
#include "actionlistitem.h"
#include "armlistitem.h"
#include "arminfo.h"
#include "attackreadyinfo.h"
#include "packdef.h"
#include "CGameSystem.h"
#include "tufeilist.h"
#include "tufeilistitem.h"
#include "gethit_exp.h"
#include "gethit_hp.h"
#include "echangepeoplelist.h"
#include "echangepeoplelistitem.h"
#include "echangearmlist.h"
#include "shangyao.h"
#include "functionlist.h"
#include "tool_info.h"



class AttackReadyInfo;
class gethit_hp;
class gethit_exp;
class ArmInfo;
class ArmList;

namespace Ui {
class GameMap;
}

class GameMap : public QWidget
{
    Q_OBJECT

public:
    explicit GameMap(QWidget *parent = 0);
    ~GameMap();

    //更新地图
    void updateMap();
    //设置待机
    void OverAction();
    //角色移动完成后，显示动作列表
    void actionListShow();


signals:
    void SIG_jumpWidget(int id);


private slots:
    //更新列表信号槽函数
    void slot_updateList();
    //行动处理信号槽函数
    void slot_action(QString actionName);
    //武器信息显示信号槽函数
    void slot_armInfoShow(CArm* Armnow);
    //武器选择信息（装备，交换，舍去）信号槽函数
    void slot_armChoice(CArm* Armnow);
    //玩家选择要攻击的土匪后，战斗前，显示双方信息
    void slot_attackReadyInfoShow(int blueId,CArm*Armnow, int redId);
    //伤药使用槽函数
    void slot_useShangYao(bool yes);

    //双方角色可交换的武器信息显示槽函数
    void slot_changePeopleArmShow(int peoid1, int peoid2);
    //时间推进
    void slot_timeadd();
    void on_pb_ShowFunction_clicked();
    //红色行动
    void RedWork();//ai人机行动//TODO:



private:
    Ui::GameMap *ui;
    PeopleHpInfo* m_peopleHpInfo;
    GroundTypeInfo* m_groundTypeInfo;

    ActionList* m_actionList;

    ArmList* m_armList;
    ArmInfo* m_armInfo;

    TuFeiList* m_tufeiList;

    AttackReadyInfo* m_attackReadyInfo;

    gethit_hp* m_gethithp;


    EchangePeopleList* m_echangePeopleList;

    EchangeArmList* m_echangeArmList1;
    EchangeArmList* m_echangeArmList2;


    ShangYao* m_shangyao;
    Functionlist* m_Functionlist;
public:
    //这些用来标记控件是否显示，在按下ESC按键时需要用到
    static bool m_actionListEnable;
    static bool m_armListEnable;
    static bool m_armInfoEnable;
    static bool m_tufeiListEnable;
    static bool m_attackReadyInfoEnable;
    static bool m_gethithpEnable;
    static bool m_echangePeopleListEnable;
    static bool m_echangeArmListEnable;
    static bool m_shangyaoEnable;
    static bool m_FunctionlistEnable;

//绘制地图
public:
    void paintEvent(QPaintEvent *event);
    void drawPixmap(QPainter *painter);

//鼠标捕获
public:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);


//键盘和移动相关
public:
    void keyPressEvent(QKeyEvent *event);
    bool key_controlAble;
    int Xreset;
    int Yreset;
//信息
    Tool_Info * m_tool_info;
//时间相关
public:
    int TimeId;
    QTimer* timer;

//AI移动

int RedWork_AIATKPeo(int peoid,int round);//ai人机行动-返回最合适的攻击目标；
void RedWork_AIMovetoPeo(int peoid);//ai人机行动-自己移动
void BlueWork();//我方行动
};


#endif // GAMEMAP_H
