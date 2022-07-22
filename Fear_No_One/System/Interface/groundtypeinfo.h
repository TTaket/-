#ifndef GROUNDTYPEINFO_H
#define GROUNDTYPEINFO_H
#include <CGameSystem.h>
#include <QWidget>

namespace Ui {
class GroundTypeInfo;
}

class GroundTypeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit GroundTypeInfo(QWidget *parent = 0);
    ~GroundTypeInfo();
    int ground_id;
    void setInfo();//更新信息

private:
    Ui::GroundTypeInfo *ui;
};

#endif // GROUNDTYPEINFO_H
