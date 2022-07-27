#ifndef ECHANGEPEOPLELIST_H
#define ECHANGEPEOPLELIST_H

#include <QWidget>
#include <QListWidgetItem>
#include "echangepeoplelistitem.h"

namespace Ui {
class EchangePeopleList;
}

class EchangePeopleList : public QWidget
{
    Q_OBJECT

public:
    explicit EchangePeopleList(QWidget *parent = 0);
    ~EchangePeopleList();

    void addItem(EchangePeopleListItem* item);
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
    Ui::EchangePeopleList *ui;

    std::vector<QListWidgetItem*> m_qListWidgetVector;
    std::vector<EchangePeopleListItem*> m_ChangePeopleListItemVector;
};

#endif // ECHANGEPEOPLELIST_H
