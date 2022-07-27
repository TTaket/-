#ifndef GETHIT_EXP_H
#define GETHIT_EXP_H

#include <QWidget>

namespace Ui {
class gethit_exp;
}

class gethit_exp : public QWidget
{
    Q_OBJECT

public:
    explicit gethit_exp(QWidget *parent = nullptr);
    ~gethit_exp();

private:
    Ui::gethit_exp *ui;
};

#endif // GETHIT_EXP_H
