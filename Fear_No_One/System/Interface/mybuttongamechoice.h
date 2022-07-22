#ifndef MYBUTTONGAMECHOICE_H
#define MYBUTTONGAMECHOICE_H

#include <QPushButton>

class MyButtonGameChoice : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButtonGameChoice(QWidget *parent = 0);

    //重写鼠标移入事件
    void enterEvent(QEvent* e);
    //重写鼠标移出事件
    void leaveEvent(QEvent* e);
signals:

public slots:
};

#endif // MYBUTTONGAMECHOICE_H
