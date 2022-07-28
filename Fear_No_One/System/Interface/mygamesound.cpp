#include "mygamesound.h"

MyGameSound::MyGameSound():
    m_soundOpen(true), //默认打开音效
    m_gameStartSound(NULL),
    m_gameMouseMoveToChoiceSound(NULL),
    m_gameMousePressChoiceSound(NULL),
    m_gameMapBgm(NULL),
    m_gamePeopleMove(NULL)
{
    m_gameStartSound = new QSound("../Fear_No_One/Resource/Sound/其他/背景乐1.wav");
    m_gameMouseMoveToChoiceSound = new QSound("../Fear_No_One/Resource/Sound/其他/选取.wav");
    m_gameMousePressChoiceSound = new QSound("../Fear_No_One/Resource/Sound/其他/选中音效.wav");
    m_gameMapBgm = new QSound("../Fear_No_One/Resource/Sound/其他/背景乐3.wav");
    m_gamePeopleMove = new QSound("../Fear_No_One/Resource/Sound/其他/移动.wav");
}

MyGameSound::~MyGameSound()
{
    if(m_gameStartSound)
    {
        delete m_gameStartSound;
        m_gameStartSound = NULL;
    }
    if(m_gameMouseMoveToChoiceSound)
    {
        delete m_gameMouseMoveToChoiceSound;
        m_gameMouseMoveToChoiceSound = NULL;
    }
    if(m_gameMousePressChoiceSound)
    {
        delete m_gameMousePressChoiceSound;
        m_gameMousePressChoiceSound = NULL;
    }
}

//游戏开始界面背景音乐播放
void MyGameSound::gameStartSoudPlay(bool enable)
{
    if(enable)
    {
        if(m_soundOpen)
        {
            m_gameStartSound->setLoops(QSound::Infinite); //循环播放
            m_gameStartSound->play();
        }
    }
    else
    {
        m_gameStartSound->stop();
    }
}

//鼠标移入选项时的音效
void MyGameSound::gameMouseMoveToChoiceSoundPlay(bool enable)
{
    if(enable)
    {
        if(m_soundOpen)
        {
            m_gameMouseMoveToChoiceSound->play();
        }
    }
    else
    {
        m_gameMouseMoveToChoiceSound->stop();
    }
}

//鼠标点击选项时的音效
void MyGameSound::gameMousePressChoiceSoundPlay(bool enable)
{
    if(enable)
    {
        if(m_soundOpen)
        {
            m_gameMousePressChoiceSound->play();
        }
    }
    else
    {
        m_gameMousePressChoiceSound->stop();
    }
}

//游戏地图背景音乐
void MyGameSound::gameMapBgmPlay(bool enable)
{
    if(enable)
    {
        if(m_soundOpen)
        {
            m_gameMapBgm->setLoops(QSound::Infinite);
            m_gameMapBgm->play();
        }
    }
    else
    {
        m_gameMapBgm->stop();
    }
}

//人物移动音效
void MyGameSound::gamePeopleMovePlay(bool enable)
{
    if(enable)
    {
        if(m_soundOpen)
        {
            m_gamePeopleMove->play();
        }
    }
    else
    {
        m_gamePeopleMove->stop();
    }
}


void MyGameSound::setSoundOpen(bool enable)
{
    m_soundOpen = enable;
}
