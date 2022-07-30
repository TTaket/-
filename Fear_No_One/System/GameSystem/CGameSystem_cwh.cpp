#include "CGameSystem.h"


std::vector<Character*>CGameSystem::Character_Info;
std::vector<CGround_Map*> CGameSystem::CGround_Map_Info;
std::vector<Ground*>CGameSystem::Ground_Info;
std::map<int,int> CGameSystem::side_story_used;
std::map<int,int>CGameSystem::point_funid;
int CGameSystem::Money;
int CGameSystem::Checkpoint = 0;
int CGameSystem::GAME_NEXT =0;
int CGameSystem::SaveSelect = 0;
bool CGameSystem::WoFangXingDong = 0;
int CGameSystem::EnemyNum=0x3f3f3f3f;

MyGameSound* CGameSystem::m_gameSound = NULL;

int CGameSystem::save01check =0; //标记着存档1在第几关
int CGameSystem::save02check =0;
int CGameSystem::save03check =0;
int CGameSystem::Sys_Window_Height;
int CGameSystem::Sys_Window_width;
int CGameSystem::using_peoid =0;
int CGameSystem::Mouse_X =0;//当前鼠标X坐标
int CGameSystem::Mouse_Y =0;//当前鼠标y坐标

bool CGameSystem::gameOverFlag = false;

CArm* CGameSystem::using_arm = nullptr;
int CGameSystem::exchangePeoid1 =0; //用于保存交换武器的两个人物id
int CGameSystem::exchangePeoid2 =0;

void CGameSystem::InitGame(){//初始化
	//地图部分
    Sys_Window_Height = 600;
    Sys_Window_width = 900;
	Money = 500;
	Checkpoint = 1;
	GAME_NEXT = 0;
	EnemyNum=0x3f3f3f3f;
	for(int i=1;i<=_DEF_CGround_Map_Num;i++){
		Init_VectorPush(CGround_Map,i);
	}
	//人物部分
	for(int i=1;i<=_DEF_Character_Num;i++){
		Init_VectorPush(Character,i);
	}
	//地皮
	for(int i=1;i<=_DEF_Ground_Num;i++){
		Init_VectorPush(Ground,i);
	}
	//支线
	for(int i=1;i<=_DEF_SideStory_Num;i++){
		side_story_used[i] = 0;
	}
	CGameSystem::point_funid[_DEF_GET_POINTTOSIDE(1,3,8)] = 5;
	CGameSystem::point_funid[_DEF_GET_POINTTOSIDE(1,8,8)] = 1;
	CGameSystem::point_funid[_DEF_GET_POINTTOSIDE(1,8,3)] = 2;
	CGameSystem::point_funid[_DEF_GET_POINTTOSIDE(1,14,4)] = 3;
	CGameSystem::point_funid[_DEF_GET_POINTTOSIDE(1,11,6)] = 4;
	CGameSystem::point_funid[_DEF_GET_POINTTOSIDE(1,15,10)] = 6;

    //创建音效播放器
    CGameSystem::m_gameSound = new MyGameSound; //游戏结束时记得delete
}


void CGameSystem::OverGame(){
	//地图部分
	Over_VectorDelete(CGround_Map);
	//人物部分
	Over_VectorDelete(Character);
	//地皮部分
	Over_VectorDelete(Ground);
}



