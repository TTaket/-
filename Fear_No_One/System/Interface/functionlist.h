#ifndef FUNCTION_H
#define FUNCTION_H

#include <QWidget>
#include <CGameSystem.h>
#include "duiwu.h"

namespace Ui {
class Functionlist;
}

class Functionlist : public QWidget
{
    Q_OBJECT

public:
    explicit Functionlist(QWidget *parent = nullptr);
    ~Functionlist();

public:
    Duiwu * m_duiwu;
signals:
    void ST_RedWork();
private slots:
    void on_pb_sound_clicked();

    void on_pb_duiwu_clicked();

    void on_pb_red_clicked();

    void on_pb_overgame_clicked();

private:
    Ui::Functionlist *ui;
};

#endif // FUNCTION_H
