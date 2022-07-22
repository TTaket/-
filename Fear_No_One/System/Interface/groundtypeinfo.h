#ifndef GROUNDTYPEINFO_H
#define GROUNDTYPEINFO_H

#include <QWidget>

namespace Ui {
class GroundTypeInfo;
}

class GroundTypeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit GroundTypeInfo(QWidget *parent = 0);
    ~GroundTypeInfo();

private:
    Ui::GroundTypeInfo *ui;
};

#endif // GROUNDTYPEINFO_H
