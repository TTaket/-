#include "mybuttongamechoice.h"

MyButtonGameChoice::MyButtonGameChoice(QWidget *parent) : QPushButton(parent)
{

}

//重写鼠标移入事件
void MyButtonGameChoice::enterEvent(QEvent *e)
{
    //按键闪烁
    setFont(QFont("华文秀丽_CNKI",19));
    //播放选择音效
}

//重写鼠标移出事件
void MyButtonGameChoice::leaveEvent(QEvent *e)
{
    //闪烁消失
    setFont(QFont("华文秀丽_CNKI",15));
}