Fightinfo* CGameSystem::GetHit(int x1 , CArm *CArm1 ,int y1){ //我方， 我方武器， 敌方
    Fightinfo* finfo = new Fightinfo;
    CArm *CArm2 = CGameSystem::Character_Info[y1-1]->m_Zhuangbei;//土匪
	//影响因素：
	//攻击方人物 ： 力量 、 技巧 、熟练度 、 速度、 幸运；
	//攻击方武器 ： 攻击力 、 命中； 
	//防守方人物 ： 护甲 、 魔抗 、 幸运值
	//防守方武器 ： 闪躲
	


	//攻击次数计算公式 ： 速度+幸运-速度-幸运 》8  两次；
	//伤害计算公式 ： 武器攻击力*力量/20 *熟练度效果 - 护甲/魔抗； --> 最低伤害 10*30/40-10 = 0； 最高伤害 60*2*18/20-5 = 103 ； 普遍伤害：15*45/20-7 = 26
	//命中计算公式 ： 武器命中 + 幸运 - 武器闪避 - 敌幸运 --> 最低命中 60+10-18-20 = 32 最高命中 100% 普遍命中75 + 13-13-10 =65%
	//暴击计算公式： 技巧+10+幸运 -->  最低概率 5 + 10 + 10 = 25% 最高概率 13+10+20 = 53% 普遍概率 10 + 8 + 10 = 28% 

	srand(0);
	double shouliandu_jiacheng=0;

	CGameSystem::Character_Info[x1-1]->m_Zhuangbei->Is_Nowzhuangbei = 0;
	CGameSystem::Character_Info[x1-1]->m_Zhuangbei = CArm1;
	CArm1->Is_Nowzhuangbei = 1;
    finfo->id1 = x1;
    finfo->id2 = y1;
    finfo->Base_level = CGameSystem::Character_Info[x1-1]->m_Attributes.m_Level;
    finfo->hp1_now = CGameSystem::Character_Info[x1-1]->m_Attributes.m_HpNow;
    finfo->hp2_now = CGameSystem::Character_Info[y1-1]->m_Attributes.m_HpNow;
    finfo->hp1_max = CGameSystem::Character_Info[x1-1]->m_Attributes.m_HpMax;
    finfo->hp2_max = CGameSystem::Character_Info[y1-1]->m_Attributes.m_HpMax;
    finfo->Groundid = CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[CGameSystem::Character_Info[x1-1]->m_NowX][CGameSystem::Character_Info[x1-1]->m_NowY];

	switch(CArm1->m_WuqiZhonglei){
		case _DEF_CArm_Jian:
			switch (CGameSystem::Character_Info[x1-1]->m_Attributes.Shuliandu_jian)
			{
			case 1:
				shouliandu_jiacheng = 50;
				break;
			case 2:
				shouliandu_jiacheng = 70;
				break;
			case 3:
				shouliandu_jiacheng = 100;
				break;
			case 4:
				shouliandu_jiacheng = 120;
				break;
			case 5:
				shouliandu_jiacheng = 150;
				break;
			case 6:
				shouliandu_jiacheng = 200;
				break;
			}
			break;
		case _DEF_CArm_Fu:
			switch (CGameSystem::Character_Info[x1-1]->m_Attributes.Shuliandu_fu)
			{
			case 1:
				shouliandu_jiacheng = 50;
				break;
			case 2:
				shouliandu_jiacheng = 70;
				break;
			case 3:
				shouliandu_jiacheng = 100;
				break;
			case 4:
				shouliandu_jiacheng = 120;
				break;
			case 5:
				shouliandu_jiacheng = 150;
				break;
			case 6:
				shouliandu_jiacheng = 200;
				break;
			}
			break;
		case _DEF_CArm_Qiang:
			switch (CGameSystem::Character_Info[x1-1]->m_Attributes.Shuliandu_qiang)
			{
			case 1:
				shouliandu_jiacheng = 50;
				break;
			case 2:
				shouliandu_jiacheng = 70;
				break;
			case 3:
				shouliandu_jiacheng = 100;
				break;
			case 4:
				shouliandu_jiacheng = 120;
				break;
			case 5:
				shouliandu_jiacheng = 150;
				break;
			case 6:
				shouliandu_jiacheng = 200;
				break;
			}
			break;
		case _DEF_CArm_Gong:
			switch (CGameSystem::Character_Info[x1-1]->m_Attributes.Shuliandu_gong)
			{
			case 1:
				shouliandu_jiacheng = 50;
				break;
			case 2:
				shouliandu_jiacheng = 70;
				break;
			case 3:
				shouliandu_jiacheng = 100;
				break;
			case 4:
				shouliandu_jiacheng = 120;
				break;
			case 5:
				shouliandu_jiacheng = 150;
				break;
			case 6:
				shouliandu_jiacheng = 200;
				break;
			}
			break;
	}
	int ATKtime = CGameSystem::Character_Info[x1-1]->m_Attributes.Sudu+CGameSystem::Character_Info[x1-1]->m_Attributes.Xingyun - CGameSystem::Character_Info[y1-1]->m_Attributes.Sudu-CGameSystem::Character_Info[y1-1]->m_Attributes.Xingyun;
	if(ATKtime>=8){
		ATKtime = 2;
	}else{
		ATKtime = 1;
	}
    finfo->ATKtime = ATKtime;
	int Hit = CGameSystem::Character_Info[x1-1]->m_Attributes.Gongjili*CArm1->m_ATK/20 *shouliandu_jiacheng/100 -  CGameSystem::Character_Info[y1-1]->m_Attributes.Hujia;
	int Baoji = CGameSystem::Character_Info[x1-1]->m_Attributes.Xingyun + CGameSystem::Character_Info[x1-1]->m_Attributes.Jiqiao +10;
	int Mingzhong = CArm1->m_Mingzhong + CGameSystem::Character_Info[x1-1]->m_Attributes.Xingyun - CGameSystem::Character_Info[y1-1]->m_Attributes.Xingyun - CArm2->m_Shanbi;
	int	Add_Exp = 0;
	bool Add_shouliandu = 0;
	bool Add_Money = 0;
    int roundval = 0;
	CArm1->m_Lastusetime -=ATKtime;
    for(int i=1;i<=ATKtime;i++){
        roundval =rand()%100+1;
        if( roundval<=Baoji){
			//信号暴击动作 伤害值
            if(i == 1){
                finfo->is_boji1 = 1;
                finfo->Hit1 = (int)(Hit*1.5);
            }else{
                finfo->is_boji2 = 1;
                finfo->Hit2 = (int)(Hit*1.5);

            }
            finfo->Add_Exp =finfo->Add_Exp +45;
			Add_Exp += 45;
            if(!CGameSystem::Character_Info[y1-1]->LostHp((int)(Hit*1.5))){//如果死亡 武器熟练度标记为1 跳出；
                if(y1 == 1){
                    CGameSystem::The_();//主角死亡;
				}
                finfo->is_die = 1;
				Add_shouliandu = 1;
				Add_Money = 1;
                finfo->Add_shouliandu = 1;
                finfo->Add_Money = 1;
				break;
			}
		}else{
            roundval =rand()%100+1;
            if(roundval <= Mingzhong){
                Add_Exp += 30;
                finfo->Add_Exp = finfo->Add_Exp+30;
                if(i == 1){
                    finfo->Hit1 = (int)(Hit);
                }else{
                    finfo->Hit2 = (int)(Hit);

                }
			//信号普通动作 伤害值
                if(!CGameSystem::Character_Info[y1-1]->LostHp(Hit)){//如果死亡 武器熟练度标记为1 跳出；
					if(y1 == 1){
						CGameSystem::The_Hero_Dies();
					}
                    finfo->is_die = 1;
					Add_shouliandu = 1;
					Add_Money = 1;
                    finfo->Add_shouliandu = 1;
                    finfo->Add_Money = 1;
					break;
				}
			}else{
			//信号普通动作 miss
                if(i == 1){
                    finfo->is_miss1 = 1;
                }else{
                    finfo->is_miss2 = 1;
                }
                finfo->Add_Exp = finfo->Add_Exp+15;
                Add_Exp += 15;
			}
		}
	}
	if(CGameSystem::Character_Info[x1-1]->m_Attributes.m_Job == _DEF_Character_Job_TuFei){//土匪没有加成
        return nullptr;
	}
	//经验值加成；
    finfo->Base_Exp = CGameSystem::Character_Info[x1-1]->m_Attributes.m_Exp;
	CGameSystem::Character_Info[x1-1]->upgrade(Add_Exp);//不可能连上两级
	//熟练度加成；
	if(Add_shouliandu){
		CGameSystem::Character_Info[x1-1]->upshuliandu(CArm1->m_WuqiZhonglei);
	}
	if(Add_Money){
		CGameSystem::Money+=500;
	}

    return finfo;
};

