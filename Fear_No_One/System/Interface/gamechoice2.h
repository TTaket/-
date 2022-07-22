#ifndef GAMECHOICE2_H
#define GAMECHOICE2_H

#include <QWidget>
#include <Qpainter>
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
    void on_pb_returnLastPage_clicked();

    void on_pb_choice2_1_clicked();

signals:
    void SIG_jumpWidget(int id);

private:
    Ui::GameChoice2 *ui;
};

#endif // GAMECHOICE2_H
