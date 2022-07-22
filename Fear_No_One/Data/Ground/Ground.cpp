#include "Ground.h"


Ground::Ground(int id):m_Move(0){
	m_Id = id;
	m_name.clear();
};

Ground::~Ground(){
};



void Ground::InitGround(){
	switch (m_Id - _DEF_Ground_BASE){
		case 1:Ground_1_Init
			break;
		case 2:Ground_2_Init
			break;
		case 3:Ground_3_Init
			break;
		case 4:Ground_4_Init
			break;
		case 5:Ground_5_Init
			break;
		case 6:Ground_6_Init
			break;
		case 7:Ground_7_Init
			break;
		case 8:Ground_8_Init
			break;
		case 9:Ground_9_Init
			break;
		default:
			std::cout <<"err ： 地皮信息初始化"<< std::endl;
			break;
	}
	std::cout<< "Debug: Ground_"<< m_Id-_DEF_Ground_BASE <<"已安装" << std::endl;
};


