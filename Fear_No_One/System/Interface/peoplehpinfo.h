#ifndef PEOPLEHPINFO_H
#define PEOPLEHPINFO_H
#include <CGameSystem.h>
#include <QWidget>

namespace Ui {
class PeopleHpInfo;
}

class PeopleHpInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PeopleHpInfo(QWidget *parent = 0);
    ~PeopleHpInfo();
    int people_id;
    void setInfo();//更新信息

private:
    Ui::PeopleHpInfo *ui;
};

#endif // PEOPLEHPINFO_H
