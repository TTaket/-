#ifndef GAMESUCCESS_H
#define GAMESUCCESS_H

#include <QWidget>
#include "CGameSystem.h"

namespace Ui {
class GameSuccess;
}

class GameSuccess : public QWidget
{
    Q_OBJECT

public:
    explicit GameSuccess(QWidget *parent = 0);
    ~GameSuccess();

private slots:
    void on_pb_returnGameStart_clicked();
signals:
    void SIG_jumpWidget(int i);

private:
    Ui::GameSuccess *ui;
};

#endif // GAMESUCCESS_H
