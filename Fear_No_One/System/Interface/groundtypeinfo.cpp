#include "groundtypeinfo.h"
#include "ui_groundtypeinfo.h"

GroundTypeInfo::GroundTypeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroundTypeInfo)
{
    ui->setupUi(this);
}

GroundTypeInfo::~GroundTypeInfo()
{
    delete ui;
}
