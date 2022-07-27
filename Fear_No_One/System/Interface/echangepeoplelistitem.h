#ifndef ECHANGEPEOPLELISTITEM_H
#define ECHANGEPEOPLELISTITEM_H

#include <QWidget>
#include "Character.h"

namespace Ui {
class EchangePeopleListItem;
}

class EchangePeopleListItem : public QWidget
{
    Q_OBJECT

public:
    explicit EchangePeopleListItem(QWidget *parent = 0);
    ~EchangePeopleListItem();

    //设置选项信息
    void setInfo(int id);
    //获取友方Id
    int getBlueId();

    //手指是否显示
    void setFingerShow(bool enable);
private:
    Ui::EchangePeopleListItem *ui;
    int m_id; //保存友方id
};

#endif // CHANGEPEOPLELISTITEM_H
