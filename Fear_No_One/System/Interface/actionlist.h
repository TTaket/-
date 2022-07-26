#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include <QWidget>
#include <QListWidgetItem>
#include "actionlistitem.h"
#include "Character.h"

namespace Ui {
class ActionList;
}

class ActionList : public QWidget
{
    Q_OBJECT

public:
    explicit ActionList(QWidget *parent = 0);
    ~ActionList();

    void addItem(ActionListItem* item);
    void deleteItemList();
    void updateList();
    void createList();
    //劫持test


private slots:
    //处理单击选中
    void on_lw_ActionItemList_itemClicked(QListWidgetItem *item);

    void on_lw_ActionItemList_itemDoubleClicked(QListWidgetItem *item);

signals:
    void SIG_updateList();
    void SIG_action(QString actionName);

private:
    Ui::ActionList *ui;
    std::vector<QListWidgetItem*> m_qListWidgetVector;
    std::vector<ActionListItem*> m_ActionListItemVector;
};

#endif // ACTIONLIST_H
