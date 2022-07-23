#ifndef GAMECHOICEITEM_H
#define GAMECHOICEITEM_H

#include <QWidget>

namespace Ui {
class GameChoiceItem;
}

class GameChoiceItem : public QWidget
{
    Q_OBJECT

public:
    explicit GameChoiceItem(QWidget *parent = 0);
    ~GameChoiceItem();

    //重写鼠标移入事件
    void enterEvent(QEvent* e);
    //重写鼠标移出事件
    void leaveEvent(QEvent* e);

    //设置选项名称
    void setInfo(QString name);
private slots:
    void on_pb_gameChoice1Item_clicked();

signals:
    void SIG_pb_continue();
    void SIG_pb_start();
    void SIG_pb_return();
    void SIG_pb_delete();
    void SIG_pb_copy();

private:
    Ui::GameChoiceItem *ui;
};

#endif // GAMECHOICEITEM_H
