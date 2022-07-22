#ifndef PEOPLEHPINFO_H
#define PEOPLEHPINFO_H

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

private:
    Ui::PeopleHpInfo *ui;
};

#endif // PEOPLEHPINFO_H
