#include "mybuttongamestart.h"

MyButtonGameStart::MyButtonGameStart(QWidget *parent) : QPushButton(parent)
{

}

//重写鼠标移入事件
void MyButtonGameStart::enterEvent(QEvent *e)
{
    //按键闪烁
    setFont(QFont("华文新魏",29));
}

//重写鼠标移出事件
void MyButtonGameStart::leaveEvent(QEvent *e)
{
    //闪烁消失
    setFont(QFont("华文新魏",25));
}
