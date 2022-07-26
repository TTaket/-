#include "changepeoplelist.h"
#include "ui_changepeoplelist.h"

ChangePeopleList::ChangePeopleList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePeopleList)
{
    ui->setupUi(this);

}

ChangePeopleList::~ChangePeopleList()
{
    delete ui;
}
