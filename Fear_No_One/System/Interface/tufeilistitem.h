#ifndef TUFEILISTITEM_H
#define TUFEILISTITEM_H

#include <QWidget>
#include "Character.h"

namespace Ui {
class TufeiListItem;
}

class TufeiListItem : public QWidget
{
    Q_OBJECT

public:
    explicit TufeiListItem(QWidget *parent = 0);
    ~TufeiListItem();

    //设置选项信息
    void setInfo(int id);
    //获取土匪Id
    int getTufeiId();

    //手指是否显示
    void setFingerShow(bool enable);
private:
    Ui::TufeiListItem *ui;
    int m_id; //保存土匪id
};

#endif // TUFEILISTITEM_H