void CGameSystem::GetTreat(int x1 , CArm *CArm1 ,int y1){
	CArm1->m_Lastusetime--;
	int shuliandujiacheng = 0;
	switch (Character_Info[x1-1]->m_Attributes.Shuliandu_zhang)
	{
	case 1: shuliandujiacheng = 50;
		break;
	case 2: shuliandujiacheng = 70;
		break;
	case 3: shuliandujiacheng = 100;
		break;
	case 4: shuliandujiacheng = 120;
		break;
	case 5: shuliandujiacheng = 150;
		break;
	case 6: shuliandujiacheng = 200;
		break;
	}
	int Val =  shuliandujiacheng* CArm1->m_ATK/100;
	CGameSystem::Character_Info[y1-1]->AddHp(Val);
	CGameSystem::Character_Info[x1-1]->upgrade(45);
	CGameSystem::Character_Info[x1-1]->upshuliandu(CArm1->m_WuqiZhonglei);
}


void CGameSystem::Side_story(int id){

	if(side_story_used[id]){
		return;
	}
	switch (id)
	{
		case 1:{/*支线剧情1要塞 全员生命值10点*/
				for(auto it = CGameSystem::Character_Info.begin();it!=CGameSystem::Character_Info.end();it++){
					if(!(*it)->m_Islive){
						continue;
					}
					if((*it)->m_Attributes.m_Job!=_DEF_Character_Job_TuFei){
						(*it)->AddHp(10);
					}
				}
			   }
			break;
		case 2:{/*支线剧情2要塞 全员生命值10点*/
			   for(auto it = CGameSystem::Character_Info.begin();it!=CGameSystem::Character_Info.end();it++){
					if(!(*it)->m_Islive){
						continue;
					}
					if((*it)->m_Attributes.m_Job!=_DEF_Character_Job_TuFei){
						(*it)->AddHp(10);
					}
				}
			   }
			break;
		case 3:{/*支线剧情3村庄 获得 药水*3*/
			   //对话
				CGameSystem::Character_Info[1]->Additem (5,6);
				//界面提醒
			   }
			break;
		case 4:{/*支线剧情4村庄 获得金币 3000*/
				//对话	
				CGameSystem::Money+=3000;
				//界面提醒
			   }
			break;
		case 5:{/*支线剧情5王座 关卡一胜利条件*/
				if(CGameSystem::Character_Info[1]->m_NowX == _DEF_CHECKPOINT1_X && CGameSystem::Character_Info[1]->m_NowY == _DEF_CHECKPOINT1_Y){
					//弹出对话 
					CGameSystem::GAME_NEXT = 1;
				}else{
					std::cout << "需要罗伊(主人公)到达该位置" << std::endl; 
				}
			   }
			break;
		case 6:{/*支线剧情6菜单 获得隐藏物品 */
				//弹出对话 
				CGameSystem::Character_Info[1]->Additem (8,1);
				
			   }
			break;
		default:
			std::cout << "支线剧情出发出错" << std::endl;
			break;
	}
	side_story_used[id] = 1;
	return;
}
void CGameSystem::Thing_Fun(int Character_id , CArm* CArm){
	switch(CArm->m_Thing_funid)
	{
		case 1:{//伤药
				CArm->m_Num--;
				CGameSystem::Character_Info[Character_id-1]->AddHp(CArm->m_ATK);
				}
			   std::cout<<"物品使用成功！" <<std::endl;
			break;
		case 2:{//龙纹典
				CArm->m_Num--;
				for(int i=1;i<=5;i++){
					CGameSystem::Character_Info[Character_id-1]->upgrade(100);
				}
				std::cout<<"物品使用成功！" <<std::endl;
			}
			break;
		default:
			std::cout << "物品使用出错" << std::endl;
			break;
	}
}


