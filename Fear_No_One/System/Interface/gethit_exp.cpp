#include "gethit_exp.h"
#include "ui_gethit_exp.h"

gethit_exp::gethit_exp(QWidget *parent) :
    QWidget(parent),
    peoid(0),
    now_level(0),
    now_Exp(0),
    last_Exp(0),
    is_levelup(0),
    ui(new Ui::gethit_exp)
{
    ui->setupUi(this);
}

gethit_exp::~gethit_exp()
{
    delete ui;
}

void gethit_exp::init_ui(int id ,int level1 , int Exp1 ,int addExp){
    peoid = id;
    now_level = level1;
    now_Exp = Exp1;
    last_Exp = addExp;
    is_levelup = 0;
    ui->lb_icon->setPixmap(QPixmap(CGameSystem::Character_Info[peoid-1]->m_iconPos).scaled(ui->lb_icon->width(), ui->lb_icon->height()));
    ui->lb_name->setText(QString::fromStdString(CGameSystem::Character_Info[peoid-1]->m_name));
    ui->ProBar_Exp->setRange(0,100);
    ui->ProBar_Exp->setValue(now_Exp);
    ui->lb_levelval->setText( QString::number(level1));
    ui->background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/Gamechoice.png").scaled(ui->background->width(), ui->background->height()));
    ui->lb_levelup->hide();

}

void gethit_exp::st_level(){
    this->show();
    QCoreApplication::processEvents();//保证完整的show
    QThread::msleep(500);
    int willExp = 0;
    willExp = now_Exp + last_Exp;
    while(last_Exp>0){
        last_Exp--;
        ui->ProBar_Exp->setValue(++now_Exp);
            if(now_Exp >= 100){
                is_levelup = 1;
                ui->lb_levelval->setText( QString::number(now_level+1));
                ui->lb_levelup->show();
                QCoreApplication::processEvents();//保证完整的show
                QThread::msleep(1500);
                ui->ProBar_Exp->setValue(0);
                now_Exp = 0;
                break;
            }
            QThread::msleep(30);
        }
    while(last_Exp>0){
        last_Exp--;
        ui->ProBar_Exp->setValue(++now_Exp);
        QCoreApplication::processEvents();//保证完整
        QThread::msleep(30);
    }
    QThread::msleep(500);
    this->hide();
}

void gethit_exp::show_ui(int id ,int level1 , int Exp1 ,int addExp){
    init_ui(id,level1,Exp1,addExp);
    st_level();
}
