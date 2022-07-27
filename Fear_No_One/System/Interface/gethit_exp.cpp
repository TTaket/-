#include "gethit_exp.h"
#include "ui_gethit_exp.h"

gethit_exp::gethit_exp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gethit_exp)
{
    ui->setupUi(this);
}

gethit_exp::~gethit_exp()
{
    delete ui;
}
