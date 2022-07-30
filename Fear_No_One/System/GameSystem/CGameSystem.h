#pragma once
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <QDebug>
#include <QThread>
#include <set>
#include <windows.h>

#include "Map.h"
#include "tool_info.h"
#include "packdef.h"
#include "Character.h"
#include "Ground.h"
#include "Arms.h"
#include "mygamesound.h"


class CArm;
class Ground;
class Character;
class CGround_Map;
class MyGameSound;



class CGameSystem{
public:
    static void InitGame();//初始化游戏
    static void OverGame();//结束游戏
    static void Make_The_Scene(int sceneid);//游戏后端场景的布置 - 胜利条件的确定
    static void The_Hero_Dies();//主人公死亡

    static Fightinfo* GetHit(int RenwuId1 , CArm * CArm1 ,int RenwuId2);//底层 - 攻击的伤害的落实与死亡判定和奖励
    static void Thing_Fun(int RenwuId,CArm * CArm1);//底层 - 物品的使用
    static void GetTreat(int RenwuId1 , CArm * CArm1 ,int RenwuId2);//底层 - 治疗的落实
    static void Side_story(int funid);//底层 - 地图引发的支线激活
    static void Arm_exchange(int peoid,CArm* CArm,int aimid);//底层 - 物品交换（只允许单方面的给）


    static void DuSave(int id);//读档
    static void CunSave(int id);//存档
    static void Savemanage_Du();//存档管理的 读取
    static void Savemanage_Cun(int id);//存档管理的 写入


    static std::list<int> Action(int id);//获取可执行的 行动链表
    static std::list<MoveInfo*> Able_UsedtoMove(int id);//可移动的范围链表；
    static int Able_UsedtoGroundFun(int guankaid,int x,int y);//是否可以与地形交互 - 返回值是 地皮id/0
    static std::list<int> Able_UsedtoExchange(int id);//是否可以交换物品




//槽函数
//1.存档选择编号
//2.移动范围 --触发移动函数；
//1.我方行动结束
//信号函数



public:
	//动态数组可以根据id o1的查询 所以取代了链表
    static std::vector<CGround_Map*>CGround_Map_Info;//关卡地图信息
    static std::vector<Character*>Character_Info;//人物信息
    static std::vector<Ground*>Ground_Info;//地皮信息
    static std::map<int,int>side_story_used;//支线是否被激活信息
    static std::map<int,int>point_funid;//点-支线对应表
    static int Checkpoint;//第几关
    static int Money;//钱
	
    static int Sys_Window_Height;//游戏窗口的大小
    static int Sys_Window_width;//游戏窗口的大小
    static int EnemyNum;//敌人数量-非敌全歼胜利条件的时候默认为 无穷大
    static int GAME_NEXT;//是否达到胜利条件进入下一关
    static int SaveSelect;//选择的存档编号
    static bool WoFangXingDong;//是否是我方行动的回合
    static int save01check;//1存档的进度
    static int save02check;//2存档的进度
    static int save03check;//3存档的进度

    static MyGameSound* m_gameSound; //游戏音效播放器
    static Tool_Info* m_tool_info; //信息窗口


public:
    //游戏运行过程中的
    static int using_peoid;//当前选中的人物
    static CArm* using_arm; //当前选中的人物所选择的武器
    static int exchangePeoid1; //用于保存交换武器的两个人物id
    static int exchangePeoid2;
    static int Mouse_X;//当前鼠标X坐标
    static int Mouse_Y;//当前鼠标y坐标
    static void change_using_peoid(int x);
    static void change_using_arm(CArm* Armnow);
    static void change_exchange_peoids(int peoid1, int peoid2);
    static bool gameOverFlag;
    static bool gameSuccessFlag;
};
