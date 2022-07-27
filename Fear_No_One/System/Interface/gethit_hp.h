#ifndef GETHIT_HP_H
#define GETHIT_HP_H

#include <QWidget>
#include<CGameSystem.h>
#include<gamemap.h>
#include<QPalette>






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
    int blueid;
    int redid;
    CArm* Arm1;
    CArm* Arm2;
    int ground_id;
    Fightinfo* finfo;

public:

    void setInfo(Fightinfo* Finfo);
    void Init_ui();
    void st_Fight();

public slots:
    void slot_Fightinfo(Fightinfo* Finfo);

private:
    Ui::gethit_hp *ui;
};

#endif // GETHIT_HP_H
