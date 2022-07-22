#ifndef ARMCHOICE_H
#define ARMCHOICE_H

#include <QWidget>
#include <actionlistitem.h>
#include <QListWidgetItem>

namespace Ui {
class ArmChoice;
}

class ArmChoice : public QWidget
{
    Q_OBJECT

public:
    explicit ArmChoice(QWidget *parent = 0);
    ~ArmChoice();

    void addItem(ActionListItem* item);
    void deleteItemList();
    void updateList();
    void createList();

private slots:
    void on_lw_armChoice_itemClicked(QListWidgetItem *item);

    void on_lw_armChoice_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ArmChoice *ui;
    std::vector<QListWidgetItem*> m_qListWidgetVector;
    std::vector<ActionListItem*> m_ActionListItemVector;
};

#endif // ARMCHOICE_H
