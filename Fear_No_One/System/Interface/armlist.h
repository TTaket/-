#ifndef ARMLIST_H
#define ARMLIST_H

#include <QWidget>
#include <QListWidgetItem>
#include "ArmListitem.h"

namespace Ui {
class ArmList;
}

class ArmList : public QWidget
{
    Q_OBJECT

public:
    explicit ArmList(QWidget *parent = 0);
    ~ArmList();

    void addItem(ArmListItem* item);
    void deleteItemList();
    void updateList();
    void createList();

private slots:
    void on_lw_armList_itemClicked(QListWidgetItem *item);

    void on_lw_armList_itemDoubleClicked(QListWidgetItem *item);

signals:
    void SIG_armInfoShow(QString armName);
    void SIG_armChoice();

private:
    Ui::ArmList *ui;
    std::vector<QListWidgetItem*> m_qListWidgetVector;
    std::vector<ArmListItem*> m_armListItemVector;
};

#endif // ArmList_H