void CGameSystem::The_Hero_Dies(){
	//对话
	//弹出界面 -- 设置需要回应 --强制结束；
	//结束游戏//TODO:回收
    gameOverFlag = true;
};


void CGameSystem::Make_The_Scene(int sceneid){
	//布置关卡
    switch(sceneid){
        case 1:
            Init_Make_The_Scene01;
            break;
        case 2:
            break;
        case 3:
            break;
    }
	//绘制checkpoint的界面;
	//发出胜利条件
	if(sceneid == 2)
		CGameSystem::EnemyNum=_DEF_CHECKPOINT2_ENEMYNUM;
	else
		CGameSystem::EnemyNum=0x3f3f3f3f;
};

void CGameSystem::CunSave(int id){
	CGameSystem::Savemanage_Cun(id);
	char s[100]={};
	sprintf_s(s,"./Save/Save0%d.txt",id);
	std::ofstream outfile;
	outfile.open(s, std::ios::out);
	for(int i = 0;i<_DEF_Character_Num;i++){
		outfile <<  CGameSystem::Character_Info[i]->m_Id                              << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Islive			              << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_NowX			                  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_NowY				              << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_name				              << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Gongjili			  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Jiqiao			      << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Hujia				  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Mokang			      << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Xingyun			  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Sudu			      << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.m_Exp			      << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.m_Level			  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.m_HpMax			  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.m_HpNow			  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.m_Job				  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_jian	      << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_gong	      << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_qiang	  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_fu		  << std::endl;
		outfile <<	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_zhang      << std::endl;
		outfile <<  CGameSystem::Character_Info[i]->Armslist.size()                   << std::endl;
		for(auto it = CGameSystem::Character_Info[i]->Armslist.begin();it!=CGameSystem::Character_Info[i]->Armslist.end();it++){
			outfile <<  (*it)->m_Id   									  << std::endl;
			outfile <<  (*it)->m_Juli									  << std::endl;
			outfile <<  (*it)->m_WuqiZhonglei							  << std::endl;
			outfile <<  (*it)->m_IsATK									  << std::endl;
			outfile <<  (*it)->m_IsTreat								  << std::endl;
			outfile <<  (*it)->m_Isthing								  << std::endl;
			outfile <<  (*it)->m_Thing_funid							  << std::endl;
			outfile <<  (*it)->m_name									  << std::endl;
			outfile <<  (*it)->m_Maxusetime								  << std::endl;
			outfile <<  (*it)->m_Num									  << std::endl;
			outfile <<  (*it)->m_ATK									  << std::endl;
			outfile <<  (*it)->m_Shanbi									  << std::endl;
			outfile <<  (*it)->m_Mingzhong								  << std::endl;
			outfile <<  (*it)->m_Lastusetime                              << std::endl;
			outfile <<  (*it)->Is_Nowzhuangbei                            << std::endl;
		}
	}
	//支线:
	for(auto it = CGameSystem::side_story_used.begin();it!=CGameSystem::side_story_used.end();it++){
		outfile << (it)->second << std::endl;
	}
	//全局:
	outfile << CGameSystem::Checkpoint   <<std::endl;
	outfile << CGameSystem::Money        <<std::endl;
	outfile.close();
};
void CGameSystem::DuSave(int id){
	//文件数据重新读入系统
    switch (id) {
        case 1:
            if(save01check == 0){
                return;
            }
            break;
        case 2:
            if(save02check == 0){
                return;
            }
            break;
        case 3:
            if(save03check == 0){
                return;
            }
            break;
    }
    char s[100]={};
    sprintf_s(s,"./Save/Save0%d.txt",id);
	std::ifstream infile;
	infile.open(s, std::ios::in);
	if(!infile.is_open()){
		std::cout << "cannot open file"<<std::endl;
	}
	int tmpnum =0;
	for(int i = 0;i<_DEF_Character_Num;i++){
		infile >>	CGameSystem::Character_Info[i]->m_Id                              ;
		infile >>	CGameSystem::Character_Info[i]->m_Islive			              ;
		infile >>	CGameSystem::Character_Info[i]->m_NowX			                  ;
		infile >>	CGameSystem::Character_Info[i]->m_NowY				              ;
		infile >>	CGameSystem::Character_Info[i]->m_name				              ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Gongjili			  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Jiqiao			      ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Hujia				  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Mokang			      ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Xingyun			  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Sudu			      ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.m_Exp			      ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.m_Level			  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.m_HpMax			  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.m_HpNow			  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.m_Job				  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_jian	      ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_gong	      ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_qiang	  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_fu		  ;
		infile >>	CGameSystem::Character_Info[i]->m_Attributes.Shuliandu_zhang      ;
		infile >>	tmpnum;
		CGameSystem::Character_Info[i]->Armslist.clear();
		for(int i=1;i<=tmpnum;i++){
			CArm *p = new CArm(_DEF_CArm_BASE+1); 
			infile >>  p->m_Id   									 ;
			infile >>  p->m_Juli									 ;
			infile >>  p->m_WuqiZhonglei							 ;
			infile >>  p->m_IsATK									 ;
			infile >>  p->m_IsTreat							  		 ;
			infile >>  p->m_Isthing							  		 ;
			infile >>  p->m_Thing_funid						  		 ;
			infile >>  p->m_name									 ;
			infile >>  p->m_Maxusetime								 ;
			infile >>  p->m_Num								  		 ;
			infile >>  p->m_ATK								  		 ;
			infile >>  p->m_Shanbi									 ;
			infile >>  p->m_Mingzhong								 ;
			infile >>  p->m_Lastusetime                              ;
			infile >>  p->Is_Nowzhuangbei						     ;
			if(p->Is_Nowzhuangbei){
				CGameSystem::Character_Info[i]->m_Zhuangbei = p;
			}
		}
	}
	//支线:
	for(auto it = CGameSystem::side_story_used.begin();it!=CGameSystem::side_story_used.end();it++){
		infile >> (it)->second ;
	}
	//全局:
	infile >> CGameSystem::Checkpoint   ;
	infile >> CGameSystem::Money        ;
	infile.close();

};

