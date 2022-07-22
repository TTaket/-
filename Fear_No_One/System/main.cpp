#include "CGameSystem.h"
#include <QApplication>
#include <stdlib.h>
#include <iostream>
#include "game.h"



int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    CGameSystem::InitGame();
    Game g;
    g.show();

	//弹出开始界面 ->选择第二个界面
	//读取存档管理
    //	CGameSystem::DuSave(CGameSystem::SaveSelect);
    //	while(CGameSystem::Checkpoint<=3){
    //		CGameSystem::GAME_NEXT = 0;
    //		//布置关卡
    //		CGameSystem::Make_The_Scene(CGameSystem::Checkpoint);
    //		while(!CGameSystem::GAME_NEXT && CGameSystem::EnemyNum){
    //            CGameSystem::WoFangXingDong = 1;
    //            //弹框： 我方回合
    //            while(CGameSystem::WoFangXingDong){

    //            }
    //            //弹框： 敌方回合
    //            CGameSystem::WoFangXingDong = 1;
    //            CGameSystem::AIWork();
    //        }
    //        //提示 恭喜过关
    //        CGameSystem::Checkpoint++;
    //        //存档界面
    //    }
    //    //提示 恭喜通关 反馈信息；
    //    CGameSystem::OverGame();

    //CGameSystem::OverGame();
    return a.exec();
}


