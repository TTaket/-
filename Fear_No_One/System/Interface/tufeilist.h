#ifndef TUFEILIST_H
#define TUFEILIST_H

#include <QWidget>
#include "tufeilistitem.h"
#include <QListWidgetItem>
#include "Character.h"

namespace Ui {
class TuFeiList;
}

class TuFeiList : public QWidget
{
    Q_OBJECT

public:
    explicit TuFeiList(QWidget *parent = 0);
    ~TuFeiList();

    void addItem(TufeiListItem* item);
    void deleteItemList();
    void updateList();
    void createList();

private slots:
    void on_lw_tufeiList_itemClicked(QListWidgetItem *item);
    void on_lw_tufeiList_itemDoubleClicked(QListWidgetItem *item);

signals:
    //玩家选择攻击的土匪后，战斗前，显示双方信息
    void SIG_attackReadyInfoShow(int blueId, CArm* Armnow ,int readId);

private:
    Ui::TuFeiList *ui;

    std::vector<QListWidgetItem*> m_qListWidgetVector;
    std::vector<TufeiListItem*> m_TufeiListItemVector;
};

#endif // TUFEILIST_H
