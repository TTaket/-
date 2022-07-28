#ifndef GAMESTART_H
#define GAMESTART_H

#include <QWidget>
#include <QPainter>
#include "CGameSystem.h"

namespace Ui {
class GameStart;
}

class GameStart : public QWidget
{
    Q_OBJECT

public:
    explicit GameStart(QWidget *parent = 0);
    ~GameStart();

public:
    void paintEvent(QPaintEvent *event);
    void drawPixmap(QPainter *painter);

private slots:
    void on_pb_gameStart_clicked();

signals:
    void SIG_jumpWidget(int id);

private:
    Ui::GameStart *ui;
};

#endif // GAMESTART_H
