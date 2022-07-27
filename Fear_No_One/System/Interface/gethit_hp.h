#ifndef GETHIT_HP_H
#define GETHIT_HP_H

#include <QWidget>
#include<CGameSystem.h>
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
    CArm* Armnow;
    Fightinfo* finfo;
public:
    void setInfo();
private:
    Ui::gethit_hp *ui;
};

#endif // GETHIT_HP_H
