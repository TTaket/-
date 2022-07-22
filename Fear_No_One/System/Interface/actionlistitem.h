#ifndef ACTIONLISTITEM_H
#define ACTIONLISTITEM_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class ActionListItem;
}

class ActionListItem : public QWidget, public QListWidgetItem
{
    Q_OBJECT

public:
    explicit ActionListItem(QWidget *parent = 0);
    ~ActionListItem();

    //设置选项信息
    void setInfo(QString name);
    //获取选项信息
    QString getInfo();

    //手指是否显示
    void setFingerShow(bool enable);

signals:
    //单击选中信号
    void SIG_itemSignleClicked();

private:
    Ui::ActionListItem *ui;
};

#endif // ACTIONLISTITEM_H
