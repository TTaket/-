#include "Character.h"

Character::Character(int id):m_Islive(1),m_NowX(0),m_NowY(0),m_Ismove(1){
	m_Id = id;
    m_Map_ZhuangTai = 0;
	m_name.clear();
	m_Zhuangbei = nullptr;
	Armslist.clear();
	memset(&m_Attributes,0,sizeof m_Attributes);
}

Character::~Character(){
	for(auto it = Armslist.begin();it!=Armslist.end();){
		if(*it){
			delete *it;
			*it = nullptr;
			it = Armslist.erase(it);
		}
	}
	Armslist.clear();
}

void Character::InitCharacter(){
	//人物对应表;
	switch(m_Id-_DEF_Character_BASE){
		case 1:Character_01_Init
			break;
		case 2:Character_02_Init
			break;
		case 3:Character_03_Init
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			Character_TuFei_Init(((m_Id-_DEF_Character_BASE-3)/2+1),(m_Id-_DEF_Character_BASE));
			break;
		case 11:
			Character_TuFei_Init(6,11);
			break;
		default:
			std::cout << "err:  人物信息初始化错误" << std::endl;
	}
	std::cout<< "Debug: Character_"<< m_Id-_DEF_Character_BASE <<"已安装" << std::endl;
}

void Character::upgrade(int Add_Exp){
	if(m_Attributes.m_Exp + Add_Exp >= 100){
		m_Attributes.m_Exp = (m_Attributes.m_Exp + Add_Exp - 100);
		if(m_Attributes.m_Level >= _DEF_Character_Max_Level){
			return;
		}else{
			m_Attributes.m_Level++;
            //升级奖励！
            srand(0);
            int val=0;
            val = rand()%11+1;
            if(val>=7){
                m_Attributes.Sudu++;
            }else if (val > 10){
                m_Attributes.Sudu+=2;
            }
            val = rand()%11+1;
            if(val>=5){
                m_Attributes.Hujia++;
            }else if (val > 10){
                m_Attributes.Hujia+=2;
            }
            val = rand()%11+1;
            if(val>=5){
                m_Attributes.Gongjili++;
            }else if (val > 10){
                m_Attributes.Gongjili+=2;
            }
            val = rand()%11+1;
            if(val>=8){
                m_Attributes.Jiqiao++;
            }else if (val > 10){
                m_Attributes.Jiqiao+=2;
            }
            val = rand()%11+1;
            if(val>=10){
                m_Attributes.Xingyun++;
            }
            val = rand()%11+1;
            if(val>=5){
                m_Attributes.m_HpMax+=2;
            }else if (val >= 9){
                m_Attributes.m_HpMax+=4;
            }
		}
    }else{
        m_Attributes.m_Exp += Add_Exp;
    }
};
void Character::upshuliandu (int WuqiZhonglei){
	switch (WuqiZhonglei)
	{
		case _DEF_CArm_Jian :
			if(m_Attributes.Shuliandu_jian < _DEF_Character_Max_Shouliandu){
				m_Attributes.Shuliandu_jian++;
				//熟练度升级信息界面;
			}
			break;
		case _DEF_CArm_Gong :
			if(m_Attributes.Shuliandu_gong < _DEF_Character_Max_Shouliandu){
				m_Attributes.Shuliandu_gong++;
				//熟练度升级信息界面;
			}
			break;
		case _DEF_CArm_Qiang: 
			if(m_Attributes.Shuliandu_qiang < _DEF_Character_Max_Shouliandu){
				m_Attributes.Shuliandu_qiang++;
				//熟练度升级信息界面;
			}
			break;
		case _DEF_CArm_Fu :
			if(m_Attributes.Shuliandu_fu < _DEF_Character_Max_Shouliandu){
				m_Attributes.Shuliandu_fu++;
				//熟练度升级信息界面;
			}
			break;
		case _DEF_CArm_Zhang :
			if(m_Attributes.Shuliandu_zhang < _DEF_Character_Max_Shouliandu){
				m_Attributes.Shuliandu_zhang++;
				//熟练度升级信息界面;
			}
			break;
	}
};
void Character::AddHp (int num){
	if(!m_Islive){
		std::cout << "无法给阵亡单位治疗" <<std::endl; 
		return;
	}
	if(m_Attributes.m_HpNow +num >= m_Attributes.m_HpMax){
		m_Attributes.m_HpNow = m_Attributes.m_HpMax;
	}else{
		m_Attributes.m_HpNow += num;
	}

	return;
}
bool Character::LostHp (int num){
	if(m_Attributes.m_HpNow > num){
		m_Attributes.m_HpNow -= num;
		return 1;
	}
	if(m_Attributes.m_HpNow <= num){
        m_Attributes.m_HpNow = 0;
		return 0;
	}
	//死亡对话;
	return 0;
}

