#include "peoplehpinfo.h"
#include "ui_peoplehpinfo.h"

PeopleHpInfo::PeopleHpInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PeopleHpInfo)
{
    ui->setupUi(this);
}

PeopleHpInfo::~PeopleHpInfo()
{
    delete ui;
}
