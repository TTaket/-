#ifndef CHANGEPEOPLELIST_H
#define CHANGEPEOPLELIST_H

#include <QWidget>
#include <QListWidgetItem>
#include "changepeoplelistitem.h"

namespace Ui {
class ChangePeopleList;
}

class ChangePeopleList : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePeopleList(QWidget *parent = 0);
    ~ChangePeopleList();

    void addItem(ChangePeopleListItem* item);
    void deleteItemList();
    void updateList();
    void createList();

private slots:
    void on_lw_changePeopleList_itemClicked(QListWidgetItem *item);

    void on_lw_changePeopleList_itemDoubleClicked(QListWidgetItem *item);

signals:
    //双方角色可交换的武器信息显示信号
    void SIG_changePeopleArmShow(int peoid1, int peoid2);

private:
    Ui::ChangePeopleList *ui;

    std::vector<QListWidgetItem*> m_qListWidgetVector;
    std::vector<ChangePeopleListItem*> m_ChangePeopleListItemVector;
};

#endif // CHANGEPEOPLELIST_H
