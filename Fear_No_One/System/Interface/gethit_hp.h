#ifndef GETHIT_HP_H
#define GETHIT_HP_H

#include <QWidget>
#include<CGameSystem.h>
#include<gamemap.h>
#include"tool_info.h"
#include"gethit_exp.h"




class gethit_exp;

namespace Ui {
class gethit_hp;
}

class gethit_hp : public QWidget
{
    Q_OBJECT

public:
    explicit gethit_hp(QWidget *parent = nullptr);
    ~gethit_hp();

public:
    Tool_Info* tinfo;
    int blueid;
    int redid;
    CArm* Arm1;
    CArm* Arm2;
    int ground_id;
    Fightinfo* finfo;
    gethit_exp* m_gethit_exp;

public:
    void setInfo(Fightinfo* Finfo,CArm* arm1,CArm* arm2);
    void Init_ui();
    void st_Fight();

public slots:
    void slot_Fightinfo(Fightinfo* Finfo ,CArm* arm1 ,CArm* arm2);

private:
    Ui::gethit_hp *ui;
};

#endif // GETHIT_HP_H
