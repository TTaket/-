#ifndef DUIWU_H
#define DUIWU_H

#include <QWidget>
#include <QTableWidgetItem>
#include "CGameSystem.h"
#include "Arms.h"
#include "Character.h"

namespace Ui {
class Duiwu;
}

class Duiwu : public QWidget
{
    Q_OBJECT

public:
    explicit Duiwu(QWidget *parent = 0);
    ~Duiwu();

    void setInfo();

private slots:
    void on_pb_close_clicked();

private:
    Ui::Duiwu *ui;
};

#endif // DUIWU_H
