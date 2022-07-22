#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QList>
#include "peoplehpinfo.h"
#include "groundtypeinfo.h"
#include "actionlist.h"
#include "armlist.h"
#include "actionlistitem.h"
#include "ArmListitem.h"
#include "arminfo.h"
#include "armchoice.h"
#include "packdef.h"
#include "CGameSystem.h"

namespace Ui {
class GameMap;
}

class GameMap : public QWidget
{
    Q_OBJECT

public:
    explicit GameMap(QWidget *parent = 0);
    ~GameMap();


    //更新地图
    void updateMap();


signals:
    void SIG_jumpWidget(int id);
private slots:
    void on_pb_test_clicked();
    //更新列表信号槽函数
    void slot_updateList();
    //行动处理信号槽函数
    void slot_action(QString actionName);
    //武器信息显示信号槽函数
    void slot_armInfoShow(QString armName);
    //武器选择信息（装备，交换，舍去）信号槽函数
    void slot_armChoice();


private:
    Ui::GameMap *ui;
    PeopleHpInfo* m_peopleHpInfo;
    GroundTypeInfo* m_groundTypeInfo;
    ActionList* m_actionList;
    ArmList* m_armList;
    ArmInfo* m_armInfo;
    ArmChoice* m_armChoice;

//绘制地图
public:
    void paintEvent(QPaintEvent *event);
    void drawPixmap(QPainter *painter);

//鼠标捕获
public:
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // GAMEMAP_H
