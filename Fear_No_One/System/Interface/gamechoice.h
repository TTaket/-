#ifndef GAMECHOICE_H
#define GAMECHOICE_H

#include <QWidget>
#include <QPainter>
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
    void on_pb_startNew_clicked();

    void on_pb_returnLastPage_clicked();

signals:
    void SIG_jumpWidget(int id);

private:
    Ui::GameChoice *ui;
};

#endif // GAMECHOICE1_H
