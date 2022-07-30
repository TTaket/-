#include "mygamesound.h"
#include <QDebug>

MyGameSound::MyGameSound():
    m_soundOpen(true), //默认打开音效
    m_gameStartBgm(NULL),
    m_gameStartBgmPlayList(NULL),
    m_gameMapBgm(NULL),
    m_gameMapBgmPlayList(NULL),
    m_gameMouseMoveToChoiceSound(NULL),
    m_gameMousePressChoiceSound(NULL),
    m_gamePeopleMove(NULL),
    m_gameOver(NULL),
    m_gameSuccess(NULL)
{
    m_gameStartBgm = new QMediaPlayer;
    m_gameStartBgmPlayList = new QMediaPlaylist;
    m_gameStartBgmPlayList->setPlaybackMode(QMediaPlaylist::Loop);
    m_gameStartBgmPlayList->addMedia(QUrl::fromLocalFile("../Fear_No_One/Resource/Sound/其他/背景乐1.wav"));
    m_gameStartBgm->setPlaylist(m_gameStartBgmPlayList);

    m_gameMapBgm = new QMediaPlayer;
    m_gameMapBgmPlayList = new QMediaPlaylist;
    m_gameMapBgmPlayList->setPlaybackMode(QMediaPlaylist::Loop);
    m_gameMapBgmPlayList->addMedia(QUrl::fromLocalFile("../Fear_No_One/Resource/Sound/其他/背景乐3.wav"));
    m_gameMapBgm->setPlaylist(m_gameMapBgmPlayList);

    m_gameMouseMoveToChoiceSound = new QSound("../Fear_No_One/Resource/Sound/其他/选取.wav");
    m_gameMousePressChoiceSound = new QSound("../Fear_No_One/Resource/Sound/其他/选中音效.wav");
    m_gamePeopleMove = new QSound("../Fear_No_One/Resource/Sound/其他/移动.wav");
    m_gameOver = new QSound("../Fear_No_One/Resource/Sound/其他/失败.wav");
    m_gameSuccess = new QSound("../Fear_No_One/Resource/Sound/其他/游戏胜利.wav");
}

MyGameSound::~MyGameSound()
{
    if(m_gameStartBgm)
    {
        delete m_gameStartBgm;
        m_gameStartBgm = NULL;
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
    if(m_gameMapBgm)
    {
        delete m_gameMapBgm;
        m_gameMapBgm = NULL;
    }
    if(m_gameOver)
    {
        delete m_gameOver;
        m_gameOver = NULL;
    }
    if(m_gameSuccess)
    {
        delete m_gameSuccess;
        m_gameSuccess = NULL;
    }
}

//游戏开始界面背景音乐播放
void MyGameSound::gameStartBgmPlay(bool enable)
{
    if(enable)
    {
        if(m_soundOpen)
        {
            m_gameStartBgm->play();
        }
        else
        {
            m_gameMapBgm->stop();
        }
    }
    else
    {
        m_gameStartBgm->stop();
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
        else
        {
            m_gameMapBgm->stop();
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
        else
        {
            m_gameMapBgm->stop();
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
            m_gameMapBgm->play();
        }
        else
        {
            m_gameMapBgm->stop();
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
        else
        {
            m_gameMapBgm->stop();
        }
    }
    else
    {
        m_gamePeopleMove->stop();
    }
}

void MyGameSound::gameOverSoundPlay(bool enable)
{
    if(enable)
    {
        if(m_soundOpen)
        {
            m_gameOver->play();
        }
        else
        {
            m_gameOver->stop();
        }
    }
    else
    {
        m_gameOver->stop();
    }
}

void MyGameSound::gameSuccessSoundPlay(bool enable)
{
    if(enable)
    {
        if(m_soundOpen)
        {
            m_gameSuccess->play();
        }
        else
        {
            m_gameSuccess->stop();
        }
    }
    else
    {
        m_gameSuccess->stop();
    }
}


void MyGameSound::setSoundOpen(bool enable)
{
    m_soundOpen = enable;
}

bool MyGameSound::getSoundOpen()
{
    return m_soundOpen;
}

