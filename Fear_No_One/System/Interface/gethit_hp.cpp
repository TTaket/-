#include "gethit_hp.h"
#include "ui_gethit_hp.h"

gethit_hp::gethit_hp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gethit_hp)
{
    ui->setupUi(this);
}

gethit_hp::~gethit_hp()
{
    delete ui;
}


void gethit_hp::setInfo(){

}
