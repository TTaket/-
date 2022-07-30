#ifndef SOUNDOPENCLOSE_H
#define SOUNDOPENCLOSE_H

#include <QWidget>
#include "CGameSystem.h"

namespace Ui {
class SoundOpenClose;
}

class SoundOpenClose : public QWidget
{
    Q_OBJECT

public:
    explicit SoundOpenClose(QWidget *parent = 0);
    ~SoundOpenClose();

signals:
    void SIG_soundOpen();
    void SIG_soundClose();
private slots:
    void on_pb_soundOpen_clicked();

    void on_pb_soundClose_clicked();

private:
    Ui::SoundOpenClose *ui;
};

#endif // SOUNDOPENCLOSE_H
