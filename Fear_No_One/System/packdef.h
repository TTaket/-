#pragma once

//GameSystem
//1.宏定义 初始化添加到动态数组;
#define Init_VectorPush(type,id) \
	type* type_id = new type (_DEF_##type##_BASE + id);\
	type_id->Init##type();\
	type##_Info.push_back(type_id)
//2.宏定义 从动态数组中回收;
#define Over_VectorDelete(type) \
	while(!type##_Info.empty()){\
		if(*(type##_Info.end()-1)){\
			std::cout << "Debug: "<<#type << "_"<<(*(type##_Info.end()-1))->m_Id -_DEF_##type##_BASE <<"已卸载" << std::endl;\
			delete *(type##_Info.end()-1);\
			*(type##_Info.end()-1) = nullptr;\
		}\
		type##_Info.pop_back();\
	}
//3.第一关 -- 占领王座
	#define _DEF_CHECKPOINT1_X 3
	#define _DEF_CHECKPOINT1_Y 8
//4.第二关 -- 占领王座
	#define _DEF_CHECKPOINT2_ENEMYNUM 15
//5.交互界面
	#define _DEF_Action_BASE 6000
	#define _DEF_Action_ATK _DEF_Action_BASE+1
	#define _DEF_Action_Treat _DEF_Action_BASE+2
	#define _DEF_Action_Thing _DEF_Action_BASE+3
	#define _DEF_Action_Exchange _DEF_Action_BASE+4
	#define _DEF_Action_GroundFun _DEF_Action_BASE+5
//6.存档上限大小
	#define _DEF_MAX_SAVESIZE 1000000	

//7.AI_自动移动
    #define _DEF_AIMove_Fangxiang_start  1
    #define _DEF_AIMove_Fangxiang_left   2
    #define _DEF_AIMove_Fangxiang_right  3
    #define _DEF_AIMove_Fangxiang_up     4
    #define _DEF_AIMove_Fangxiang_down   5

//8.战斗信息
struct Fightinfo{
    Fightinfo(){
        ATKtime       =0;
        Hit1          =0;
        is_boji1      =0;
        is_miss1      =0;
        Hit2          =0;
        is_boji2      =0;
        is_miss2      =0;
        Base_Exp      =0;
        Base_level    =0;
        Add_Exp       =0;
        Add_Money     =0;
        Add_shouliandu=0;
        id1           =0;
        id2           =0;
        Groundid      =0;
        hp1_now       =0;
        hp1_max       =0;
        hp2_now       =0;
        hp2_max       =0;
        is_die        =0;
    }

    int  ATKtime;
    int  Hit1;
    bool is_boji1;
    bool is_miss1;

    int  Hit2;
    bool is_boji2;
    bool is_miss2;

    int  Base_Exp;
    int  Base_level;
    int  Add_Exp;

    int  Add_Money;
    int  Add_shouliandu;

    int  id1;
    int  id2;

    int hp1_now;
    int hp1_max;
    int hp2_now;
    int hp2_max;

    int  Groundid;

    bool is_die;

};

/*支线剧情1要塞 全员生命值10点*/
/*支线剧情2要塞 全员生命值10点*/
/*支线剧情3村庄 获得 药水*3*/
/*支线剧情4村庄 获得金币 3000*/
/*支线剧情5王座 关卡一胜利条件*/
/*支线剧情6菜单 获得隐藏物品 */


//--------游戏合理性维护---------------
//建议生命值 35-60；
//建议武器攻击力 30-60；
//建议力量 10-18;
//建议命中60-100
//建议护甲 5-10；
//建议技巧 5-13；
//建议幸运值 10-18；
//建议闪避 5-20；
//建议速度 8-20；


//Ground_Map
	//1. 地图最大尺寸
		#define _DEF_MAP_MAX 105
	//2. 地图编号基础起点
		#define _DEF_CGround_Map_BASE 1000
	//3. 地图总数
		#define _DEF_CGround_Map_Num 3
    //4. 移动结构体
        struct MoveInfo{
            int x;
            int y;
            int color;
            int step;
            bool operator< (const MoveInfo&that){
                return step < that.step;
            }
        };



//Character
	//1. 人物基础起点
		#define _DEF_Character_BASE 2000
		#define _DEF_Character_Job_Base 5000
	//2. 人物总数
		#define _DEF_Character_Num 11
	//3. 最大值设定
		#define _DEF_Character_Max_Gongjili 18
		#define _DEF_Character_Max_Jiqiao 13
		#define _DEF_Character_Max_Hujia 10
		#define _DEF_Character_Max_Mokang 10
		#define _DEF_Character_Max_Xingyun 18
		#define _DEF_Character_Max_Sudu 20
		#define _DEF_Character_Max_Level 30
		#define _DEF_Character_Max_HpMax 60
		#define _DEF_Character_Max_Shouliandu 6
	//4. 职业设定
		#define _DEF_Character_Job_LingZhu _DEF_Character_Job_Base+1
		#define _DEF_Character_Job_QingQi _DEF_Character_Job_Base+2
		#define _DEF_Character_Job_ZhongQi _DEF_Character_Job_Base+3
		#define _DEF_Character_Job_MuShi _DEF_Character_Job_Base+4
		#define _DEF_Character_Job_GongJianShou _DEF_Character_Job_Base+5
		#define _DEF_Character_Job_JianShi _DEF_Character_Job_Base+6
		#define _DEF_Character_Job_TuFei _DEF_Character_Job_Base+7
	//5.宏定义 土匪人物的生成  土匪 - 等级最多10 
		#define Character_TuFei_Init(dengji,id)\
		m_name = "土匪";\
		Armslist.push_back(new CArm(_DEF_CArm_BASE+3));\
		Armslist.push_back(new CArm(_DEF_CArm_BASE+5));\
		m_Zhuangbei = *(Armslist.begin());\
		(*(Armslist.begin()))->Is_Nowzhuangbei = 1;\
		m_Attributes.Gongjili = 10;\
		m_Attributes.Jiqiao = 5+dengji/2;\
		m_Attributes.Hujia = dengji/2+5;\
		m_Attributes.Mokang = dengji/2+5;\
		m_Attributes.Xingyun = 10;\
		m_Attributes.Sudu = 8+dengji/2;\
		m_Attributes.m_Exp = 0;\
		m_Attributes.m_Level = (dengji-1)*2+1;\
		m_Attributes.m_HpMax = 35+dengji*2;\
		m_Attributes.m_HpNow = 35+dengji*2;\
		m_Attributes.m_Job = _DEF_Character_Job_TuFei;\
		m_Attributes.Shuliandu_jian = 0;\
		m_Attributes.Shuliandu_gong = 0;\
		m_Attributes.Shuliandu_qiang = 0;\
		m_Attributes.Shuliandu_fu = dengji/2+1;\
        m_Attributes.Shuliandu_zhang = 0;\
        m_iconPos ="../Fear_No_One/Resource/Character/Head/head-tufei.png";\
        m_MappicPos[0][0][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/15.png";\
        m_MappicPos[0][1][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/12.png";\
        m_MappicPos[0][2][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/17.png";\
        m_MappicPos[5][0][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/41.png";\
        m_MappicPos[5][1][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/44.png";\
        m_MappicPos[5][2][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/47.png";\
        m_MappicPos[1][0][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/20.png";\
        m_MappicPos[1][1][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/22.png";\
        m_MappicPos[1][2][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/25.png";\
        m_MappicPos[1][3][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/29.png";\
        m_MappicPos[2][0][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/03.png";\
        m_MappicPos[2][1][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/06.png";\
        m_MappicPos[2][2][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/09.png";\
        m_MappicPos[2][3][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/10.png";\
        m_MappicPos[4][0][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/70.png";\
        m_MappicPos[4][1][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/71.png";\
        m_MappicPos[4][2][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/72.png";\
        m_MappicPos[4][3][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/73.png";\
        m_MappicPos[3][0][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/34.png";\
        m_MappicPos[3][1][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/36.png";\
        m_MappicPos[3][2][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/38.png";\
        m_MappicPos[3][3][0] = "../Fear_No_One/Resource/Character/Map_basic/shanzei_Mask/40.png";\
        m_MappicPos[0][0][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/15.png";\
        m_MappicPos[0][1][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/12.png";\
        m_MappicPos[0][2][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/17.png";\
        m_MappicPos[5][0][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/41.png";\
        m_MappicPos[5][1][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/44.png";\
        m_MappicPos[5][2][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/47.png";\
        m_MappicPos[1][0][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/20.png";\
        m_MappicPos[1][1][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/22.png";\
        m_MappicPos[1][2][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/25.png";\
        m_MappicPos[1][3][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/29.png";\
        m_MappicPos[2][0][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/03.png";\
        m_MappicPos[2][1][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/06.png";\
        m_MappicPos[2][2][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/09.png";\
        m_MappicPos[2][3][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/10.png";\
        m_MappicPos[4][0][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/70.png";\
        m_MappicPos[4][1][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/71.png";\
        m_MappicPos[4][2][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/72.png";\
        m_MappicPos[4][3][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/73.png";\
        m_MappicPos[3][0][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/34.png";\
        m_MappicPos[3][1][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/36.png";\
        m_MappicPos[3][2][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/38.png";\
        m_MappicPos[3][3][1] = "../Fear_No_One/Resource/Character/Map_basic/shanzei/40.png";




//Ground
	//1. 地皮基础起点
		#define _DEF_Ground_BASE 3000
	//2. 地皮总数
		#define _DEF_Ground_Num 9
	//3. 支线数量
		#define _DEF_SideStory_Num 6
	//4. 点-支线 计算函数
		#define _DEF_GET_POINTTOSIDE(guanqia , x , y)\
		(((guanqia)*10000000) + (x)*1000 +(y))
    //5.地皮上色
        #define _DEF_COLOR_GROUND_BLUE 1
        #define _DEF_COLOR_GROUND_RED 2
//CArm
	//1. 物品基础起点
		#define _DEF_CArm_BASE 4000
	//2. 物品总数

		#define _DEF_CArm_Num 8
	//3. 武器种类
		#define _DEF_CArm_Jian 1
		#define _DEF_CArm_Gong 2
		#define _DEF_CArm_Qiang 3
		#define _DEF_CArm_Fu 4
		#define _DEF_CArm_Zhang 5


//make_Scene
    #define Init_Make_The_Scene01\
        CGameSystem::Character_Info[1 -1]->m_NowX = 13;  \
        CGameSystem::Character_Info[1 -1]->m_NowY = 1;   \
        CGameSystem::Character_Info[2 -1]->m_NowX = 14;  \
        CGameSystem::Character_Info[2 -1]->m_NowY = 2;   \
        CGameSystem::Character_Info[3 -1]->m_NowX = 12;  \
        CGameSystem::Character_Info[3 -1]->m_NowY = 3;   \
        CGameSystem::Character_Info[4 -1]->m_NowX = 15;  \
        CGameSystem::Character_Info[4 -1]->m_NowY = 5;   \
        CGameSystem::Character_Info[5 -1]->m_NowX = 5;   \
        CGameSystem::Character_Info[5 -1]->m_NowY = 5;   \
        CGameSystem::Character_Info[6 -1]->m_NowX = 6;   \
        CGameSystem::Character_Info[6 -1]->m_NowY = 9;   \
        CGameSystem::Character_Info[7 -1]->m_NowX = 8;   \
        CGameSystem::Character_Info[7 -1]->m_NowY = 5;   \
        CGameSystem::Character_Info[8 -1]->m_NowX = 9;   \
        CGameSystem::Character_Info[8 -1]->m_NowY = 8;   \
        CGameSystem::Character_Info[9 -1]->m_NowX = 3;   \
        CGameSystem::Character_Info[9 -1]->m_NowY = 2;   \
        CGameSystem::Character_Info[10-1]->m_NowX = 14;  \
        CGameSystem::Character_Info[10-1]->m_NowY = 9;   \
        CGameSystem::Character_Info[11-1]->m_NowX = 3;   \
        CGameSystem::Character_Info[11-1]->m_NowY = 8

//gamemap
//1. 设置战斗背景宏
    #define _DEF_Setstring(x)\
        #x
    #define _DEF_FightGround_load(x)\
        _DEF_Setstring(../Fear_No_One/Resource/Photo/Fight_ground##x.png)


//make_scene
//文件位置是否存档的时候应该写到存档里面
//gethit..3个 ui交互
//TODO：可优化内部优先级 领主》弓箭》剑士》骑士






//工具 1：地图输入
// #include <bits/stdc++.h>
// #include <conio.h>
// using namespace std;
// #define XMAX 15
// #define YMAX 10 
// int main(){
//     for (int i = 1;i<=YMAX;i++){
//         for(int j = 1;j<=XMAX;j++){
//             printf("m_Groundid[%d][%d]=",j,i);
//             getche();
//             printf(";\\\n");
//         }
//     }
// }


//工具 2：地图翻转
//#include <bits/stdc++.h>
//#define N 150
//using namespace std;
//char s[N+50][200];
//char ss[200];
//int main(){
//    int a1, b1, c1;
//    for (int i = 1; i <= N;i++){
//        cin >> ss;
//        sscanf(ss,"m_Groundid[%d][%d]=%d;", &a1, &b1, &c1);
//        sprintf(s[i],"m_Groundid[%d][%d]=%d;\\",b1,a1,c1);
//    }
//    for (int i=1;i<=N;i++){
//        cout << s[i] << endl;
//    }
//}
