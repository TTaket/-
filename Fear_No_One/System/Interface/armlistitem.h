#ifndef ARMLISTITEM_H
#define ARMLISTITEM_H
#include<CGameSystem.h>
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
    void setInfo();
    //获取武器名字信息
    QString getArmName();
    CArm* pArm;
    //手指是否显示
    void setFingerShow(bool enable);

    int m_peoid; //武器所属人id，在交换武器时需要用到
private:
    Ui::ArmListItem *ui;
};

#endif // ARMLISTITEM_H
