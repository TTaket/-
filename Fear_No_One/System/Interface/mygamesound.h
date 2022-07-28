#ifndef MYGAMESOUND_H
#define MYGAMESOUND_H

#include <QSound>
#include "CGameSystem.h"

class MyGameSound
{
public:
    MyGameSound();
    ~MyGameSound();

    void gameStartSoudPlay(bool enable);
    void gameMouseMoveToChoiceSoundPlay(bool enable);
    void gameMousePressChoiceSoundPlay(bool enable);
    void gameMapBgmPlay(bool enable);
    void gamePeopleMovePlay(bool enable);

    void setSoundOpen(bool enable);


private:
    bool m_soundOpen; //音效打开关闭标志

    QSound* m_gameStartSound; //游戏开始界面音效
    QSound* m_gameMouseMoveToChoiceSound; //鼠标移入选项时的音效
    QSound* m_gameMousePressChoiceSound; //鼠标点击选项时的音效
    QSound* m_gameMapBgm;// 游戏地图背景音乐
    QSound* m_gamePeopleMove; //人物移动音效
};

#endif // MYGAMESOUND_H
