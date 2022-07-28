#include "tool_info.h"
#include "ui_tool_info.h"

Tool_Info::Tool_Info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tool_Info)
{
    ui->setupUi(this);
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/Info.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);
}

Tool_Info::~Tool_Info()
{
    delete ui;
}

void Tool_Info::showinfo(QString qstr){
    ui->lb_Info->setText(qstr);
    this->show();
    QCoreApplication::processEvents();
    QThread::msleep(1000);
    this->hide();
}
