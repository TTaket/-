#include "Map.h"
#include <iostream>
CGround_Map::CGround_Map(int id):m_MapXmax(0),m_MapYmax(0){
	m_Id = id;
	for(int i=1;i<=_DEF_MAP_MAX-5;i++){
		for(int j = 1;j<=_DEF_MAP_MAX-5;j++){
			m_IsSeeable[i][j] = 0;
			m_Groundid[i][j] = 0;
			m_Peopleid[i][j] = 0;
            m_Color[i][j]=0;
		}
	}
};

CGround_Map::~CGround_Map(){
};

void CGround_Map::InitCGround_Map(){
	switch(m_Id-_DEF_CGround_Map_BASE){
		case 1:MAP_01_Init;
			break;
		case 2://MAP_02_Init;
			break;
		case 3://MAP_03_Init;
			break;
		default:
			std::cout <<"err ： 关卡地图初始化"<< std::endl;
			break;
	}
	std::cout<< "Debug: Ground_Map_"<< m_Id-_DEF_CGround_Map_BASE <<"已安装" << std::endl;
}
	

