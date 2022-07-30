#ifndef SHANGYAO_H
#define SHANGYAO_H

#include <QWidget>
#include "Arms.h"

namespace Ui {
class ShangYao;
}

class ShangYao : public QWidget
{
    Q_OBJECT

public:
    explicit ShangYao(QWidget *parent = 0);
    ~ShangYao();

    CArm* ArmNow;

private slots:
    void on_pb_yes_clicked();

    void on_pb_no_clicked();

signals:
    void SIG_useShangYao(bool yes);

private:
    Ui::ShangYao *ui;
};

#endif // SHANGYAO_H
