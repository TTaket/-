#ifndef ATTACKREADYINFO_H
#define ATTACKREADYINFO_H

#include <QWidget>
#include "CGameSystem.h"
#include "gamemap.h"

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

signals:
    void SIG_Fightinfo(Fightinfo*,CArm*,CArm*);
private slots:
    void on_lb_startZhandou_clicked();

private:
    Ui::AttackReadyInfo *ui;

    int m_blueId; //记录将要战斗的蓝方角色id
    int m_redId; //记录将要战斗的红方角色id
    CArm* blueArm;
    CArm* redArm ;

};

#endif // ATTACKREADYINFO_H
