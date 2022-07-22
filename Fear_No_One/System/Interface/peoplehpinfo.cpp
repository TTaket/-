#include "peoplehpinfo.h"
#include "ui_peoplehpinfo.h"

PeopleHpInfo::PeopleHpInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeopleHpInfo)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png"));
}

PeopleHpInfo::~PeopleHpInfo()
{
    delete ui;
}
