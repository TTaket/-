#ifndef GAMECHOICE2_H
#define GAMECHOICE2_H

#include <QWidget>
#include <Qpainter>
#include <CGameSystem.h>
namespace Ui {
class GameChoice2;
}

class GameChoice2 : public QWidget
{
    Q_OBJECT

public:
    explicit GameChoice2(QWidget *parent = 0);
    ~GameChoice2();
public:
    void paintEvent(QPaintEvent *event);
    void drawPixmap(QPainter *painter);

private slots:
    void slot_pb_save1();
    void slot_pb_save2();
    void slot_pb_save3();
    void slot_pb_return();

signals:
    void SIG_jumpWidget(int id);

private:
    Ui::GameChoice2 *ui;
};

#endif // GAMECHOICE2_H
