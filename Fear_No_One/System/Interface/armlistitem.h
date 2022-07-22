#ifndef ARMLISTITEM_H
#define ARMLISTITEM_H

#include <QWidget>

namespace Ui {
class ArmListItem;
}

class ArmListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ArmListItem(QWidget *parent = 0);
    ~ArmListItem();

    //设置选项信息
    void setInfo(QString name, int iconId, int value);
    //获取武器名字信息
    QString getArmName();

    //手指是否显示
    void setFingerShow(bool enable);

private:
    Ui::ArmListItem *ui;
};

#endif // ARMLISTITEM_H
