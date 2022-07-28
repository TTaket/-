#ifndef GAMECHOICE_H
#define GAMECHOICE_H

#include <QWidget>
#include <QPainter>
#include "CGameSystem.h"

namespace Ui {
class GameChoice;
}

class GameChoice : public QWidget
{
    Q_OBJECT

public:
    explicit GameChoice(QWidget *parent = 0);
    ~GameChoice();


public:
    void paintEvent(QPaintEvent *event);
    void drawPixmap(QPainter *painter);

private slots:
    void slot_pb_continue();
    void slot_pb_start();
    void slot_pb_return();
    void slot_pb_delete();
    void slot_pb_copy();

signals:
    void SIG_jumpWidget(int id);

private:
    Ui::GameChoice *ui;
};

#endif // GAMECHOICE1_H
