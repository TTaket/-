#include "groundtypeinfo.h"
#include "ui_groundtypeinfo.h"

GroundTypeInfo::GroundTypeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroundTypeInfo)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png"));
}
GroundTypeInfo::~GroundTypeInfo()
{
    delete ui;
}
