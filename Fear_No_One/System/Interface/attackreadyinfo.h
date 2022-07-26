#ifndef ATTACKREADYINFO_H
#define ATTACKREADYINFO_H

#include <QWidget>
#include "Arms.h"
#include "Character.h"
#include "CGameSystem.h"

namespace Ui {
class AttackReadyInfo;
}

class AttackReadyInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AttackReadyInfo(QWidget *parent = 0);
    ~AttackReadyInfo();

    void setInfo(int blueId,CArm* Armnow, int redId);

private slots:
    void on_lb_startZhandou_clicked();

private:
    Ui::AttackReadyInfo *ui;

    int m_blueId; //记录将要战斗的蓝方角色id
    int m_redId; //记录将要战斗的红方角色id
};

#endif // ATTACKREADYINFO_H
