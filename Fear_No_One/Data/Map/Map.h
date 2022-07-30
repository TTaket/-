#pragma once
#include "packdef.h"
#include <list>
#include "CGameSystem.h"


class CGround_Map{
public:
	CGround_Map(int id);
	~CGround_Map();
public:
    int m_Id;//地图id
    int m_MapXmax;//地图最大x
    int m_MapYmax;//地图最大y
    bool m_IsSeeable[_DEF_MAP_MAX][_DEF_MAP_MAX]; //是否可视
    int m_Groundid[_DEF_MAP_MAX][_DEF_MAP_MAX];  //地皮id
    int m_Peopleid[_DEF_MAP_MAX][_DEF_MAP_MAX];  //人id
    int m_Color[_DEF_MAP_MAX][_DEF_MAP_MAX];//颜色;
public:
	void InitCGround_Map();
};

#define MAP_01_Init \
m_MapXmax = 15;\
m_MapYmax = 10;\
m_Groundid[1][1]=1;\
m_Groundid[2][1]=1;\
m_Groundid[3][1]=1;\
m_Groundid[4][1]=2;\
m_Groundid[5][1]=2;\
m_Groundid[6][1]=2;\
m_Groundid[7][1]=2;\
m_Groundid[8][1]=2;\
m_Groundid[9][1]=2;\
m_Groundid[10][1]=2;\
m_Groundid[11][1]=1;\
m_Groundid[12][1]=1;\
m_Groundid[13][1]=1;\
m_Groundid[14][1]=1;\
m_Groundid[15][1]=1;\
m_Groundid[1][2]=1;\
m_Groundid[2][2]=1;\
m_Groundid[3][2]=1;\
m_Groundid[4][2]=1;\
m_Groundid[5][2]=2;\
m_Groundid[6][2]=2;\
m_Groundid[7][2]=2;\
m_Groundid[8][2]=2;\
m_Groundid[9][2]=1;\
m_Groundid[10][2]=1;\
m_Groundid[11][2]=1;\
m_Groundid[12][2]=1;\
m_Groundid[13][2]=1;\
m_Groundid[14][2]=1;\
m_Groundid[15][2]=1;\
m_Groundid[1][3]=3;\
m_Groundid[2][3]=1;\
m_Groundid[3][3]=1;\
m_Groundid[4][3]=1;\
m_Groundid[5][3]=1;\
m_Groundid[6][3]=2;\
m_Groundid[7][3]=2;\
m_Groundid[8][3]=7;\
m_Groundid[9][3]=1;\
m_Groundid[10][3]=1;\
m_Groundid[11][3]=1;\
m_Groundid[12][3]=1;\
m_Groundid[13][3]=1;\
m_Groundid[14][3]=1;\
m_Groundid[15][3]=1;\
m_Groundid[1][4]=3;\
m_Groundid[2][4]=1;\
m_Groundid[3][4]=1;\
m_Groundid[4][4]=1;\
m_Groundid[5][4]=1;\
m_Groundid[6][4]=5;\
m_Groundid[7][4]=1;\
m_Groundid[8][4]=1;\
m_Groundid[9][4]=1;\
m_Groundid[10][4]=1;\
m_Groundid[11][4]=1;\
m_Groundid[12][4]=1;\
m_Groundid[13][4]=1;\
m_Groundid[14][4]=6;\
m_Groundid[15][4]=1;\
m_Groundid[1][5]=3;\
m_Groundid[2][5]=5;\
m_Groundid[3][5]=1;\
m_Groundid[4][5]=1;\
m_Groundid[5][5]=1;\
m_Groundid[6][5]=1;\
m_Groundid[7][5]=1;\
m_Groundid[8][5]=1;\
m_Groundid[9][5]=1;\
m_Groundid[10][5]=1;\
m_Groundid[11][5]=1;\
m_Groundid[12][5]=5;\
m_Groundid[13][5]=1;\
m_Groundid[14][5]=1;\
m_Groundid[15][5]=1;\
m_Groundid[1][6]=3;\
m_Groundid[2][6]=1;\
m_Groundid[3][6]=1;\
m_Groundid[4][6]=1;\
m_Groundid[5][6]=1;\
m_Groundid[6][6]=1;\
m_Groundid[7][6]=1;\
m_Groundid[8][6]=1;\
m_Groundid[9][6]=1;\
m_Groundid[10][6]=3;\
m_Groundid[11][6]=6;\
m_Groundid[12][6]=1;\
m_Groundid[13][6]=1;\
m_Groundid[14][6]=1;\
m_Groundid[15][6]=1;\
m_Groundid[1][7]=1;\
m_Groundid[2][7]=1;\
m_Groundid[3][7]=1;\
m_Groundid[4][7]=1;\
m_Groundid[5][7]=1;\
m_Groundid[6][7]=3;\
m_Groundid[7][7]=3;\
m_Groundid[8][7]=1;\
m_Groundid[9][7]=1;\
m_Groundid[10][7]=1;\
m_Groundid[11][7]=3;\
m_Groundid[12][7]=1;\
m_Groundid[13][7]=4;\
m_Groundid[14][7]=4;\
m_Groundid[15][7]=1;\
m_Groundid[1][8]=1;\
m_Groundid[2][8]=1;\
m_Groundid[3][8]=8;\
m_Groundid[4][8]=1;\
m_Groundid[5][8]=1;\
m_Groundid[6][8]=3;\
m_Groundid[7][8]=1;\
m_Groundid[8][8]=7;\
m_Groundid[9][8]=1;\
m_Groundid[10][8]=1;\
m_Groundid[11][8]=3;\
m_Groundid[12][8]=4;\
m_Groundid[13][8]=4;\
m_Groundid[14][8]=4;\
m_Groundid[15][8]=4;\
m_Groundid[1][9]=1;\
m_Groundid[2][9]=9;\
m_Groundid[3][9]=9;\
m_Groundid[4][9]=9;\
m_Groundid[5][9]=3;\
m_Groundid[6][9]=1;\
m_Groundid[7][9]=1;\
m_Groundid[8][9]=1;\
m_Groundid[9][9]=5;\
m_Groundid[10][9]=1;\
m_Groundid[11][9]=4;\
m_Groundid[12][9]=4;\
m_Groundid[13][9]=4;\
m_Groundid[14][9]=1;\
m_Groundid[15][9]=1;\
m_Groundid[1][10]=1;\
m_Groundid[2][10]=9;\
m_Groundid[3][10]=9;\
m_Groundid[4][10]=9;\
m_Groundid[5][10]=3;\
m_Groundid[6][10]=1;\
m_Groundid[7][10]=1;\
m_Groundid[8][10]=1;\
m_Groundid[9][10]=1;\
m_Groundid[10][10]=4;\
m_Groundid[11][10]=4;\
m_Groundid[12][10]=4;\
m_Groundid[13][10]=1;\
m_Groundid[14][10]=1;\
m_Groundid[15][10]=1;\
m_Peopleid[3][2] = 9;\
m_Peopleid[5][5] = 5;\
m_Peopleid[3][8] = 11;\
m_Peopleid[6][9] = 6;\
m_Peopleid[8][5] = 7;\
m_Peopleid[9][8] = 8;\
m_Peopleid[14][9] = 10;\
m_Peopleid[15][5] = 4;\
m_Peopleid[12][3] = 3;\
m_Peopleid[13][1] = 1;\
m_Peopleid[14][2] = 2;
