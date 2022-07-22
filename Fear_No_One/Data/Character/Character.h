#pragma once
#include <list>
#include <string.h>
#include <cstring>
#include <iostream>

#include "packdef.h"
#include "Arms.h"


class CArm;




typedef struct{
    int Gongjili;
    int Jiqiao;
    int Hujia;
    int Mokang;
    int Xingyun;
    int Sudu;
    int m_Exp;
    int m_Level;
    int m_HpMax;
    int m_HpNow;
    int m_Job;
    int Shuliandu_jian;
    int Shuliandu_gong;
    int Shuliandu_qiang;
    int Shuliandu_fu;
    int Shuliandu_zhang;
}Attributes;//人物的属性


class Character{
public:
	Character(int id);
	~Character();
public:
    int m_Id;//人物id
    bool m_Islive;//是否存活
    bool m_Ismove;//是否可以移动
    std::string m_name;//人物的名字
    int m_NowX;//人物当前的横坐标
    int m_NowY;//人物当前的纵坐标

    std::list<CArm*>Armslist;//武器链表
    CArm* m_Zhuangbei;//正在装备的武器
	Attributes m_Attributes;

public:
	void InitCharacter();
    void upgrade(int Add_Exp);//经验值提升
    void upshuliandu (int wuqizhonglei);//熟练度提升
    bool LostHp (int num);//失去生命值
    void AddHp (int num);//恢复生命值
    void Additem (int id,int Num);//添加物品

    std::list<CArm*> Able_UsedtoATK();  //可被使用的武器链表
    std::list<CArm*> Able_UsedtoTreat();//可被使用的法杖链表
    std::list<CArm*> Able_UsedtoThing();//可被使用的物品链表

};



//熟练度设置 ：
/*
熟练度升级条件 用该类型武器击杀敌人
0 - 无法使用武器
1 - E 50%的使用武器
2 - D 70%的使用武器
3 - C 100%的使用武器
4 - B 120%的使用武器
5 - A 150%的使用武器
6 - S 200%的使用武器
*/
//等级和加点设置
//Gongjili  10 - 18;
//Jiqiao;   5 - 13;
//Hujia;    5 - 10;
//Mokang;   5 - 10;
//Xingyun;  10 - 18;
//Sudu;     8 - 20;
//m_Exp;    0 - 100;
//m_Level;  1 - 30;
//m_HpMax;  35 - 60;

#define Character_01_Init \
m_name = "罗伊";\
Armslist.push_back(new CArm(_DEF_CArm_BASE+1));\
Armslist.push_back(new CArm(_DEF_CArm_BASE+7));\
Armslist.push_back(new CArm(_DEF_CArm_BASE+5));\
m_Zhuangbei = *(Armslist.begin());\
(*(Armslist.begin()))->Is_Nowzhuangbei = 1;\
m_Attributes.Gongjili = 13;\
m_Attributes.Jiqiao = 13;\
m_Attributes.Hujia = 7;\
m_Attributes.Mokang = 7;\
m_Attributes.Xingyun = 15;\
m_Attributes.Sudu = 10;\
m_Attributes.m_Exp = 0;\
m_Attributes.m_Level = 1;\
m_Attributes.m_HpMax = 35;\
m_Attributes.m_HpNow = 35;\
m_Attributes.m_Job = _DEF_Character_Job_LingZhu;\
m_Attributes.Shuliandu_jian = 3;\
m_Attributes.Shuliandu_gong = 0;\
m_Attributes.Shuliandu_qiang = 0;\
m_Attributes.Shuliandu_fu = 0;\
m_Attributes.Shuliandu_zhang = 0;


#define Character_02_Init \
m_name = "李清";\
Armslist.push_back(new CArm(_DEF_CArm_BASE+2));\
Armslist.push_back(new CArm(_DEF_CArm_BASE+5));\
m_Zhuangbei = *(Armslist.begin());\
(*(Armslist.begin()))->Is_Nowzhuangbei = 1;\
m_Attributes.Gongjili = 15;\
m_Attributes.Jiqiao = 7;\
m_Attributes.Hujia = 8;\
m_Attributes.Mokang = 8;\
m_Attributes.Xingyun = 12;\
m_Attributes.Sudu = 17;\
m_Attributes.m_Exp = 0;\
m_Attributes.m_Level = 3;\
m_Attributes.m_HpMax = 45;\
m_Attributes.m_HpNow = 45;\
m_Attributes.m_Job = _DEF_Character_Job_QingQi;\
m_Attributes.Shuliandu_jian = 2;\
m_Attributes.Shuliandu_gong = 0;\
m_Attributes.Shuliandu_qiang = 4;\
m_Attributes.Shuliandu_fu = 0;\
m_Attributes.Shuliandu_zhang = 0;


#define Character_03_Init \
m_name = "皮古";\
Armslist.push_back(new CArm(_DEF_CArm_BASE+2));\
Armslist.push_back(new CArm(_DEF_CArm_BASE+5));\
m_Zhuangbei = *(Armslist.begin());\
(*(Armslist.begin()))->Is_Nowzhuangbei = 1;\
m_Attributes.Gongjili = 10;\
m_Attributes.Jiqiao = 5;\
m_Attributes.Hujia = 10;\
m_Attributes.Mokang = 10;\
m_Attributes.Xingyun = 10;\
m_Attributes.Sudu = 10;\
m_Attributes.m_Exp = 0;\
m_Attributes.m_Level = 3;\
m_Attributes.m_HpMax = 55;\
m_Attributes.m_HpNow = 55;\
m_Attributes.m_Job = _DEF_Character_Job_ZhongQi;\
m_Attributes.Shuliandu_jian = 2;\
m_Attributes.Shuliandu_gong = 0;\
m_Attributes.Shuliandu_qiang = 3;\
m_Attributes.Shuliandu_fu = 0;\
m_Attributes.Shuliandu_zhang = 0;


//4-剑士-帝林
//5-弓箭手-哥应星
//6-修女-紫川宁
