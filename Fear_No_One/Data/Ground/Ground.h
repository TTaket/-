#pragma once
#include "packdef.h"
#include <string>
#include <iostream>
#include <map>
#include "CGameSystem.h"

class Ground{
public:
	Ground(int id);
	~Ground();
public:
    int m_Id;           //地皮id
    int m_Move;         //地皮的移动难度
    bool m_ablewalk;    //是否可移动到
    std::string m_name; //名字
public:
	void InitGround();

	
};


//地形
#define Ground_1_Init \
	m_Move = 1;\
	m_ablewalk = 1;\
	m_name = "草地";

#define Ground_2_Init \
	m_Move = 2;\
	m_ablewalk = 1;\
	m_name = "山地";


#define Ground_3_Init \
	m_ablewalk = 0;\
	m_name = "悬崖";

#define Ground_4_Init \
	m_Move = 4;\
	m_ablewalk = 1;\
	m_name = "海洋";

#define Ground_5_Init \
	m_Move = 2;\
	m_ablewalk = 1;\
	m_name = "树林";

#define Ground_6_Init \
	m_Move = 1;\
	m_ablewalk = 1;\
	m_name = "村庄";

#define Ground_7_Init \
	m_Move = 1;\
	m_ablewalk = 1;\
	m_name = "要塞";


#define Ground_8_Init \
	m_Move = 1;\
	m_ablewalk = 1;\
	m_name = "王座";

#define Ground_9_Init \
	m_ablewalk = 0;\
	m_name = "要塞墙壁";





