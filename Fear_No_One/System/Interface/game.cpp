#include "game.h"
#include "ui_game.h"
#include <QDebug>

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game),
    m_gameStart(NULL),
    m_gameChoice(NULL),
    m_gameMap(NULL),
    m_gameSuccess(NULL)
{
    ui->setupUi(this);
    setWindowTitle("火焰纹章-Fear No One");
    //把stack widget原来的widget删除，不需要
    for(int i=0;i<ui->sw_game->count();i++)
    {
        QWidget* widget = ui->sw_game->widget(i);
        ui->sw_game->removeWidget(widget);
    }

    //游戏开始界面
    m_gameStart = new GameStart;

    QObject::connect(m_gameStart,
                     SIGNAL(SIG_jumpWidget(int)),
                     this,
                     SLOT(dealJumpWidget(int)));

    //游戏选项界面1
    m_gameChoice = new GameChoice;
    QObject::connect(m_gameChoice,
                     SIGNAL(SIG_jumpWidget(int)),
                     this,
                     SLOT(dealJumpWidget(int)));

    //游戏选项界面2
    m_gameChoice2 = new GameChoice2;
    QObject::connect(m_gameChoice2,
                     SIGNAL(SIG_jumpWidget(int)),
                     this,
                     SLOT(dealJumpWidget(int)));

    //游戏地图界面
    m_gameMap = new GameMap;
    QObject::connect(m_gameMap,
                     SIGNAL(SIG_jumpWidget(int)),
                     this,
                     SLOT(dealJumpWidget(int)));

    //gameover界面
    m_gameOver = new GameOver;
    QObject::connect(m_gameOver,
                     SIGNAL(SIG_jumpWidget(int)),
                     this,
                     SLOT(dealJumpWidget(int)));

    //游戏胜利界面
    m_gameSuccess = new GameSuccess;
    QObject::connect(m_gameSuccess,
                     SIGNAL(SIG_jumpWidget(int)),
                     this,
                     SLOT(dealJumpWidget(int)));

    //添加ui界面
    ui->sw_game->addWidget(m_gameStart);
    ui->sw_game->addWidget(m_gameChoice);
    ui->sw_game->addWidget(m_gameChoice2);
    ui->sw_game->addWidget(m_gameMap);
    ui->sw_game->addWidget(m_gameOver);
    ui->sw_game->addWidget(m_gameSuccess);

    ui->sw_game->setCurrentWidget(m_gameStart);
}

Game::~Game()
{
    delete ui;

    if(m_gameStart)
    {
        delete m_gameStart;
        m_gameStart = NULL;
    }
    if(m_gameChoice)
    {
        delete m_gameChoice;
        m_gameChoice = NULL;
    }
    if(m_gameChoice2)
    {
        delete m_gameChoice2;
        m_gameChoice2 = NULL;
    }
    if(m_gameMap)
    {
      delete m_gameMap;
      m_gameMap = NULL;
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

//跳转到相应的界面
void Game::dealJumpWidget(int widgetId)
{
    qDebug()<<widgetId;
    ui->sw_game->setCurrentIndex(widgetId);
    //播放跳转音效
}


//关闭事件
void Game::closeEvent(QCloseEvent *event)
{
    int closeApp = QMessageBox::question(this, "关闭", "退出火焰纹章吗？");
    if(closeApp == QMessageBox::Yes)
    {
        CGameSystem::OverGame();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
