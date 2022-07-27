#ifndef CHANGEPEOPLELISTITEM_H
#define CHANGEPEOPLELISTITEM_H

#include <QWidget>
#include "Character.h"

namespace Ui {
class ChangePeopleListItem;
}

class ChangePeopleListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePeopleListItem(QWidget *parent = 0);
    ~ChangePeopleListItem();

    //设置选项信息
    void setInfo(int id);
    //获取友方Id
    int getBlueId();

    //手指是否显示
    void setFingerShow(bool enable);
private:
    Ui::ChangePeopleListItem *ui;
    int m_id; //保存友方id
};

#endif // CHANGEPEOPLELISTITEM_H
