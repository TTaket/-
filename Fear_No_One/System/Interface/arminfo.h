#ifndef ARMINFO_H
#define ARMINFO_H

#include <QWidget>
#include "Arms.h"
#include "gamemap.h"

namespace Ui {
class ArmInfo;
}

class ArmInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ArmInfo(QWidget *parent = 0);
    ~ArmInfo();

    void setArmInfo(CArm* arm);

private:
    Ui::ArmInfo *ui;
};

#endif // ARMINFO_H
