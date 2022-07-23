#ifndef GAMECHOICE2ITEM_H
#define GAMECHOICE2ITEM_H

#include <QWidget>

namespace Ui {
class GameChoice2Item;
}

class GameChoice2Item : public QWidget
{
    Q_OBJECT

public:
    explicit GameChoice2Item(QWidget *parent = 0);
    ~GameChoice2Item();

    //重写鼠标移入事件
    void enterEvent(QEvent* e);
    //重写鼠标移出事件
    void leaveEvent(QEvent* e);

    //设置选项名称
    void setInfo(QString name);

private slots:
    void on_pb_gameChoiceItem_2_clicked();

signals:
    void SIG_pb_save1();
    void SIG_pb_save2();
    void SIG_pb_save3();
    void SIG_pb_return();

private:
    Ui::GameChoice2Item *ui;
};

#endif // GAMECHOICE2ITEM_H
