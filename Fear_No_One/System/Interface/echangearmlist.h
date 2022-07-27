#ifndef ECHANGEARMLIST_H
#define ECHANGEARMLIST_H

#include <QWidget>
#include <QListWidgetItem>
#include "armlistitem.h"

namespace Ui {
class EchangeArmList;
}

class EchangeArmList : public QWidget
{
    Q_OBJECT

public:
    explicit EchangeArmList(QWidget *parent = 0);
    ~EchangeArmList();

    void addItem(ArmListItem* item);
    void deleteItemList();
    void updateList();
    void createList();
    void setInfo(int id);

    int m_id; //人物id

private slots:
    void on_lw_blueArmList_itemClicked(QListWidgetItem *item);

    void on_lw_blueArmList_itemDoubleClicked(QListWidgetItem *item);

signals:
    //这个信号在交换武器时，通知gamemap对双方武器列表进行实时更新显示
    void SIG_changePeopleArmShow(int peoid1, int peoid2);

private:
    Ui::EchangeArmList *ui;

    std::vector<QListWidgetItem*> m_qListWidgetVector;
    std::vector<ArmListItem*> m_armListItemVector;
};

#endif // CHANGEARMLIST_H
