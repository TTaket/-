#ifndef GETHIT_EXP_H
#define GETHIT_EXP_H

#include <QWidget>
#include "gamemap.h"
#include "CGameSystem.h"

class gamemap;

namespace Ui {
class gethit_exp;
}

class gethit_exp : public QWidget
{
    Q_OBJECT

public:
    explicit gethit_exp(QWidget *parent = nullptr);
    ~gethit_exp();
public:
    int peoid;
    int now_level;
    int now_Exp;
    int last_Exp;
    bool is_levelup;
public:
    void init_ui(int level1 , int Exp1 , int id ,int addExp);
    void st_level();

    void show_ui(int id ,int level1 , int Exp1 ,int addExp);

private:
    Ui::gethit_exp *ui;
};

#endif // GETHIT_EXP_H
