#include "soundopenclose.h"
#include "ui_soundopenclose.h"

SoundOpenClose::SoundOpenClose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundOpenClose)
{
    ui->setupUi(this);
    ui->lb_background->setPixmap(QPixmap("../Fear_No_One/Resource/Photo/board(w).png")
                                 .scaled(ui->lb_background->width(), ui->lb_background->height()));
}

SoundOpenClose::~SoundOpenClose()
{
    delete ui;
}

//开启音效
void SoundOpenClose::on_pb_soundOpen_clicked()
{
    Q_EMIT SIG_soundOpen();
}

//关闭音效
void SoundOpenClose::on_pb_soundClose_clicked()
{
    Q_EMIT SIG_soundClose();
}