std::list<int> CGameSystem::Action(int id){
	std::list<int>ans;
	//攻击
	std::list<CArm*> ATKable = CGameSystem::Character_Info[id-1]->Able_UsedtoATK();
    bool ispeoatk = 0;
    for(auto it = ATKable.begin();it!=ATKable.end();it++){
        std::list<int>peoidlist = (*it)->Able_UsedtoATKPeoid(id,(*it));
        if(!peoidlist.empty()){
            ispeoatk = 1;
        }
    }
    if(ispeoatk){
        ans.push_back(_DEF_Action_ATK);
    }
    //治疗
	std::list<CArm*> Treatable = CGameSystem::Character_Info[id-1]->Able_UsedtoTreat();
	if(!Treatable.empty()){
		ans.push_back(_DEF_Action_Treat);
	}
    //物品
	std::list<CArm*> Thingable = CGameSystem::Character_Info[id-1]->Able_UsedtoThing();
	if(!Thingable.empty()){
		ans.push_back(_DEF_Action_Thing);
	}
    //交互
    int interactid = CGameSystem::Able_UsedtoGroundFun(CGameSystem::Checkpoint , CGameSystem::Character_Info[id-1]->m_NowX ,CGameSystem::Character_Info[id-1]->m_NowY);
	if(interactid != 0){
		ans.push_back(_DEF_Action_GroundFun);
	}
    //交换
    std::list<int> Exchangeable = CGameSystem::Able_UsedtoExchange(id);
	if(!Exchangeable.empty()){
		ans.push_back(_DEF_Action_Exchange);
	}
	return ans;
};

