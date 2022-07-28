#ifndef MYBUTTONGAMESTART_H
#define MYBUTTONGAMESTART_H

#include <QPushButton>
#include "CGameSystem.h"

class MyButtonGameStart : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButtonGameStart(QWidget *parent = 0);

    //重写鼠标移入事件
    void enterEvent(QEvent* e);
    //重写鼠标移出事件
    void leaveEvent(QEvent* e);
signals:

public slots:
};

#endif // MYBUTTONGAMESTART_H
