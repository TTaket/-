#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>
#include "CGameSystem.h"

namespace Ui {
class GameOver;
}

class GameOver : public QWidget
{
    Q_OBJECT

public:
    explicit GameOver(QWidget *parent = 0);
    ~GameOver();

signals:
    void SIG_jumpWidget(int i);

private slots:
    void on_pb_returnGameStart_clicked();

private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
