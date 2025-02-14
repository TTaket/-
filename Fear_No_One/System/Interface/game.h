#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QMessageBox>
#include "gamestart.h"
#include "gamechoice.h"
#include "gamechoice2.h"
#include "gamemap.h"
#include "packdef.h"
#include "CGameSystem.h"
#include "gameover.h"
#include "gamesuccess.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();

public slots:
    void dealJumpWidget(int widgetId);

private:
    Ui::Game *ui;

    GameStart* m_gameStart;
    GameChoice* m_gameChoice;
    GameChoice2* m_gameChoice2;
    GameMap* m_gameMap;
    GameOver* m_gameOver;
    GameSuccess* m_gameSuccess;

//游戏的关闭
public:
    void closeEvent(QCloseEvent *event);
};

#endif // GAME_H
