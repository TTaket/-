#include "shangyao.h"
#include "ui_shangyao.h"

ShangYao::ShangYao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShangYao)
{
    ui->setupUi(this);

    QString str = "";
    str.append("使用伤药后，Hp恢复1点\n");
    str.append("确定要使用伤药吗？");
    ui->lb_tip->setText(str);
}

ShangYao::~ShangYao()
{
    delete ui;
}

void ShangYao::on_pb_yes_clicked()
{
    Q_EMIT SIG_useShangYao(true);
}

void ShangYao::on_pb_no_clicked()
{
    Q_EMIT SIG_useShangYao(false);
}
