#include "Arms.h"

CArm::CArm(int id):m_ATK(0),m_Thing_funid(0),Is_Nowzhuangbei(0),m_Shanbi(0),m_Mingzhong(0),m_Num(1),m_IsATK(0),m_Maxusetime(0),m_Lastusetime(0),m_Juli(0),m_IsTreat(0),m_Isthing(0),m_WuqiZhonglei(0){
	m_Id = id;
	m_name.clear();
	InitCArm();
};
CArm::~CArm(){
};

void CArm::InitCArm(){
	switch(m_Id-_DEF_CArm_BASE){
		case 1: CArm_1_Init;
			break;
		case 2: CArm_2_Init;
			break;
		case 3: CArm_3_Init;
			break;
		case 4: CArm_4_Init;
			break;
		case 5: CArm_5_Init;
			break;
		case 6: CArm_6_Init;
			break;
		case 7: CArm_7_Init;
			break;
		case 8: CArm_8_Init;
			break;
		default:
			std::cout << "err:  物品信息初始化错误" << std::endl;
	}
}


void CArm::CArm_AddNum(int x){
	m_Num+=x;
};

bool CArm::CArm_SubNum(int x){
	m_Num-=x;
	if(m_Num<=0){
		return 0;
	}
	return 1;
};

bool CArm::CArm_SubTime(int x){
	m_Lastusetime-=x;
	if(m_Lastusetime<=0){
		return 0;
	}
	return 1;
};


void CArm::Used_ATK(int peo ,int aim){
	CGameSystem::GetHit(peo,this,aim);
	if(m_Lastusetime<=0){
		m_Lastusetime = 0;
	}
};
void CArm::Used_Treat(int peo,int aim){
	CGameSystem::GetTreat(peo,this,aim);
	if(m_Lastusetime<=0){
		m_Lastusetime = 0;
	}
};
void CArm::Used_Thing(int userid){
	CGameSystem::Thing_Fun(userid,this);
	if(m_Num<=0){
		m_Num = 0;
	}
};

std::list<int> CArm::Able_UsedtoATKPeoid(int peoid, CArm* CArm){
    std::list<int>ans;
        int x =  CGameSystem::Character_Info[peoid-1]->m_NowX;
        int y =  CGameSystem::Character_Info[peoid-1]->m_NowY;
        int juli = CArm->m_Juli;
        int aim = 0;
        if(x-juli>0 && (aim=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x-juli][y])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive)
                ans.push_back(aim);
            aim = 0;
        }
        if(y-juli>0 && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x][y-juli])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive)
                ans.push_back(aim);
            aim = 0;
        }
        if(x+juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x+juli][y])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive)
                ans.push_back(aim);
            aim = 0;

        }
        if(y+juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x][y+juli])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive)
                ans.push_back(aim);
            aim = 0;
        }
    return ans;
};
std::list<int> CArm::Able_UsedtoTreatPeoid(int peoid,CArm* CArm){
    std::list<int>ans;
        int x =  CGameSystem::Character_Info[peoid-1]->m_NowX;
        int y =  CGameSystem::Character_Info[peoid-1]->m_NowY;
        int juli = CArm->m_Juli;
        int aim=0;
        if(x-juli>0 && (aim=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x-juli][y])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive)
                ans.push_back(aim);
            aim = 0;
        }
        if(y-juli>0 && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x][y-juli])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive)
                ans.push_back(aim);
            aim = 0;
        }
        if(x+juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x+juli][y])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive)
                ans.push_back(aim);
            aim = 0;

        }
        if(y+juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax && (aim = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[x][y+juli])){
            if(aim && CGameSystem::Character_Info[aim-1]->m_Islive)
                ans.push_back(aim);
            aim = 0;
        }
    return ans;
};