void CGameSystem::Savemanage_Du(){
	std::ifstream infile1("./Save/manage01.txt", std::ios::in | std::ios::binary);
	infile1.read((char*)&CGameSystem::save01check,sizeof(int));
	infile1.close();
	std::ifstream infile2("./Save/manage02.txt", std::ios::in | std::ios::binary);
	infile2.read((char*)&CGameSystem::save02check,sizeof(int));
	infile2.close();
	std::ifstream infile3("./Save/manage03.txt", std::ios::in | std::ios::binary);
	infile3.read((char*)&CGameSystem::save03check,sizeof(int));
	infile3.close();
}

void CGameSystem::Savemanage_Cun(int id){
	char s[100]={};
	sprintf_s(s,"./Save/manage0%d.txt",id);
	std::ofstream outfile1(s, std::ios::out | std::ios::binary);
	outfile1.write((char*)&CGameSystem::Checkpoint,sizeof(int));
	outfile1.close();
}

std::list<MoveInfo*> CGameSystem::Able_UsedtoMove(int id){
    std::list<MoveInfo*>ans;
    std::priority_queue<MoveInfo*>q;
    int Maxmapx =CGameSystem::CGround_Map_Info[Checkpoint-1]->m_MapXmax;
    int Maxmapy =CGameSystem::CGround_Map_Info[Checkpoint-1]->m_MapYmax;
    int visMap[_DEF_MAP_MAX][_DEF_MAP_MAX]={};
    int MoveAbility = CGameSystem::Character_Info[id-1]->m_Attributes.Sudu/4+2;
    qDebug() << "Able_UsedtoMove : 移动力为 : "<< MoveAbility;
    //考虑移动力 -- >可到达地方标蓝 蓝色区域内的敌人标红
    MoveInfo *pos = new MoveInfo{CGameSystem::Character_Info[id-1]->m_NowX ,CGameSystem::Character_Info[id-1]->m_NowY,_DEF_COLOR_GROUND_BLUE,0};
    visMap[CGameSystem::Character_Info[id-1]->m_NowX][CGameSystem::Character_Info[id-1]->m_NowY] = _DEF_COLOR_GROUND_BLUE;
    ans.push_back(pos);
    q.push(pos);
    while(!q.empty()){
        int xnow = q.top()->x;
        int ynow = q.top()->y;
        int stepnow = q.top()->step;
        q.pop();
        if(visMap[xnow][ynow] == _DEF_COLOR_GROUND_RED){
            continue;
        }
        //左
        if(xnow-1>0 && !visMap[xnow-1][ynow]){
            if(!(CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow-1][ynow]-1]->m_ablewalk)||(CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Peopleid[xnow-1][ynow]!=0 && CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Peopleid[xnow-1][ynow]-1]->m_Islive)){
                MoveInfo *pos = new MoveInfo{xnow-1 ,ynow, _DEF_COLOR_GROUND_RED,0x3f3f3f3f};
                ans.push_back(pos);
                visMap[xnow-1][ynow] = _DEF_COLOR_GROUND_RED;
            }else if(stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow-1][ynow]-1]->m_Move <= MoveAbility){
                if(visMap[xnow-1][ynow] != _DEF_COLOR_GROUND_BLUE){
                    MoveInfo *pos = new MoveInfo{xnow-1 ,ynow, _DEF_COLOR_GROUND_BLUE,stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow-1][ynow]-1]->m_Move};
                    if(stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow-1][ynow]-1]->m_Move < MoveAbility){
                        q.push(pos);
                    }
                    ans.push_back(pos);
                    visMap[xnow-1][ynow] = _DEF_COLOR_GROUND_BLUE;
                }
            }
        }
        //下
        if(ynow-1>0&& !visMap[xnow][ynow-1]){
            if(!(CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow][ynow-1]-1]->m_ablewalk)||(CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Peopleid[xnow][ynow-1]!=0&& CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Peopleid[xnow][ynow-1]-1]->m_Islive)){
                MoveInfo *pos = new MoveInfo{xnow ,ynow-1, _DEF_COLOR_GROUND_RED,0x3f3f3f3f};
                ans.push_back(pos);
                visMap[xnow][ynow-1] = _DEF_COLOR_GROUND_RED;
            }else if(stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow][ynow-1]-1]->m_Move <= MoveAbility){
                if(visMap[xnow][ynow-1] != _DEF_COLOR_GROUND_BLUE){
                    MoveInfo *pos = new MoveInfo{xnow ,ynow-1, _DEF_COLOR_GROUND_BLUE,stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow][ynow-1]-1]->m_Move};
                    if(stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow][ynow-1]-1]->m_Move < MoveAbility){
                        q.push(pos);
                    }
                    ans.push_back(pos);
                    visMap[xnow][ynow-1] = _DEF_COLOR_GROUND_BLUE;
                }
            }
        }
        //右
        if(xnow+1<=Maxmapx&& !visMap[xnow+1][ynow]){
            if(!(CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow+1][ynow]-1]->m_ablewalk)||(CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Peopleid[xnow+1][ynow]!=0&& CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Peopleid[xnow+1][ynow]-1]->m_Islive)){
                MoveInfo *pos = new MoveInfo{xnow+1 ,ynow, _DEF_COLOR_GROUND_RED,0x3f3f3f3f};
                ans.push_back(pos);
                visMap[xnow+1][ynow] = _DEF_COLOR_GROUND_RED;
            }else if(stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow+1][ynow]-1]->m_Move <= MoveAbility){
                if(visMap[xnow+1][ynow] != _DEF_COLOR_GROUND_BLUE){
                    MoveInfo *pos = new MoveInfo{xnow+1 ,ynow, _DEF_COLOR_GROUND_BLUE,stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow+1][ynow]-1]->m_Move};
                    if(stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow+1][ynow]-1]->m_Move < MoveAbility){
                        q.push(pos);
                    }
                    ans.push_back(pos);
                    visMap[xnow+1][ynow] = _DEF_COLOR_GROUND_BLUE;
                }
            }
        }
        //上
        if(ynow+1<=Maxmapy&& !visMap[xnow][ynow+1]){
            if(!(CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow][ynow+1]-1]->m_ablewalk)||(CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Peopleid[xnow][ynow+1]!=0&& CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Peopleid[xnow][ynow+1]-1]->m_Islive)){
                MoveInfo *pos = new MoveInfo{xnow ,ynow+1, _DEF_COLOR_GROUND_RED,0x3f3f3f3f};
                ans.push_back(pos);
                visMap[xnow][ynow+1] = _DEF_COLOR_GROUND_RED;
            }else if(stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow][ynow+1]-1]->m_Move <= MoveAbility){
                if(visMap[xnow][ynow+1] != _DEF_COLOR_GROUND_BLUE){
                    MoveInfo *pos = new MoveInfo{xnow ,ynow+1, _DEF_COLOR_GROUND_BLUE,stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow][ynow+1]-1]->m_Move};
                    if(stepnow+CGameSystem::Ground_Info[CGameSystem::CGround_Map_Info[Checkpoint-1]->m_Groundid[xnow][ynow+1]-1]->m_Move < MoveAbility){
                        q.push(pos);
                    }
                    ans.push_back(pos);
                    visMap[xnow][ynow+1] = _DEF_COLOR_GROUND_BLUE;
                }
            }
        }
    }
    //考虑攻击范围 -->移动力+攻击范围的方块表红色
    std::list<CArm*>wuqi = CGameSystem::Character_Info[id-1]->Able_UsedtoATK();
    std::set<int>atkround;
    for(auto it = wuqi.begin();it!=wuqi.end();it++){
        atkround.insert((*it)->m_Juli);
    }
    for(auto ite = atkround.begin();ite!=atkround.end();ite++){
        int atkroundnow = (*ite);
        for(auto it = ans.begin();it!=ans.end();it++){
            if((*it)->color == _DEF_COLOR_GROUND_RED){
                continue;
            }
            int xnow = (*it)->x;
            int ynow = (*it)->y;
            //左
            if(xnow-atkroundnow>0){
                if(!visMap[xnow-atkroundnow][ynow]){
                    MoveInfo *pos = new MoveInfo{xnow-atkroundnow ,ynow, _DEF_COLOR_GROUND_RED,0x3f3f3f3f};
                    ans.push_back(pos);
                }
            }
            //下
            if(ynow-atkroundnow>0){
                 if(!visMap[xnow][ynow-atkroundnow]){
                     MoveInfo *pos = new MoveInfo{xnow ,ynow-atkroundnow, _DEF_COLOR_GROUND_RED,0x3f3f3f3f};
                     ans.push_back(pos);
                 }
            }
            //右
            if(xnow+atkroundnow<=Maxmapx){
                if(!visMap[xnow+atkroundnow][ynow]){
                    MoveInfo *pos = new MoveInfo{xnow+atkroundnow ,ynow, _DEF_COLOR_GROUND_RED,0x3f3f3f3f};
                    ans.push_back(pos);
                }
            }
            //上
            if(ynow+atkroundnow<=Maxmapy){
                if(!visMap[xnow][ynow+atkroundnow]){
                    MoveInfo *pos = new MoveInfo{xnow ,ynow+atkroundnow, _DEF_COLOR_GROUND_RED,0x3f3f3f3f};
                    ans.push_back(pos);
                }
            }
        }
    }
    return ans;
};

