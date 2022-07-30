#ifndef MYGAMESOUND_H
#define MYGAMESOUND_H

#include <QSound>
#include <windows.h>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "CGameSystem.h"

class MyGameSound
{
public:
    MyGameSound();
    ~MyGameSound();

    void gameStartBgmPlay(bool enable);
    void gameMouseMoveToChoiceSoundPlay(bool enable);
    void gameMousePressChoiceSoundPlay(bool enable);
    void gameMapBgmPlay(bool enable);
    void gamePeopleMovePlay(bool enable);
    void gameOverSoundPlay(bool enable);
    void gameSuccessSoundPlay(bool enable);

    void setSoundOpen(bool enable);
    bool getSoundOpen();



private:
    bool m_soundOpen; //音效打开关闭标志

    QMediaPlayer* m_gameStartBgm; //游戏开始界面音效
    QMediaPlayer* m_gameMapBgm;// 游戏地图背景音乐
    QMediaPlaylist* m_gameStartBgmPlayList; //playlist用于循环播放，QMediaplayer要借助playlist才能循环播放
    QMediaPlaylist* m_gameMapBgmPlayList;


    QSound* m_gameMouseMoveToChoiceSound; //鼠标移入选项时的音效
    QSound* m_gameMousePressChoiceSound; //鼠标点击选项时的音效
    QSound* m_gamePeopleMove; //人物移动音效
    QSound* m_gameOver; //游戏失败
    QSound* m_gameSuccess; //游戏胜利
};

#endif // MYGAMESOUND_H
