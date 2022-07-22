#pragma once

#include <iostream>
#include <string>
#include <list>
#include "packdef.h"
#include "CGameSystem.h"
#include "Character.h"

class CArm{
public:
	CArm(int id);
	~CArm();
public:
    int m_Id;//物品id
    std::string m_name;//名字
    bool m_IsATK;//是否属于武器
    bool m_IsTreat;//是否属于治疗法杖
    bool m_Isthing;//是否属于物品

//针对武器：

    int m_Juli;//攻击距离
    int m_ATK;//攻击力or治疗量
    int m_Shanbi;//武器闪避能力
    int m_Mingzhong;//武器命中能力
    int m_WuqiZhonglei;//武器种类
    bool Is_Nowzhuangbei;//现在是否正在被装备
    int m_Maxusetime;//最大可使用次数
    int m_Lastusetime;//剩余的使用次数



//针对物品：
    int m_Num;//数量
    int m_Thing_funid;//物品效果


public:
    void InitCArm();//武器的初始化
    std::list<int> Able_UsedtoATKPeoid(int peoid,CArm* CArm);  //该武器可攻击到的人的id
    std::list<int> Able_UsedtoTreatPeoid(int peoid,CArm* CArm);//该武器可治疗到的人的id
    void Used_ATK(int peo,int aim);//使用这个武器去攻击
    void Used_Treat(int peo,int aim);//使用这个法杖去治疗
    void Used_Thing(int x);//使用这个物品

    void CArm_AddNum(int x);//增加数量
    bool CArm_SubNum(int x);//减少数量
    bool CArm_SubTime(int x);//减少剩余使用次数
};





//武器信息预设 
//1.铁剑 2.银枪 3.板斧 4.治疗法杖 5.伤药 6.铁弓
#define CArm_1_Init \
	m_IsATK = 1;\
	m_Juli = 1;\
	m_name = "铁剑";\
	m_Maxusetime = 30;\
	m_ATK = 30;\
	m_Shanbi = 10;\
	m_Mingzhong = 75;\
	m_WuqiZhonglei = _DEF_CArm_Jian;\
	m_Lastusetime = 30

#define CArm_2_Init \
	m_IsATK = 1;\
	m_Juli = 1;\
	m_name = "银枪";\
	m_Maxusetime = 25;\
	m_ATK = 45;\
	m_Shanbi = 15;\
	m_Mingzhong = 65;\
	m_WuqiZhonglei = _DEF_CArm_Qiang;\
	m_Lastusetime = 25


#define CArm_3_Init \
	m_IsATK = 1;\
	m_Juli = 1;\
	m_name = "板斧";\
	m_Maxusetime = 45;\
	m_ATK = 35;\
	m_Shanbi = 5;\
	m_Mingzhong = 80;\
	m_WuqiZhonglei = _DEF_CArm_Fu;\
	m_Lastusetime = 45

#define CArm_4_Init \
	m_IsTreat = 1;\
	m_Juli = 1;\
	m_name = "治疗法杖";\
	m_Maxusetime = 25;\
	m_ATK = 30;\
	m_Mingzhong = 100;\
	m_WuqiZhonglei = _DEF_CArm_Zhang;\
	m_Lastusetime = 25

#define CArm_5_Init \
	m_Isthing = 1;\
	m_name = "伤药";\
	m_Thing_funid = 1;\
	m_Num = 1;

#define CArm_6_Init \
	m_IsATK = 1;\
	m_Juli = 3;\
	m_name = "铁弓";\
	m_Maxusetime = 30;\
	m_ATK = 50;\
	m_Shanbi = 0;\
	m_Mingzhong = 100;\
	m_WuqiZhonglei = _DEF_CArm_Gong;\
	m_Lastusetime = 30

#define CArm_7_Init \
	m_IsATK = 1;\
	m_Juli = 1;\
	m_name = "十字剑";\
	m_Maxusetime = 5;\
	m_ATK = 60;\
	m_Shanbi = 0;\
	m_Mingzhong = 100;\
	m_WuqiZhonglei = _DEF_CArm_Jian;\
	m_Lastusetime = 5

#define CArm_8_Init \
	m_Isthing = 1;\
	m_name = "龙纹典";\
	m_Thing_funid = 2;\
	m_Num = 1;