std::list<CArm*> Character::Able_UsedtoATK(){
	std::list<CArm*>ans;
	//找到可以使用的武器list
	for(auto it = Armslist.begin();it!=Armslist.end();it++){
		//1.熟练度不为0；
		//2.剩余使用次数不为0；
		//3.范围内不为空；
		//4.是武器
		if(!(*it)->m_IsATK){
			continue;
		}
		int shuliandu = 0;
		switch ((*it)->m_WuqiZhonglei)
		{
			case _DEF_CArm_Jian:
				shuliandu = m_Attributes.Shuliandu_jian;
				break;
			case _DEF_CArm_Fu:
				shuliandu = m_Attributes.Shuliandu_fu;
				break;
			case _DEF_CArm_Gong:
				shuliandu = m_Attributes.Shuliandu_gong;
				break;
			case _DEF_CArm_Qiang:
				shuliandu = m_Attributes.Shuliandu_qiang;
				break;
		}
		if(!shuliandu){
			continue;
		}
		if((*it)->m_Lastusetime <= 0){
			continue;
		}
		bool ispeo = 0;
//        if(m_NowX-(*it)->m_Juli>0 && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX-(*it)->m_Juli][m_NowY]){
//            if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX-(*it)->m_Juli][m_NowY]-1]->m_Islive)
//                ispeo = 1;
//        }
//        if(m_NowY-(*it)->m_Juli>0 && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX][m_NowY-(*it)->m_Juli]){
//            if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX][m_NowY-(*it)->m_Juli]-1]->m_Islive)
//                ispeo = 1;
//        }
//        if(m_NowX+(*it)->m_Juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX+(*it)->m_Juli][m_NowY]){
//            if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX+(*it)->m_Juli][m_NowY]-1]->m_Islive)
//                ispeo = 1;
//        }
//        if(m_NowY+(*it)->m_Juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX][m_NowY+(*it)->m_Juli]){
//            if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX][m_NowY+(*it)->m_Juli]-1]->m_Islive)
//                ispeo = 1;
//        }
//		if(ispeo){
			ans.push_back(*it);
//		}
	}
	return ans;
};

std::list<CArm*> Character::Able_UsedtoTreat(){
	std::list<CArm*>ans;
	//找到可以使用的法杖list
	for(auto it = Armslist.begin();it!=Armslist.end();it++){
		//1.熟练度不为0；
		//2.剩余使用次数不为0；
		//3.范围内不为空；
		//4.是武器
		if(!(*it)->m_IsTreat){
			continue;
		}
		if(!m_Attributes.Shuliandu_zhang){
			continue;
		}
		if((*it)->m_Lastusetime <= 0){
			continue;
		}
		bool ispeo = 0;
		if(m_NowX-(*it)->m_Juli>0 && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX-(*it)->m_Juli][m_NowY]){
            if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX-(*it)->m_Juli][m_NowY]-1]->m_Islive)
                ispeo = 1;
		}
		if(m_NowY-(*it)->m_Juli>0 && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX][m_NowY-(*it)->m_Juli]){
            if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX][m_NowY-(*it)->m_Juli]-1]->m_Islive)
                ispeo = 1;
		}
		if(m_NowX+(*it)->m_Juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapXmax && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX+(*it)->m_Juli][m_NowY]){
            if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX+(*it)->m_Juli][m_NowY]-1]->m_Islive)
                ispeo = 1;
		}
		if(m_NowY+(*it)->m_Juli<=CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_MapYmax && CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX][m_NowY+(*it)->m_Juli]){
            if(CGameSystem::Character_Info[CGameSystem::CGround_Map_Info[CGameSystem::Checkpoint-1]->m_Peopleid[m_NowX][m_NowY+(*it)->m_Juli]-1]->m_Islive)
                ispeo = 1;
		}
		if(ispeo){
			ans.push_back(*it);
		}
	}
	return ans;
};

std::list<CArm*> Character::Able_UsedtoThing(){
	std::list<CArm*> ans;
	for(auto it = Armslist.begin();it!=Armslist.end();){
		if(!(*it)->m_Isthing){
			it++;
			continue;
		}
		if((*it)->m_Num <= 0){
			it = Armslist.erase(it);
			continue;
		}
		ans.push_back(*it);
		it++;
	}
	return ans;
}

void Character::Additem (int id,int Num){
	bool ishave = 0;
	for(auto it = Armslist.begin();it!=Armslist.end();it++){
		if((*it)->m_Id == id){
			ishave = 1;
			if((*it)->m_IsATK || (*it)->m_IsTreat){
				Armslist.push_back( new CArm(id));
			}else if((*it)->m_IsATK){
				(*it)->CArm_AddNum(Num);
			}
			break;
		}
	}
	if(!ishave){
		CArm * tmp = new CArm(id);
		tmp->m_Num = Num;
		Armslist.push_back( tmp);
	}
	return;
};
