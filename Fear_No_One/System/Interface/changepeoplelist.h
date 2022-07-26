#ifndef CHANGEPEOPLELIST_H
#define CHANGEPEOPLELIST_H

#include <QWidget>

namespace Ui {
class ChangePeopleList;
}

class ChangePeopleList : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePeopleList(QWidget *parent = 0);
    ~ChangePeopleList();

private:
    Ui::ChangePeopleList *ui;
};

#endif // CHANGEPEOPLELIST_H