void CGameSystem::Arm_exchange(int peoid,CArm* CArm,int aimid){
    CGameSystem::Character_Info[aimid-1]->Armslist.push_back(CArm);
    for(auto it = CGameSystem::Character_Info[peoid-1]->Armslist.begin();it!=CGameSystem::Character_Info[peoid-1]->Armslist.end();it++){
        if((*it) == CArm){
            CGameSystem::Character_Info[aimid-1]->Armslist.erase(it);
            break;
        }
    }
};

int CGameSystem::Able_UsedtoGroundFun(int guankaid,int x,int y){
    int id = 0;
    int check = _DEF_GET_POINTTOSIDE(guankaid,x,y);
    if(!(CGameSystem::point_funid.find(check)!=CGameSystem::point_funid.end())){
        id = CGameSystem::point_funid[check];
    }
    if(id!=0 && !CGameSystem::side_story_used[id]){
        return id;
    }else{
        return 0;
    }
};

std::list<int> CGameSystem::Able_UsedtoExchange(int id){
    std::list<int>ans;
    int xnow = CGameSystem::Character_Info[id-1]->m_NowX;
    int ynow = CGameSystem::Character_Info[id-1]->m_NowY;
    if(xnow-1 >0){
        int peoid = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow-1][ynow];
        if(peoid != 0 && CGameSystem::Character_Info[peoid-1]->m_Attributes.m_Job != _DEF_Character_Job_TuFei){
            if(CGameSystem::Character_Info[peoid-1]->m_Islive){
                ans.push_back(peoid);
            }
        }
    }
    if(ynow-1 >0){
        int peoid = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow-1];
        if(peoid != 0 && CGameSystem::Character_Info[peoid-1]->m_Attributes.m_Job != _DEF_Character_Job_TuFei){
            if(CGameSystem::Character_Info[peoid-1]->m_Islive){
                ans.push_back(peoid);
            }
        }
    }
    if(xnow+1 <= CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax){
        int peoid = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow+1][ynow];
        if(peoid != 0 && CGameSystem::Character_Info[peoid-1]->m_Attributes.m_Job != _DEF_Character_Job_TuFei){
            if(CGameSystem::Character_Info[peoid-1]->m_Islive){
                ans.push_back(peoid);
            }
        }
    }
    if(ynow+1 <= CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax){
        int peoid = CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[xnow][ynow+1];
        if(peoid != 0 && CGameSystem::Character_Info[peoid-1]->m_Attributes.m_Job != _DEF_Character_Job_TuFei){
            if(CGameSystem::Character_Info[peoid-1]->m_Islive){
                ans.push_back(peoid);
            }

        }
    }
    return ans;
};

void CGameSystem::change_using_peoid(int x){
    if(using_peoid!=0){
        CGameSystem::Character_Info[using_peoid-1]->m_Map_ZhuangTai = 0;//取消原本状态
    }
    CGameSystem::Character_Info[x -1 ]->m_Map_ZhuangTai = 5;//设置为选中态
    using_peoid = x;
}

void CGameSystem::change_using_arm(CArm* Armnow)
{
    using_arm = Armnow;
}
void CGameSystem::change_exchange_peoids(int peoid1, int peoid2)
{
    exchangePeoid1 = peoid1;
    exchangePeoid2 = peoid2;
}
